#include "Cpu/Cpu.h"

void Cpu::AdcIm()
{
	auto cl = ClocksCounter(&Cycles);
	Value = AddWithCarry(pc++);
}

void Cpu::AdcZp()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	AddWithCarry(zeroPageAddress);
}

void Cpu::AdcZpX()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	AddWithCarry(zeroPageAddress);
}

void Cpu::AdcAbs()
{
	auto cl = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	AddWithCarry(address);
}

void Cpu::AdcAbsX()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	Value = address;
	address += x; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, x)) Cycles++;
	AddWithCarry(address);
}

void Cpu::AdcAbsY()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t lo, hi;
	uint16_t address = ReadWord(pc, &lo, &hi);
	pc += 2;
	Value = address;
	address += y; // another cycle?
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	AddWithCarry(address);
}

void Cpu::AdcIndX()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	uint16_t realAddress = ReadWord(zeroPageAddress);
	AddWithCarry(realAddress);
}

void Cpu::AdcIndY()
{
	auto cl = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	uint8_t lo, hi;
	uint16_t realAddress = ReadWord(zeroPageAddress, &lo, &hi);
	realAddress += y;
	if (AddressPageWillBeCrossed(lo, hi, y)) Cycles++;
	AddWithCarry(realAddress);
}

uint8_t Cpu::AddWithCarry(uint16_t address)
{
	uint8_t value = ReadByte(address);
	uint16_t result = a + value + c;
	SetAWithArithmeticFlags(value, result);
	return value;
}