#include "Rom.h"

#include <iostream>
#include <fstream>


Rom::Rom(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file) file.read((char*)mCells, MemoryChipSize);
	else std::cout << "Could not open the file " << filePath << std::endl;
	file.close();
}

Rom::~Rom()
{
}

uint8_t Rom::ReadData(uint16_t address) const
{
	return mCells[address];
}

void Rom::WriteData(uint16_t address, uint8_t data)
{
	std::cout << "The rom cannot be written to\n";
}