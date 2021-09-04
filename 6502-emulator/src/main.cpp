#include <iostream>
#include <vector>
#include "Components/Cpu/CpuVisualizer.h"
#include "Components/Cpu/Cpu.h"
#include "Components/Bus.h"
#include "Components/Memory/Ram.h"
#include "Components/Memory/Rom.h"

int main()
{
	CpuVisualizer visualizer;

	Bus* bus = new Bus();
	Cpu* cpu = new Cpu(bus);
	Ram* ram = new Ram();
	Rom* rom = new Rom();
	// rom->Load("res/lda_test.bin");
	// rom->Load("res/ldx_test.bin");
	// rom->Load("res/ldy_test.bin");
	rom->Load("res/adc_test.bin");

	bus->ConnectDevice(ram, {0x0000, 0x3fff});
	bus->ConnectDevice(rom, {0x8000, 0xffff});

	bus->WriteByte(0x0000, 0x02);
	bus->WriteByte(0x0001, 0x03);
	bus->WriteByte(0x0002, 0x00);
	bus->WriteByte(0x0003, 0x80);

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