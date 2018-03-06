#include "Opcode.h"
#include "Window.h"
#include "Main.h"
#include "Sprite.h"

Opcode::Opcode()
{
}


void Opcode::selectOpcode(short opcode)
{
	short test = opcode & 0xF000;

	if ((opcode & 0xF000) != 0xd000)
	{
		SDL_Delay(1);
	}

	switch (opcode & 0xF000)
	{
	case 0x0000:
	{
		switch (opcode & 0x0FFF)
		{
			case 0x00E0:
			{
				//clear screen
				opcode00E0();
				break;
			}
			case 0x00EE:
			{
				//RET
				opcode00EE();
				break;
			}
			default:
			{
				//call NNN
				//Not likely to implement
				break;
			}
		}
		break;
	}
	case 0x1000:
	{
		//jump NNN
		opcode1NNN(opcode & 0x0FFF);
		break;
	}
	case 0x2000:
	{
		//call SUB NNN
		opcode2NNN(opcode & 0x0FFF);
		break;
	}
	case 0x3000:
	{
		//Conditional opcode skip (if VX == NN)
		opcode3XNN((opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	}
	case 0x4000:
	{
		//Conditional opcode skip (if VX != NN)
		opcode4XNN((opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	}
	case 0x5000:
	{
		//Conditional opcode skip (if VX == VY)
		opcode5XYN((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		break;
	}
	case 0x6000:
	{
		//Set VX = NN
		opcode6XNN((opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	}
	case 0x7000:
	{
		//Set VX += NN
		opcode7XNN((opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	}
	case 0x8000:
	{
		switch (opcode & 0x000F)
		{
			case 0x0000:
			{
				//Set VX = VY
				opcode8XY0((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0001:
			{
				//Set VX |= VY
				opcode8XY1((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0002:
			{
				//Set VX &= VY
				opcode8XY2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0003:
			{
				//Set VX ^= VY
				opcode8XY3((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0004:
			{
				//Set VX += VY
				opcode8XY4((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0005:
			{
				//Set VX -= VY
				opcode8XY5((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x0006:
			{
				//Set VX >>= 1;
				opcode8XY6((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0007:
			{
				//Set VX = VY - VX
				opcode8XY7((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
				break;
			}
			case 0x000E:
			{
				//Set VX <<= 1
				opcode8XYE((opcode & 0x0F00) >> 8);
				break;
			}
		}
		break;
	}
	case 0x9000:
	{
		//Conditional opcode skip (if VX != VY)
		opcode9XYN((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		break;
	}
	case 0xA000:
	{
		//Sets I = NNN
		opcodeANNN(opcode & 0x0FFF);
		break;
	}
	case 0xB000:
	{
		//Jumps to NNN + V0
		opcodeBNNN(opcode & 0x0FFF);
		break;
	}
	case 0xC000:
	{
		//Sets VX = rand()&NN
		opcodeCXNN((opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	}
	case 0xD000:
	{
		//Draw sprite VX, VY from I
		//set VF = 1 if a set pixel is unset, else 0
		opcodeDXYN((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, opcode & 0x000F);
		break;
	}
	case 0xE000:
	{
		switch (opcode & 0x00FF)
		{
			case 0x009E:
			{
				//Conditional opcode skip (if key() == VX)
				opcodeEX9E((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x00A1:
			{
				//Conditional opcode skip (if key() !== VX)
				opcodeEXA1((opcode & 0x0F00) >> 8);
				break;
			}
		}
		break;
	}
	case 0xF000:
	{
		switch (opcode & 0x00FF)
		{
			case 0x0007:
			{
				//Set VX = delayTimer
				opcodeFX07((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x000A:
			{
				//cin>>VX //stop operation until input recieved
				opcodeFX0A((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0015:
			{
				//Sets delayTimer = VX
				opcodeFX15((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0018:
			{
				//Sets soundTimer = VX
				opcodeFX18((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x001E:
			{
				//Sets I += VX
				opcodeFX1E((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0029:
			{
				//Sets I to the location of font character in memory
				opcodeFX29((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0033:
			{
				//Stores decimal representation of VX in I
				opcodeFX33((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0055:
			{
				//Stores V0 to VX to memory at I
				opcodeFX55((opcode & 0x0F00) >> 8);
				break;
			}
			case 0x0065:
			{
				//Fills V0 to VX with memory from I
				opcodeFX65((opcode & 0x0F00) >> 8);
				break;
			}
		}
		break;
		}
	}

}

void Opcode::opcode00E0()
{
	//Clear Screen
	chipWindow.clearScreen();
}

void Opcode::opcode00EE()
{
	//Return from subroutine
	memoryPointer = chipStack.top();
	chipStack.pop();
}

void Opcode::opcode1NNN(short NNN)
{
	//Jump to address NNN
	memoryPointer = NNN;
}

void Opcode::opcode2NNN(short NNN)
{
	//Call subroutine at address NNN
	chipStack.push(memoryPointer);
	memoryPointer = NNN;
}

void Opcode::opcode3XNN(int x, int NN)
{
	//Conditional opcode skip (if VX == NN)
	if (registers[x] == NN)
	{
		memoryPointer += 2;
	}
}

void Opcode::opcode4XNN(int x, int NN)
{
	//Conditional opcode skip (if VX != NN)
	if (registers[x] != NN)
	{
		memoryPointer += 2;
	}
}

void Opcode::opcode5XYN(int x, int y)
{
	//Conditional opcode skip (if VX == VY)
	if (registers[x] == registers[y])
	{
		memoryPointer += 2;
	}
}

void Opcode::opcode6XNN(int x, int nn)
{
	//Set VX = NN
	registers.at(x) = (uint8_t)nn;
}

void Opcode::opcode7XNN(int x, int nn)
{
	//Set VX += NN
	registers.at(x) += nn;
}


void Opcode::opcode8XY0(int x, int y)
{
	//Set VX = VY
	registers.at(x) = registers.at(y);
}


void Opcode::opcode8XY1(int x, int y)
{
	//Set VX |= VY
	registers.at(x) |= registers.at(y);
}

void Opcode::opcode8XY2(int x, int y)
{
	//Set VX &= VY
	registers.at(x) &= registers.at(y);
}

void Opcode::opcode8XY3(int x, int y)
{
	//Set VX ^= VY
	registers.at(x) ^= registers.at(y);
}

void Opcode::opcode8XY4(int x, int y)
{
	//Set VX += VY
	if (registers.at(x) + registers.at(y) > 0xFF)
	{
		registers.at(0xF) = 1;
	}
	else
	{
		registers.at(0xF) = 0;
	}

	registers.at(x) += registers.at(y);
}

void Opcode::opcode8XY5(int x, int y)
{
	//Set VX -= VY
	if (registers.at(x) > registers.at(y))
	{
		registers.at(0xF) = 1;
	}
	else
	{
		registers.at(0xF) = 0;
	}

	registers.at(x) -= registers.at(y);
}

void Opcode::opcode8XY6(int x)
{
	//Set VX >>= 1
	if ((registers.at(x) & 1) == 1)
	{
		registers.at(0xF) = 1;
	}
	else
	{
		registers.at(0xF) = 0;
	}

	registers.at(x) >>= 1;
}

void Opcode::opcode8XY7(int x, int y)
{
	//Set VX = VY - VX
	if (registers.at(y) > registers.at(x))
	{
		registers.at(0xF) = 1;
	}
	else
	{
		registers.at(0xF) = 0;
	}

	registers.at(x) -= registers.at(y);

	registers.at(x) = registers.at(y) - registers.at(x);
}

void Opcode::opcode8XYE(int x)
{
	//Set VX <<= 1
	if (((registers.at(x) & 0x80) >> 7) == 1)
	{
		registers.at(0xF) = 1;
	}
	else
	{
		registers.at(0xF) = 0;
	}

	registers.at(x) <<= 1;
}

void Opcode::opcode9XY0(int x, int y)
{
	//Conditional opcode skip (if VX != VY)
	if (registers[x] != registers[y])
	{
		memoryPointer += 2;
	}
}

void Opcode::opcodeANNN(int nnn)
{
	//Set I = NNN
	I = nnn;
}

void Opcode::opcodeBNNN(int nnn)
{
	//Jump to NNN + V0
	memoryPointer = nnn + registers[0];
}

void Opcode:: opcodeCXNN(int x, int nn)
{
	//Set VX = rand() & NN
	registers.at(x) = rand() & nn;
}

void Opcode::opcodeDXYN(int x, int y, int n)
{
	//Draw sprite at I to X Y coordinates
	chipWindow.DrawSprite(Sprite(I, n).toVector(), registers[x], registers[y], n);
}

void Opcode::opcodeEX9E(int x)
{
	//Skips next instruction if key x is down

	if (keysDown.at(registers[x]) == 1)
	{
		memoryPointer += 2;
		keysDown.at(registers[x]) = 0;
	}

}

void Opcode::opcodeEXA1(int x)
{
	//Skips next instruction if key x is not down

	if (keysDown.at(registers[x]) == 0)
	{
		memoryPointer += 2;
		keysDown.at(registers[x]) = 0;
	}
}

void Opcode::opcodeFX07(int x)
{
	//Sets VX to the value of the delay timer
	registers[x] = delayTimer;
}

void Opcode::opcodeFX0A(int x)
{
	//Stop operations until key input stored into VX
	bool keyFound = false;
	for(int i = 0; i < 16 && !keyFound; i++)
	{
		if (keysDown[i] == 1)
		{
			keyFound = true;
			registers[x] = i;
			keysDown[i] = 0;
		}
	}
	
	if (!keyFound)
	{
		memoryPointer -= 2;
	}
}

void Opcode::opcodeFX15(int x)
{
	//sets the delay timer to VX
	delayTimer = registers[x];
}

void Opcode::opcodeFX18(int x)
{
	//sets the sound timer to VX
	soundTimer = registers[x];
}

void Opcode::opcodeFX1E(int x)
{
	//Adds VX to I
	I += registers[x];
}

void Opcode::opcodeFX29(int x)
{
	//Set I to position in memory of X Font Character
	I = registers.at(x) * 5;
}

void Opcode::opcodeFX33(int x)
{
	//Stores decimal representation of VX at I

	chipMemory.writeMemory(I, (byte)(registers.at(x) / 100));
	chipMemory.writeMemory(I + 1, (byte)((registers.at(x) / 10) % 10));
	chipMemory.writeMemory(I + 2, (byte)(registers.at(x)  % 10));

}

void Opcode::opcodeFX55(int x)
{
	//stores data from registers V0 to VX in memory at address I

	for (int i = 0; i <= x; i++)
	{	
		chipMemory.writeMemory(I + i, registers[i]);
	}

}

void Opcode::opcodeFX65(int x)
{
	//copies data from memory at address I into registers V0 to VX
	for (int i = 0; i <= x; i++)
	{
		registers[i] = chipMemory.readMemory(I + i);
	}

}