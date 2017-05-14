#pragma once
using namespace std;

#include <string>

class Binary
{
public:

	static int8_t getBit(int8_t number, int index)
	{
		return (number & (1 << index)) >> index;
	}

	static int toInt(string binary)
	{
		int spriteValue = 0;
		for (int i = 0; i < (int)binary.length() - 1; i++)
		{
			if (binary[i] != '0')
			{
				spriteValue |= 1;
			}
			spriteValue <<= 1;
		}
		return spriteValue;
	}

	static string toBinary(int8_t number)
	{
		string binary = "";

		for (int i = 7; i > -1; i--)
		{
			binary += to_string(getBit(number, i));
		
		}

		return binary;
	}
	/*
	static string toBinary(int number)
	{
		string binary = "";

		for (int i = 31; i > -1; i--)
		{
			binary += to_string(getBit(number, i));

		}

		return binary;
	}
	*/
};

