#include "Rom.h"

#include <iostream>

Rom::Rom(const std::vector<uint8_t>& preloadedData) : Rom(preloadedData, 0x0000)
{}

Rom::Rom(const std::vector<uint8_t>& preloadedData, uint16_t address)
{
	for (size_t i = address; i < MemoryChipSize; i++)
	{
		mCells[i] = i < preloadedData.size() ? preloadedData[i] : 0x00;
	}
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