#pragma once

#include "Cpu/Cpu.h"
#include "Bus.h"
#include "Memory/Ram.h"
#include "Memory/Rom.h"


struct CpuTests
{
	void Test()
	{
		Bus* bus = new Bus();
		Cpu* cpu = new Cpu(bus);
		Ram* ram = new Ram();
		Rom* rom = new Rom();

		bus->ConnectDevice(ram, {0x0000, 0x3fff});
		bus->ConnectDevice(rom, {0x8000, 0xffff});



		delete cpu;
		delete bus;
		delete ram;
		delete rom;
	}
};