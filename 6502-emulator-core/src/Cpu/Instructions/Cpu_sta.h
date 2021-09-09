#include "Cpu/Cpu.h"

void Cpu::StaZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	WriteByte(zeroPageAddress, a);
}

void Cpu::StaZpX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	WriteByte(zeroPageAddress, a);
}

void Cpu::StaAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	WriteByte(address, a);
}

void Cpu::StaAbsX()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	address += x;
	Cycles++;
	WriteByte(address, a);
}

void Cpu::StaAbsY()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	address += y;
	Cycles++;
	WriteByte(address, a);
}

void Cpu::StaIndX()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += x;
	Cycles++;
	uint16_t realAddress = ReadWord(zeroPageAddress);
	WriteByte(realAddress, a);
}

void Cpu::StaIndY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	uint16_t realAddress = ReadWord(zeroPageAddress);
	realAddress += y;
	Cycles++;
	WriteByte(realAddress, a);
}