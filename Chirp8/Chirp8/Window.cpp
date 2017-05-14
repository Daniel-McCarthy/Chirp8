#include "Window.h"
#include "Binary.h"
#include "Main.h"

Window::Window(string title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	sdlSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 64, 32);
	canvas = new Uint32[64 * 32];
	memset(canvas, 0, 64 * 32 * sizeof(Uint32));
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);
	SDL_GL_SetSwapInterval(1); //Enable VSYNC
	//glClearColor(0, 0, 1, 1);
}

Window::~Window()
{

	SDL_GL_DeleteContext(sdlGLContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}



void Window::DrawPixel(int x, int y, bool enabled)
{
	if (x < 64 && y < 64)
	{
		if (enabled)
		{
			canvas[y * 64 + x] = (Uint32)0xFFFFFFFF;//White //RGBA Format
		}
		else
		{
			canvas[y * 64 + x] = (Uint32)0x00000000;//Black
		}

	}
	else
	{
		cout << "Error: Draw Pixel x and y have a range of 0-63. The input was X: " << x << " Y: " << y << endl;
	}
}

bool Window::XorPixel(int x, int y)
{
	if (canvas[y * 64 + x] == (Uint32)0)
	{
		canvas[y * 64 + x] = (Uint32)0xFFFFFFFF;//RGBA
		//registers[0xF] = 0;
		return false;
	}
	else
	{

		canvas[y * 64 + x] = (Uint32)0;
		//registers[0xF] = 1;
		return true;
	}
}

void Window::DrawSprite(vector<int> spriteData, int x, int y)
{
	for (int i = 0; i < (int)spriteData.size(); i++)
	{
		string line = Binary::toBinary(spriteData[i]);

		for (int j = 0; j < (int)line.length(); j++)
		{
			if (line[j] == '1')
			{
				DrawPixel(x+j, y+i, true);
			}
		}
	}
}

void Window::DrawSprite(vector<int> spriteData, int x, int y, int n)
{
	int height = (spriteData.size() > n) ? n : spriteData.size();
	bool collision = false;

	for (int i = 0; i < height; i++)
	{
		
		string line = Binary::toBinary(spriteData.at(i));//spriteData[i]);

		for (int j = 0; j < (int)line.length(); j++)
		{
			if (line[j] == '1')
			{
				bool anyCollision = XorPixel(x + j, y + i);

				if (anyCollision)
				{
					collision = true;
				}
			}
		}
		
	}

	if (collision)
	{
		registers[0xF] = 1;
	}
	else
	{
		registers[0xF] = 0;
		SDL_UpdateTexture(texture, NULL, canvas, 64 * sizeof(Uint32)); //TEMPORARY
	}
	//SDL_UpdateTexture(texture, NULL, canvas, 64 * sizeof(Uint32)); //TEMPORARY
}

void Window::clearScreen()
{
	memset(canvas, 0, 64 * 32 * sizeof(Uint32));
	SDL_UpdateTexture(texture, NULL, canvas, 64 * sizeof(Uint32)); //TEMPORARY
}
