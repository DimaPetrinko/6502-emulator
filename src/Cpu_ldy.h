#include "Cpu.h"

void Cpu::LdyIm()
{
	auto c = ClocksCounter(&mCycles);
	SetRegister(y, ReadByte(pc++));
}

void Cpu::LdyZp()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyZpX()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress += x;
	mCycles--;
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyAbs()
{
	auto c = ClocksCounter(&mCycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	SetRegister(y, ReadByte(address));
}

void Cpu::LdyAbsX()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	address += x; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) mCycles--;
	SetRegister(y, ReadByte(address));
}