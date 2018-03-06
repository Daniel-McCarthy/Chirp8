#pragma once

#include <Windows.h>
#include <SDL.h>
#include <ctime>
#include <string>
#include <random>
#include <stack>
#include <vector>
#include <iostream>


using namespace std;

class Opcode
{
private:
public:


	Opcode();



	void selectOpcode(short opcode);

	//0NNN needs to be implemented

	void opcode00E0();

	void opcode00EE();

	void opcode1NNN(short NNN);

	void opcode2NNN(short NNN);

	void opcode3XNN(int x, int NN);

	void opcode4XNN(int x, int NN);

	void opcode5XYN(int x, int y);

	void opcode6XNN(int x, int nn);

	void opcode7XNN(int x, int nn);

	void opcode8XY0(int x, int y);

	void opcode8XY1(int x, int y);

	void opcode8XY2(int x, int y);

	void opcode8XY3(int x, int y);

	void opcode8XY4(int x, int y);

	void opcode8XY5(int x, int y);

	void opcode8XY6(int x);

	void opcode8XY7(int x, int y);

	void opcode8XYE(int x);

	void opcode9XY0(int x, int y);

	void opcodeANNN(int nnn);

	void opcodeBNNN(int nnn);

	void opcodeCXNN(int x, int nn);

	void opcodeDXYN(int x, int y, int n);

	void opcodeEX9E(int x);

	void opcodeEXA1(int x);

	void opcodeFX07(int x);

	void opcodeFX0A(int x);

	void opcodeFX15(int x);

	void opcodeFX18(int x);

	void opcodeFX1E(int x);

	void opcodeFX29(int x);

	void opcodeFX33(int x);

	void opcodeFX55(int x);

	void opcodeFX65(int x);
};


