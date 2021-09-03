#include "Components/Cpu/Cpu.h"

void Cpu::LdaIm()
{
	auto c = ClocksCounter(&Cycles);
	SetRegister(a, ReadByte(pc++));
}

void Cpu::LdaZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	SetRegister(a, ReadByte(zeroPageAddress));
}

void Cpu::LdaZpX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress += x;
	Cycles++;
	SetRegister(a, ReadByte(zeroPageAddress));
}

void Cpu::LdaAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	SetRegister(a, ReadByte(address));
}

void Cpu::LdaAbsX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	address += x; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, x)) Cycles++;
	SetRegister(a, ReadByte(address));
}

void Cpu::LdaAbsY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	address += y; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	SetRegister(a, ReadByte(address));
}

void Cpu::LdaIndX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress += x;
	Cycles++;
	uint16_t realAddress = ReadWord(zeroPageAddress);
	SetRegister(a, ReadByte(realAddress));
}

void Cpu::LdaIndY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	zeroPageAddress;
	uint8_t lo, hi;
	uint16_t realAddress = ReadWord(zeroPageAddress, &lo, &hi);
	realAddress += y;
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	SetRegister(a, ReadByte(realAddress));
}