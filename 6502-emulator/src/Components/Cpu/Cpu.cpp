#include "Cpu.h"

#include <iostream>
#include "Components/Cpu/Instructions/Cpu_lda.h"
#include "Components/Cpu/Instructions/Cpu_ldx.h"
#include "Components/Cpu/Instructions/Cpu_ldy.h"

Cpu::Cpu(Bus* bus) : mBus(bus) {}

Cpu::~Cpu() {}

void Cpu::Reset()
{
	mCycles = 7;
	pc = ReadWord(ResetLocation);
	sp = StackEnd - StackStart;
	a = 0;
	x = 0;
	y = 0;
}

void Cpu::Clock()
{
	mInstruction = ReadByte(pc++);

	switch (mInstruction)
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

	case nop:
		Nop();
		break;
	
	default:
		printf("Undefined opeeration! %x\n", mInstruction);
		break;
	}

	// visualize registers and maybe data?
}

void Cpu::ShowState()
{
	printf("Cycles:      %i\n", mCycles);
	printf("instruction: %x\n", mInstruction);
	printf("pc:          %x\n", pc);
	printf("sp:          %x\n", sp);
	printf("a:           %x\n", a);
	printf("x:           %x\n", x);
	printf("y:           %x\n", y);
	printf("c z i d b o n\n");
	printf("%i %i %i %i %i %i %i \n", c, z, i, d, b, o, n);
}

void Cpu::Nop()
{
	auto c = ClocksCounter(&mCycles);
	mCycles++;
}

void Cpu::SetRegister(uint8_t& r, uint8_t value)
{
	r = value;
	z = r == 0;
	n = r & (1 << 7);
}

bool Cpu::AddressPageWillBeCrossed(uint8_t lo, uint8_t hi, uint8_t offset) const
{
	hi = lo;
	lo += offset;
	return lo < hi;
}

uint8_t Cpu::ReadByte(uint16_t address)
{
	mCycles++;
	return mBus->ReadByte(address);
}

uint16_t Cpu::ReadWord(uint16_t address)
{
	mCycles += 2;
	return mBus->ReadWord(address);
}

uint16_t Cpu::ReadWord(uint16_t address, uint8_t* outLo, uint8_t* outHi)
{
	mCycles += 2;
	return mBus->ReadWord(address, outLo, outHi);
}