#include <iostream>
#include <vector>
#include "Components/Cpu/Cpu.h"
#include "Components/Bus.h"
#include "Components/Memory/Ram.h"
#include "Components/Memory/Rom.h"

void CreateRomPreloadData(std::vector<uint8_t>& preloadData)
{
	// lda
	preloadData.push_back(lda_im);
	preloadData.push_back(0x28);
	preloadData.push_back(lda_zp);
	preloadData.push_back(0x42);
	preloadData.push_back(lda_zpx);
	preloadData.push_back(0x0d);
	preloadData.push_back(lda_abs);
	preloadData.push_back(0x02);
	preloadData.push_back(0x80);
	preloadData.push_back(lda_absx);
	preloadData.push_back(0xf0);
	preloadData.push_back(0x80);
	preloadData.push_back(lda_indx);
	preloadData.push_back(0x60);
	preloadData.push_back(lda_indy);
	preloadData.push_back(0x60);

	// ldx
	preloadData.push_back(ldx_im);
	preloadData.push_back(0x28);
	preloadData.push_back(ldx_zp);
	preloadData.push_back(0x42);
	preloadData.push_back(ldx_zpy);
	preloadData.push_back(0x0d);
	preloadData.push_back(ldx_abs);
	preloadData.push_back(0x02);
	preloadData.push_back(0x80);
	preloadData.push_back(ldx_absy);
	preloadData.push_back(0xf0);
	preloadData.push_back(0x80);

	// ldy
	preloadData.push_back(ldy_im);
	preloadData.push_back(0x28);
	preloadData.push_back(ldy_zp);
	preloadData.push_back(0x42);
	preloadData.push_back(ldy_zpx);
	preloadData.push_back(0x0d);
	preloadData.push_back(ldy_abs);
	preloadData.push_back(0x02);
	preloadData.push_back(0x80);
	preloadData.push_back(ldy_absx);
	preloadData.push_back(0xf0);
	preloadData.push_back(0x80);

	size_t emptyCount = MemoryChipSize - 6;
	for (size_t i = preloadData.size(); i < emptyCount; i++)
	{
		preloadData.push_back(nop);
	}

	preloadData.push_back(nop); // 0xfffa - maskable interrupt
	preloadData.push_back(nop); // 0xfffb   handler
	preloadData.push_back(0x00); // 0xfffc - reset
	preloadData.push_back(0x80); // 0xfffd   location
	preloadData.push_back(nop); // 0xfffe - brk/interrupt
	preloadData.push_back(nop); // 0xffff   handler

	preloadData[0x80f0] = 0xf1;
}

int main()
{
	std::vector<uint8_t> romData;
	CreateRomPreloadData(romData);

	Cpu* cpu;
	Bus* bus;
	Ram* ram;
	Rom* rom;

	bus = new Bus();
	cpu = new Cpu(bus);	
	ram = new Ram();
	rom = new Rom(std::move(romData));

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