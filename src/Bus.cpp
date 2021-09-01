#include "Bus.h"

Bus::Bus()
{
}

Bus::~Bus()
{
}

void Bus::ConnectDevice(Device* device, AddressRange range)
{
	mDevicesMap[device] = range;
}

Device* Bus::GetDevice(uint16_t address) const
{
	for (auto &&p : mDevicesMap)
	{
		AddressRange range = p.second;
		if (address >= range.From && address <= range.To)
		return p.first;
	}
	return nullptr;
}

uint8_t Bus::ReadByte(uint16_t address) const
{
	Device* device = GetDevice(address);
	if (!device) return 0x00;

	AddressRange range = mDevicesMap.at(device);
	return device->ReadData(address - range.From);
}

uint16_t Bus::ReadWord(uint16_t address) const
{
	uint8_t lo = ReadByte(address);
	uint8_t hi = ReadByte(address + 1);
	return (hi << 8) | lo;
}

void Bus::WriteByte(uint16_t address, uint8_t data) const
{
	Device* device = GetDevice(address);
	if (!device) return;

	AddressRange range = mDevicesMap.at(device);
	device->WriteData(address - range.From, data);
}