using namespace std;

#include <string>
#include <vector>
#include <sstream>
#include <SDL.h>

#pragma once
#ifndef  SPRITEH
#define SPRITEH
class Sprite
{
public:
	Sprite();
	Sprite(string spriteString);
	Sprite(vector<int> spriteData);
	Sprite(vector<string> spriteString);
	Sprite(short address, int height);
	~Sprite();
	string toString();
	vector<int> toVector();

private:
	vector<int> data;
};
#endif
