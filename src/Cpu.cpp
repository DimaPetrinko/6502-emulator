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
	uint8_t instruction = ReadByte(pc++);

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

void Cpu::Nop()
{
	auto c = ClocksCounter(&mCycles);
	mCycles--;
}

void Cpu::SetRegister(uint8_t& r, uint8_t value)
{
	r = value;
	z = r == 0;
	n = r & (1 << 7);
}

bool Cpu::AddressPageWillBeCrossed(uint8_t lo, uint8_t hi, uint8_t offset) const
{
	hi = lo;
	lo += offset;
	return lo < hi;
}

uint8_t Cpu::ReadByte(uint16_t address)
{
	mCycles--;
	return mBus->ReadByte(address);
}

uint16_t Cpu::ReadWord(uint16_t address)
{
	mCycles -= 2;
	return mBus->ReadWord(address);
}

uint16_t Cpu::ReadWord(uint16_t address, uint8_t* outLo, uint8_t* outHi)
{
	mCycles -= 2;
	return mBus->ReadWord(address, outLo, outHi);
}