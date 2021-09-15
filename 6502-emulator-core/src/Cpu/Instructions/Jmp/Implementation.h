#include "Cpu/Cpu.h"

void Cpu::JmpAbs()
{
	auto c = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	Value = address;
	pc = address;
}

void Cpu::JmpInd()
{
	auto cl = ClocksCounter(&Cycles);
	uint16_t address = ReadWord(pc);
	pc += 2;
	Value = address;
	uint16_t realAddress;
	#ifdef INCLUDE_JMP_IND_BUG
	if ((uint8_t)address == 0xff)
	{
		uint8_t lo = ReadByte(address);
		uint8_t hi = ReadByte(address - 0xff);
		realAddress = (hi << 8) | lo;
	}
	else realAddress = ReadWord(address);
	#else
	realAddress = ReadWord(address);
	#endif
	pc = realAddress;
}

void Cpu::AddJmpFunctions()
{
	mInstructionFunctions[jmp_abs] = &Cpu::JmpAbs;
	mInstructionFunctions[jmp_ind] = &Cpu::JmpInd;
}