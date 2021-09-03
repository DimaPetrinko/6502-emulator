#include <iostream>
#include <vector>
#include "Components/Cpu/CpuVisualizer.h"
#include "Components/Cpu/Cpu.h"
#include "Components/Bus.h"
#include "Components/Memory/Ram.h"
#include "Components/Memory/Rom.h"

void CreateRomPreloadData(std::vector<uint8_t>& preloadData)
{
}

int main()
{
	std::vector<uint8_t> romData;
	CreateRomPreloadData(romData);

	CpuVisualizer visualizer;

	Bus* bus = new Bus();
	Cpu* cpu = new Cpu(bus);
	Ram* ram = new Ram();
	Rom* rom = new Rom("res/program.bin");

	bus->ConnectDevice(ram, {0x0000, 0x3fff});
	bus->ConnectDevice(rom, {0x8000, 0xffff});

	bus->WriteByte(0x0042, 0x13);
	bus->WriteByte(0x000d, 0xff);
	bus->WriteByte(0x0060, 0x08);
	bus->WriteByte(0x0061, 0x80);

	cpu->Reset();

	char exitChar;
	while (1)
	{
		visualizer.Visualize(cpu);
		exitChar = std::cin.get();
		if (exitChar == 'q') break;
		cpu->Clock();
	}

	delete cpu;
	delete bus;
	delete ram;
	delete rom;
}