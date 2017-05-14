#pragma once

#ifndef WINDOWH
#define WINDOWH

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Window
{
public:
	Window() {}

	Window(string title, int xPos, int yPos, int width, int height);
	Window(string title, int width, int height);
	~Window();
	void DrawPixel(int x, int y, bool enabled);
	bool XorPixel(int x, int y);
	void DrawSprite(vector<int> spriteData, int x, int y);
	void DrawSprite(vector<int> spriteData, int x, int y, int n);
	void clearScreen();
	void Update();
	SDL_Renderer* sdlRenderer;
	SDL_Texture* texture;
	Uint32* canvas;
	SDL_Window* sdlWindow;
	SDL_GLContext sdlGLContext;
	SDL_Surface* sdlSurface;

};

#endif