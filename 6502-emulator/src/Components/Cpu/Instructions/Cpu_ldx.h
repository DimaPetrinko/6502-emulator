#include "Components/Cpu/Cpu.h"

void Cpu::LdxIm()
{
	auto c = ClocksCounter(&mCycles);
	SetRegister(x, ReadByte(pc++));
}

void Cpu::LdxZp()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	SetRegister(x, ReadByte(zeroPageAddress));
}

void Cpu::LdxZpY()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress += y;
	mCycles++;
	SetRegister(x, ReadByte(zeroPageAddress));
}

void Cpu::LdxAbs()
{
	auto c = ClocksCounter(&mCycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	SetRegister(x, ReadByte(address));
}

void Cpu::LdxAbsY()
{
	auto c = ClocksCounter(&mCycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	address += y; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) mCycles++;
	SetRegister(x, ReadByte(address));
}