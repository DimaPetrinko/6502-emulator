#include <iostream>
#include <vector>
#include "Cpu.h"
#include "Bus.h"
#include "Ram.h"
#include "Rom.h"

Cpu* mCpu;
Bus* mBus;
Ram* mRam;
Rom* mRom;

void CreateRomPreloadData(std::vector<uint8_t>& preloadData)
{
	preloadData.push_back(lda_im);
	preloadData.push_back(0x28);
	preloadData.push_back(lda_zp);
	preloadData.push_back(0x42);
	preloadData.push_back(0xb5);

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
}

int main()
{
	std::vector<uint8_t> romData;
	CreateRomPreloadData(romData);

	mBus = new Bus();
	mCpu = new Cpu(mBus);
	
	mRam = new Ram();
	mRom = new Rom(std::move(romData));

	mBus->ConnectDevice(mRam, {0x0000, 0x3fff});
	mBus->ConnectDevice(mRom, {0x8000, 0xffff});

	mBus->WriteByte(0x0042, 0x13);

	mCpu->Reset();
	mCpu->Clock(10);

	delete mCpu;
	delete mBus;
	delete mRam;
	delete mRom;
}