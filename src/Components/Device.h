#pragma once

#include <stdint.h>

constexpr uint16_t MemoryChipSize = 0x8000;

class Device
{
public:
	virtual uint8_t ReadData(uint16_t address) const = 0;
	virtual void WriteData(uint16_t address, uint8_t data) = 0;
};