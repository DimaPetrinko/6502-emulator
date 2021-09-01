#include "Cpu.h"

Cpu::Cpu(Bus* bus) : mBus(bus) {}

Cpu::~Cpu() {}

void Cpu::Reset()
{
	pc = mBus->ReadWord(ResetLocation);
	sp = StackEnd - StackStart;
}

void Cpu::Clock()
{
	uint8_t instruction = mBus->ReadByte(pc++);
	mCycles--;

	switch (instruction)
	{
	case lda_im:
		LdaIm();
		break;
	case lda_zp:
		LdaZp();
		break;
	case nop:
		Nop();
		break;
	
	default:
		printf("Undefined opeeration! %x\n", instruction);
		break;
	}
}

void Cpu::Clock(int times)
{
	mCycles = times;
	while(mCycles > 0) Clock();
}

void Cpu::LdaIm()
{
	a = mBus->ReadByte(pc++);
	mCycles--;
	z = a == 0;
	n = a & (1 << 7);
}

void Cpu::LdaZp()
{
	uint8_t zeroPageAddress = mBus->ReadByte(pc++);
	mCycles--;
	a = mBus->ReadByte(zeroPageAddress);
	mCycles--;
	z = a == 0;
	n = a & (1 << 7);
}

void Cpu::Nop()
{
	mCycles--;
}