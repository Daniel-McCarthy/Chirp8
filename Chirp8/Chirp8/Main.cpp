
#include "Main.h"
#include "Binary.h"
#include "Opcode.h"
#include "Input.h"

using namespace std;

Memory chipMemory = Memory();
Window chipWindow = Window("Chirp8", 64, 32);
vector<byte> registers = vector<byte>(0xF + 1);
stack<short> chipStack = stack<short>();
short I = 0;
uint8_t delayTimer = 60; //hz
uint8_t soundTimer = 0; //hz
int memoryPointer = 0x200;
vector<byte> keysDown = vector<byte>(0xF + 1);
bool run = true;

inline void decrementTimers()
{
	while (run)
	{
		if (soundTimer > 0)
			soundTimer--;

		if (delayTimer > 0)
			delayTimer--;

		if (soundTimer > 0)
		{
			//temporary sound
			//Beep(523, 40);
			Beep(350, 40);
		}
		this_thread::sleep_for(chrono::milliseconds(32));//16));
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SDL_SetWindowSize(chipWindow.sdlWindow,640, 320);
	SDL_ShowWindow(chipWindow.sdlWindow);

	for (int i = 0; i < 0xF+1; i++)
	{
		registers[i] = 0;
	}

	Opcode* opcodes = new Opcode();

	chipMemory.loadRom("C://Users//Dan//Desktop//TETRIS.g");
	//chipMemory.loadRom("C://Users//Dan//Desktop//PONG.g");
	//chipMemory.loadRom("C://Users//Dan//Desktop//PONGAI.g");
	//chipMemory.loadRom("C://Users//Dan//Desktop//BRIX.g"); //FX33 issue solved, still have problem with collision. Something wrong with flag? Maybe related to blinking pixels? 
	//chipMemory.loadRom("C://Users//Dan//Desktop//BLINKY.g"); //DOESN'T WORK AT ALL - Debug, disassemble, find out what's wrong
	//chipMemory.loadRom("C://Users//Dan//Desktop//INVADERS.g"); //Drawing is messed up, screen blinking solution seems to mess up letters too
	//chipMemory.loadRom("C://Users//Dan//Desktop//MAZE.g");
	chipMemory.loadFontSprites();


	thread decrementTimers1(decrementTimers);


	SDL_Event event;
	while (run)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				run = false;
			}
			else if (SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE) //ESC
					{
						run = false;
					}

				}

				//Chip 8 hex keyboard keys:
				//[1][2][3][C]
				//[4][5][6][D]
				//[7][8][9][E]
				//[A][0][B][F]

				//Mapped to standard keyboard keys:
				//[1][2][3][4]
				//[Q][W][E][R]
				//[A][S][D][F]
				//[Z][X][C][V]
			}

		}
		


		readInput();

		opcodes->selectOpcode((short)(chipMemory.readMemory(memoryPointer++) << 8 | chipMemory.readMemory(memoryPointer++)));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<int> data = { 2, 7, 62, 30, 4, 6 };  //Chicken Sprite
		chipWindow.DrawSprite(data, 0, 1);

		SDL_RenderClear(chipWindow.sdlRenderer);									//Clears Screen
		SDL_RenderCopy(chipWindow.sdlRenderer, chipWindow.texture, NULL, NULL);		//Copies Texture to Screen
		SDL_RenderPresent(chipWindow.sdlRenderer);									//Renders Screen

		
		//SDL_Delay(10); //moved into opcodes temporarily to avoid delaying on drawing, in hopes it speeds up tetris raycasting

		//Reset keys
		/*
		for (int i = 0; i < 16; i++)
		{
			if (keysDown[i] == 1)
				OutputDebugStringA("Key Down ");//:" + i);
		}
		*/
		/*
		for (int i = 0; i < 16; i++)
		{
			keysDown[i] = 0;
		}
		*/
	}

	//delete[] chipWindow.sdlSurface.pixels;

	SDL_DestroyTexture(chipWindow.texture);
	SDL_DestroyRenderer(chipWindow.sdlRenderer);
	SDL_DestroyWindow(chipWindow.sdlWindow);
	SDL_Quit();

	return 0;
}


