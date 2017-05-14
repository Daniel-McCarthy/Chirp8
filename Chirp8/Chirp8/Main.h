
#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Windows.h>
#include <gl\GL.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <vector>

#include "Memory.h"
#include "Window.h"



#pragma once
#ifndef  MAINH
#define MAINH

	extern Memory chipMemory; //4096 bytes
	extern vector<uint8_t> registers;
	extern stack<short> chipStack;
	extern short I;
	extern Window chipWindow;
	extern uint8_t delayTimer;
	extern uint8_t soundTimer;
	extern int memoryPointer;
	extern  vector<uint8_t> keysDown;
	
#endif // ! MAINH