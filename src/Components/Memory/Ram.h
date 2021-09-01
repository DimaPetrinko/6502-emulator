#pragma once

#include <stdint.h>
#include "Components/Device.h"

class Ram : public Device
{
private:
	uint8_t mCells[MemoryChipSize];
public:
	Ram();
	~Ram();

	uint8_t ReadData(uint16_t address) const override;
	void WriteData(uint16_t address, uint8_t data) override;
};