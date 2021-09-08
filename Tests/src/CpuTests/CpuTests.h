#pragma once

#include "Asserts.h"

#include "Cpu/CpuConstants.h"
#include "Cpu/Cpu.h"
#include "Bus.h"
#include "Memory/Ram.h"
#include "Memory/Rom.h"

struct CpuTests
{
	Bus* mBus;
	Cpu* mCpu;
	Device* mRam;
	Device* mRom;

	virtual void Setup()
	{
		mBus = new Bus();
		mCpu = new Cpu(mBus);
		mRam = new Ram();
		mRom = new Ram(); // to be able to write to it

		mBus->ConnectDevice(mRam, {0x0000, 0x3fff});
		mBus->ConnectDevice(mRom, {0x8000, 0xffff});

		mBus->WriteByte(0xfffc, 0x00);
		mBus->WriteByte(0xfffd, 0x80);
	}

	virtual void Cleanup()
	{
		delete mBus;
		delete mCpu;
		delete mRam;
		delete mRom;
	}

	virtual void RunAll() = 0;
};