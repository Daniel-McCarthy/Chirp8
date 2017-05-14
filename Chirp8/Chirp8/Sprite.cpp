#include "Sprite.h"
#include "Binary.h"
#include "Main.h"

Sprite::Sprite()
{
}

Sprite::Sprite(string spriteString)
{
	int index = 0;

	while (spriteString.length() > 8 * 15)
	{
		if (spriteString.length() % 8 != 0)
		{
			int toKeep = (int)(spriteString.length() / 8);
			spriteString = spriteString.substr(0, toKeep);

		}
	}

	while (index < (int)spriteString.length())
	{
		string binary = spriteString.substr(index, (spriteString.length() - index >= 8) ? 8 : spriteString.length() - index);
		data.push_back(Binary::toInt(binary));
		index += 8;
	}
}

Sprite::Sprite(vector<int> spriteData)
{
	while (spriteData.size() > 15)
	{
		spriteData.pop_back();
	}

	data = spriteData;
}

Sprite::Sprite(short address, int height)
{
	for (int i = 0; i < height; i++)
	{
		data.push_back(chipMemory.readMemory(address + i));
	}
}

Sprite::~Sprite()
{
}

string Sprite::toString()
{
	for (int i = 0; i < (int)data.size(); i++)
	{

	}
	return NULL;
}

vector<int> Sprite::toVector()
{
	return data;
}

