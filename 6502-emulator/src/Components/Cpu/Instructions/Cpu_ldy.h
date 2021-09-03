#include "Components/Cpu/Cpu.h"

void Cpu::LdyIm()
{
	auto c = ClocksCounter(&Cycles);
	SetRegister(y, ReadByte(pc++));
}

void Cpu::LdyZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyZpX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress += x;
	Cycles++;
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	SetRegister(y, ReadByte(address));
}

void Cpu::LdyAbsX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	address += x; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	SetRegister(y, ReadByte(address));
}