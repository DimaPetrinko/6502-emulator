#include "Cpu.h"

#include <iostream>
#include "Cpu/CpuConstants.h"
#include "Cpu/Instructions/Lda/Cpu_lda.h"
#include "Cpu/Instructions/Ldx/Cpu_ldx.h"
#include "Cpu/Instructions/Ldy/Cpu_ldy.h"
#include "Cpu/Instructions/Sta/Cpu_sta.h"
#include "Cpu/Instructions/Stx/Cpu_stx.h"
#include "Cpu/Instructions/Sty/Cpu_sty.h"
#include "Cpu/Instructions/Adc/Cpu_adc.h"

Cpu::Cpu(Bus* bus) : mBus(bus)
{
	AddAdcFunctions();

	AddLdaFunctions();
	AddLdxFunctions();
	AddLdyFunctions();

	AddStaFunctions();
	AddStxFunctions();
	AddStyFunctions();
	
	mInstructionFunctions[nop] = &Cpu::Nop;
}

Cpu::~Cpu() {}

void Cpu::Reset()
{
	Cycles = 7;
	pc = ReadWord(ResetLocation);
	sp = StackEnd - StackStart;

	a = 0;
	x = 0;
	y = 0;

	c = 0;
	z = 0;
	i = 0;
	d = 0;
	b = 0;
	v = 0;
	n = 0;
}

void Cpu::Clock()
{
	Instruction = ReadByte(pc++);

	void (Cpu::*instructionFunction)() = mInstructionFunctions[Instruction];
	if (instructionFunction == nullptr) printf("Undefined operation! %x\n", Instruction);
	else (this->*instructionFunction)();
}

void Cpu::Nop()
{
	auto c = ClocksCounter(&Cycles);
	Cycles++;
}

void Cpu::SetRegister(uint8_t& r, uint8_t value)
{
	r = value;
	z = r == 0;
	n = r >> 7;
}

void Cpu::SetAWithArithmeticFlags(uint8_t value, uint16_t result)
{
	c = result >> 8;
	v = (value + c) >> 7 == n && n != (result & 0xff) >> 7;

	SetRegister(a, result);
}

bool Cpu::AddressPageWillBeCrossed(uint8_t lo, uint8_t hi, uint8_t offset) const
{
	hi = lo;
	lo += offset;
	return lo < hi;
}

uint8_t Cpu::ReadByte(uint16_t address)
{
	Cycles++;
	return mBus->ReadByte(address);
}

uint16_t Cpu::ReadWord(uint16_t address)
{
	Cycles += 2;
	return mBus->ReadWord(address);
}

uint16_t Cpu::ReadWord(uint16_t address, uint8_t* outLo, uint8_t* outHi)
{
	Cycles += 2;
	return mBus->ReadWord(address, outLo, outHi);
}

void Cpu::WriteByte(uint16_t address, uint8_t value)
{
	Cycles++;
	mBus->WriteByte(address, value);
}

void Cpu::WriteWord(uint16_t address, uint16_t value)
{
	Cycles += 2;
	mBus->WriteWord(address, value);
}