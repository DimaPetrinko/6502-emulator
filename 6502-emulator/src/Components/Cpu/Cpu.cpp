#include "Cpu.h"

#include <iostream>
#include "Components/Cpu/CpuConstants.h"
#include "Components/Cpu/Instructions/Cpu_lda.h"
#include "Components/Cpu/Instructions/Cpu_ldx.h"
#include "Components/Cpu/Instructions/Cpu_ldy.h"
#include "Components/Cpu/Instructions/Cpu_adc.h"

Cpu::Cpu(Bus* bus) : mBus(bus)
{
	mInstructionFunctions[lda_im] = &Cpu::LdaIm;
	mInstructionFunctions[lda_zp] = &Cpu::LdaZp;
	mInstructionFunctions[lda_zpx] = &Cpu::LdaZpX;
	mInstructionFunctions[lda_abs] = &Cpu::LdaAbs;
	mInstructionFunctions[lda_absx] = &Cpu::LdaAbsX;
	mInstructionFunctions[lda_absy] = &Cpu::LdaAbsY;
	mInstructionFunctions[lda_indx] = &Cpu::LdaIndX;
	mInstructionFunctions[lda_indy] = &Cpu::LdaIndY;

	mInstructionFunctions[ldx_im] = &Cpu::LdxIm;
	mInstructionFunctions[ldx_zp] = &Cpu::LdxZp;
	mInstructionFunctions[ldx_zpy] = &Cpu::LdxZpY;
	mInstructionFunctions[ldx_abs] = &Cpu::LdxAbs;
	mInstructionFunctions[ldx_absy] = &Cpu::LdxAbsY;
	
	mInstructionFunctions[ldy_im] = &Cpu::LdyIm;
	mInstructionFunctions[ldy_zp] = &Cpu::LdyZp;
	mInstructionFunctions[ldy_zpx] = &Cpu::LdyZpX;
	mInstructionFunctions[ldy_abs] = &Cpu::LdyAbs;
	mInstructionFunctions[ldy_absx] = &Cpu::LdyAbsX;

	mInstructionFunctions[adc_im] = &Cpu::AdcIm;
	mInstructionFunctions[adc_zp] = &Cpu::AdcZp;
	mInstructionFunctions[adc_zpx] = &Cpu::AdcZpX;
	mInstructionFunctions[adc_abs] = &Cpu::AdcAbs;
	mInstructionFunctions[adc_absx] = &Cpu::AdcAbsX;
	mInstructionFunctions[adc_absy] = &Cpu::AdcAbsY;
	mInstructionFunctions[adc_indx] = &Cpu::AdcIndX;
	mInstructionFunctions[adc_indy] = &Cpu::AdcIndY;
	
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
	v = value >> 7 == n && n != (result & 0xff) >> 7;

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