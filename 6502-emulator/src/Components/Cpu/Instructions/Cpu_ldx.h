#include "Components/Cpu/Cpu.h"

void Cpu::LdxIm()
{
	auto c = ClocksCounter(&Cycles);
	Value = ReadByte(pc++);
	SetRegister(x, Value);
}

void Cpu::LdxZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	SetRegister(x, ReadByte(zeroPageAddress));
}

void Cpu::LdxZpY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += y;
	Cycles++;
	SetRegister(x, ReadByte(zeroPageAddress));
}

void Cpu::LdxAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	SetRegister(x, ReadByte(address));
}

void Cpu::LdxAbsY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	Value = address;
	address += y; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	SetRegister(x, ReadByte(address));
}