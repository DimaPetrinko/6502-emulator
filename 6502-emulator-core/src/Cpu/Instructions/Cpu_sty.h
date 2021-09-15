#include "Cpu/Cpu.h"

void Cpu::StyZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	WriteByte(zeroPageAddress, y);
}

void Cpu::StyZpX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	WriteByte(zeroPageAddress, y);
}

void Cpu::StyAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	WriteByte(address, y);
}