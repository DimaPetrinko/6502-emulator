#include "Cpu/Cpu.h"

void Cpu::StxZp()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	WriteByte(zeroPageAddress, x);
}

void Cpu::StxZpY()
{
	auto c = ClocksCounter(&Cycles);
	uint8_t zeroPageAddress = ReadByte(pc++);
	Value = zeroPageAddress;
	zeroPageAddress += y;
	Cycles++;
	WriteByte(zeroPageAddress, x);
}

void Cpu::StxAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	WriteByte(address, x);
}

void Cpu::AddStxFunctions()
{
	mInstructionFunctions[stx_zp] = &Cpu::StxZp;
	mInstructionFunctions[stx_zpy] = &Cpu::StxZpY;
	mInstructionFunctions[stx_abs] = &Cpu::StxAbs;
}