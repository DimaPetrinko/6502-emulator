#include "Cpu.h"

#include <iostream>
#include "Components/Cpu/CpuConstants.h"
#include "Components/Cpu/Instructions/Cpu_lda.h"
#include "Components/Cpu/Instructions/Cpu_ldx.h"
#include "Components/Cpu/Instructions/Cpu_ldy.h"
#include "Components/Cpu/Instructions/Cpu_adc.h"

Cpu::Cpu(Bus* bus) : mBus(bus) {}

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

	switch (Instruction)
	{
	case lda_im:
		LdaIm();
		break;
	case lda_zp:
		LdaZp();
		break;
	case lda_zpx:
		LdaZpX();
		break;
	case lda_abs:
		LdaAbs();
		break;
	case lda_absx:
		LdaAbsX();
		break;
	case lda_absy:
		LdaAbsY();
		break;
	case lda_indx:
		LdaIndX();
		break;
	case lda_indy:
		LdaIndY();
		break;

	case ldx_im:
		LdxIm();
		break;
	case ldx_zp:
		LdxZp();
		break;
	case ldx_zpy:
		LdxZpY();
		break;
	case ldx_abs:
		LdxAbs();
		break;
	case ldx_absy:
		LdxAbsY();
		break;

	case ldy_im:
		LdyIm();
		break;
	case ldy_zp:
		LdyZp();
		break;
	case ldy_zpx:
		LdyZpX();
		break;
	case ldy_abs:
		LdyAbs();
		break;
	case ldy_absx:
		LdyAbsX();
		break;

	case adc_im:
		AdcIm();
		break;
	case adc_zp:
		AdcZp();
		break;
	case adc_zpx:
		AdcZpX();
		break;
	case adc_abs:
		AdcAbs();
		break;
	case adc_absx:
		AdcAbsX();
		break;
	case adc_absy:
		AdcAbsY();
		break;
	case adc_indx:
		AdcIndX();
		break;
	case adc_indy:
		AdcIndY();
		break;

	case nop:
		Nop();
		break;
	
	default:
		printf("Undefined opeeration! %x\n", Instruction);
		break;
	}
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
	n = r & (1 << 7);
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