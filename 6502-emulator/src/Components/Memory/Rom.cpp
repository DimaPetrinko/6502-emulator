#include "Rom.h"

#include <iostream>
#include <fstream>


Rom::Rom()
{
	for (size_t i = 0; i < MemoryChipSize; i++) mCells[i] = 0xea;

	mCells[0x7ffc] = 0x00;
	mCells[0x7ffd] = 0x80;
}

Rom::~Rom()
{
}

void Rom::Load(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file)
	{
		size_t i = 0;
		while (!file.eof())
		{
			file >> mCells[i++];
		}
	} 
	else std::cout << "Could not open the file " << filePath << std::endl;
	file.close();
}

uint8_t Rom::ReadData(uint16_t address) const
{
	return mCells[address];
}

void Rom::WriteData(uint16_t address, uint8_t data)
{
	std::cout << "The rom cannot be written to\n";
}