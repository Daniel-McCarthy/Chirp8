#pragma once

using namespace std;

#include <vector>
#include <fstream>
#include <iostream>

#pragma once
#ifndef  MEMH
#define MEMH

class Memory
{
private:
	uint8_t memory[0x1000];//4096 bytes

public:
	Memory()
	{

	}

	~Memory()
	{

	}

	uint8_t readMemory(int address)
	{
		return memory[address];
	}

	vector<uint8_t> readMemory(int address, int bytes)
	{
		vector<uint8_t> returnMemory;

		for (int i = 0; i < bytes; i++)
		{
			returnMemory.push_back(memory[address + i]);
		}

		return returnMemory;
	}

	bool writeMemory(int address, uint8_t byte)
	{
		if (address >= 0 && address < 4096)
		{
			memory[address] = byte;

			if (memory[address] == byte)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool writeMemory(int address, short shortVal)
	{
		if (address >= 0 && address < 4096)
		{
			memory[address] = (uint8_t)(shortVal & 0xFF00 >> 4);
			memory[address + 1] = (uint8_t)(shortVal & 0x00FF);

			if (memory[address] == (shortVal & 0xFF00 >> 4) && memory[address+1] == (shortVal & 0x00FF))
			{
				return true;
			}
		}

		return false;
	}

	bool writeMemory(int address, vector<uint8_t> bytes)
	{
		if (address >= 0 && address + bytes.size() < 4096)
		{
			for (int i = 0; i < (int)bytes.size(); i++)
			{
				memory[address + i] = bytes[i];

				if (memory[address + i] != bytes[i])
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}

	bool loadRom(string path)
	{
		ifstream inputFile(path, ios::binary|ios::ate);
		
		if (inputFile.is_open())
		{
			int fileLength = (int)inputFile.tellg();
			inputFile.seekg(0, ios::beg);
			vector<char> rom(fileLength);
			inputFile.read(rom.data(), fileLength);

			if (rom.size() + 0x200 <= 4096)
			{
				int address = 0x200;
				for (int i = 0; i < (int)rom.size(); i++)
				{
					writeMemory(address + i, (uint8_t)rom.at(i));
				}
			}
			else
			{
				cout << "Error: Rom too large. It does not fit in Chip 8's memory." << endl;
				return false;
			}
		}
		{
			cout << "Error: Rom does not exist." << endl;
			return false;
		}

		inputFile.close();

		return true;
	}
		
	void loadFontSprites()
	{
		//Load Font Character 0
		writeMemory(0, (uint8_t)0xF0);
		writeMemory(1, (uint8_t)0x90);
		writeMemory(2, (uint8_t)0x90);
		writeMemory(3, (uint8_t)0x90);
		writeMemory(4, (uint8_t)0xF0);

		//Load Font Character 1
		writeMemory(5, (uint8_t)0x20);
		writeMemory(6, (uint8_t)0x60);
		writeMemory(7, (uint8_t)0x20);
		writeMemory(8, (uint8_t)0x20);
		writeMemory(9, (uint8_t)0x70);

		//Load Font Character 2
		writeMemory(10, (uint8_t)0xF0);
		writeMemory(11, (uint8_t)0x10);
		writeMemory(12, (uint8_t)0xF0);
		writeMemory(13, (uint8_t)0x80);
		writeMemory(14, (uint8_t)0xF0);

		//Load Font Character 3
		writeMemory(15, (uint8_t)0xF0);
		writeMemory(16, (uint8_t)0x80);
		writeMemory(17, (uint8_t)0xF0);
		writeMemory(18, (uint8_t)0x10);
		writeMemory(19, (uint8_t)0xF0);

		//Load Font Character 4
		writeMemory(20, (uint8_t)0x90);
		writeMemory(21, (uint8_t)0x90);
		writeMemory(22, (uint8_t)0xF0);
		writeMemory(23, (uint8_t)0x10);
		writeMemory(24, (uint8_t)0x10);

		//Load Font Character 0
		writeMemory(25, (uint8_t)0xF0);
		writeMemory(26, (uint8_t)0x90);
		writeMemory(27, (uint8_t)0x90);
		writeMemory(28, (uint8_t)0x90);
		writeMemory(29, (uint8_t)0xF0);

		//Load Font Character 5
		writeMemory(30, (uint8_t)0xF0);
		writeMemory(31, (uint8_t)0x80);
		writeMemory(32, (uint8_t)0xF0);
		writeMemory(33, (uint8_t)0x10);
		writeMemory(34, (uint8_t)0xF0);

		//Load Font Character 6
		writeMemory(35, (uint8_t)0xF0);
		writeMemory(36, (uint8_t)0x80);
		writeMemory(37, (uint8_t)0xF0);
		writeMemory(38, (uint8_t)0x90);
		writeMemory(39, (uint8_t)0xF0);

		//Load Font Character 7
		writeMemory(40, (uint8_t)0xF0);
		writeMemory(41, (uint8_t)0x10);
		writeMemory(42, (uint8_t)0x20);
		writeMemory(43, (uint8_t)0x40);
		writeMemory(44, (uint8_t)0x40);

		//Load Font Character 8
		writeMemory(45, (uint8_t)0xF0);
		writeMemory(46, (uint8_t)0x90);
		writeMemory(47, (uint8_t)0xF0);
		writeMemory(48, (uint8_t)0x90);
		writeMemory(49, (uint8_t)0xF0);

		//Load Font Character 9
		writeMemory(50, (uint8_t)0xF0);
		writeMemory(51, (uint8_t)0x90);
		writeMemory(52, (uint8_t)0xF0);
		writeMemory(53, (uint8_t)0x10);
		writeMemory(54, (uint8_t)0xF0);

		//Load Font Character A
		writeMemory(55, (uint8_t)0xF0);
		writeMemory(56, (uint8_t)0x90);
		writeMemory(57, (uint8_t)0xF0);
		writeMemory(58, (uint8_t)0x90);
		writeMemory(59, (uint8_t)0x90);

		//Load Font Character B
		writeMemory(60, (uint8_t)0xE0);
		writeMemory(61, (uint8_t)0x90);
		writeMemory(62, (uint8_t)0xE0);
		writeMemory(63, (uint8_t)0x90);
		writeMemory(64, (uint8_t)0xE0);

		//Load Font Character C
		writeMemory(65, (uint8_t)0xF0);
		writeMemory(66, (uint8_t)0x80);
		writeMemory(67, (uint8_t)0x80);
		writeMemory(68, (uint8_t)0x80);
		writeMemory(69, (uint8_t)0xF0);

		//Load Font Character D
		writeMemory(70, (uint8_t)0xE0);
		writeMemory(71, (uint8_t)0x90);
		writeMemory(72, (uint8_t)0x90);
		writeMemory(73, (uint8_t)0x90);
		writeMemory(74, (uint8_t)0xE0);

		//Load Font Character E
		writeMemory(75, (uint8_t)0xF0);
		writeMemory(76, (uint8_t)0x80);
		writeMemory(77, (uint8_t)0xF0);
		writeMemory(78, (uint8_t)0x80);
		writeMemory(79, (uint8_t)0xF0);

		//Load Font Character F
		writeMemory(80, (uint8_t)0xF0);
		writeMemory(81, (uint8_t)0x80);
		writeMemory(82, (uint8_t)0xF0);
		writeMemory(83, (uint8_t)0x80);
		writeMemory(84, (uint8_t)0x80);

	}

};

#endif