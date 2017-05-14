#pragma once

#ifndef INPUTH
#define INPUTH

#include "Main.h"

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

void readInput()
{
	if (GetKeyState('1') < 0) {
		keysDown[0] = 1;
	}
	else {
		keysDown[0] = 0;
	}

	if (GetKeyState('2') < 0) {
		keysDown[1] = 1;
	}
	else {
		keysDown[1] = 0;
	}

	if (GetKeyState('3') < 0) {
		keysDown[2] = 1;
	}
	else {
		keysDown[2] = 0;
	}

	if (GetKeyState('4') < 0) {
		keysDown[3] = 1;
	}
	else {
		keysDown[3] = 0;
	}

	if (GetKeyState('Q') < 0) {
		keysDown[4] = 1;
	}
	else {
		keysDown[4] = 0;
	}

	if (GetKeyState('W') < 0) {
		keysDown[5] = 1;
	}
	else {
		keysDown[5] = 0;
	}

	if (GetKeyState('E') < 0) {
		keysDown[6] = 1;
	}
	else {
		keysDown[6] = 0;
	}

	if (GetKeyState('R') < 0) {
		keysDown[7] = 1;
	}
	else {
		keysDown[7] = 0;
	}

	if (GetKeyState('A') < 0) {
		keysDown[8] = 1;
	}
	else {
		keysDown[8] = 0;
	}

	if (GetKeyState('S') < 0) {
		keysDown[9] = 1;
	}
	else {
		keysDown[9] = 0;
	}

	if (GetKeyState('D') < 0) {
		keysDown[10] = 1;
	}
	else {
		keysDown[10] = 0;
	}

	if (GetKeyState('F') < 0) {
		keysDown[11] = 1;
	}
	else {
		keysDown[11] = 0;
	}

	if (GetKeyState('Z') < 0) {
		keysDown[12] = 1;
	}
	else {
		keysDown[12] = 0;
	}

	if (GetKeyState('X') < 0) {
		keysDown[13] = 1;
	}
	else {
		keysDown[13] = 0;
	}

	if (GetKeyState('C') < 0) {
		keysDown[14] = 1;
	}
	else {
		keysDown[14] = 0;
	}

	if (GetKeyState('V') < 0) {
		keysDown[15] = 1;
	}
	else {
		keysDown[15] = 0;
	}
}


#endif // !INPUTH
