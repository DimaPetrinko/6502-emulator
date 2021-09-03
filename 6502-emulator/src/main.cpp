#include <iostream>
#include <vector>
#include "Components/Cpu/Cpu.h"
#include "Components/Bus.h"
#include "Components/Memory/Ram.h"
#include "Components/Memory/Rom.h"

void CreateRomPreloadData(std::vector<uint8_t>& preloadData)
{
}

int main()
{
	#ifdef DEBUG
	std::cout << "Debug\n";
	#endif
	std::vector<uint8_t> romData;
	CreateRomPreloadData(romData);

	Cpu* cpu;
	Bus* bus;
	Ram* ram;
	Rom* rom;

	bus = new Bus();
	cpu = new Cpu(bus);	
	ram = new Ram();
	rom = new Rom("res/program.bin");

	bus->ConnectDevice(ram, {0x0000, 0x3fff});
	bus->ConnectDevice(rom, {0x8000, 0xffff});

	bus->WriteByte(0x0042, 0x13);
	bus->WriteByte(0x000d, 0xff);
	bus->WriteByte(0x0060, 0x08);
	bus->WriteByte(0x0061, 0x80);

	cpu->Reset();
	cpu->Clock(100);

	delete cpu;
	delete bus;
	delete ram;
	delete rom;
}