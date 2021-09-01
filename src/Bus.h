#pragma once

#include <stdint.h>
#include <unordered_map>
#include "Device.h"

struct AddressRange
{
	uint16_t From;
	uint16_t To;
};

class Bus
{
private:
	std::unordered_map<Device*, AddressRange> mDevicesMap;

public:
	Bus();
	~Bus();

	void ConnectDevice(Device* device, AddressRange range);
	Device* GetDevice(uint16_t address) const;

	uint8_t ReadByte(uint16_t address) const;
	uint16_t ReadWord(uint16_t address) const;
	void WriteByte(uint16_t address, uint8_t data) const;
};