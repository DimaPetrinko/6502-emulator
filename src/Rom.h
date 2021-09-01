#pragma once

#include <stdint.h>
#include <vector>
#include "Device.h"

class Rom : public Device
{
private:
	uint8_t mCells[MemoryChipSize];
public:
	Rom(const std::vector<uint8_t>& preloadedData);
	Rom(const std::vector<uint8_t>& preloadedData, uint16_t address);
	~Rom();

	uint8_t ReadData(uint16_t address) const override;
	void WriteData(uint16_t address, uint8_t data) override;
};