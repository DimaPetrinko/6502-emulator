#include "Ram.h"

Ram::Ram()
{
}

Ram::~Ram()
{
}

uint8_t Ram::ReadData(uint16_t address) const
{
	return mCells[address];
}

void Ram::WriteData(uint16_t address, uint8_t data)
{
	mCells[address] = data;
}