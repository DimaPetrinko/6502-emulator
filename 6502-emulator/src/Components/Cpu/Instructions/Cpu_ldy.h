#include "Components/Cpu/Cpu.h"

void Cpu::LdyIm()
{
	auto c = ClocksCounter(&Cycles);
	Value = ReadByte(pc++);
	SetRegister(y, Value);
}

void Cpu::LdyZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyZpX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	SetRegister(y, ReadByte(zeroPageAddress));
}

void Cpu::LdyAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	SetRegister(y, ReadByte(address));
}

void Cpu::LdyAbsX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	Value = address;
	address += x; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	SetRegister(y, ReadByte(address));
}