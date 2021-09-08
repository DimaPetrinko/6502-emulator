#pragma once

#include <stdint.h>
#include <string>
#include "Device.h"

class Rom : public Device
{
private:
	uint8_t mCells[MemoryChipSize];
public:
	Rom();
	~Rom();

	void Load(const std::string& filePath, uint16_t& outOffset);
	uint8_t ReadData(uint16_t address) const override;
	void WriteData(uint16_t address, uint8_t data) override;
};