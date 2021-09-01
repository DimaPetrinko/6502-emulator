#pragma once

#include <stdint.h>
#include "CpuConstants.h"
#include "Bus.h"

class ClocksCounter
{
private:
	int mStartClocks;
	int mEndClocks;
	int mClocksElapsed;
	int* mCurrentClocks;

public:
	ClocksCounter(int* clocks) :
		mStartClocks(*clocks),
		mEndClocks(0),
		mClocksElapsed(0),
		mCurrentClocks(clocks)
	{}

	~ClocksCounter()
	{
		mEndClocks = *mCurrentClocks;
		mClocksElapsed = mStartClocks - mEndClocks + 1;
		printf("Elapsed %i clocks\n", mClocksElapsed);
	}

};

class Cpu
{
private:
	Bus* mBus;

	uint16_t pc;
	uint8_t sp;

	uint8_t a;
	uint8_t x;
	uint8_t y;

	uint8_t c : 1;
	uint8_t z : 1;
	uint8_t i : 1;
	uint8_t d : 1;
	uint8_t b : 1;
	uint8_t o : 1;
	uint8_t n : 1;

	int mCycles;

public:
	Cpu(Bus* bus);
	~Cpu();

	void Reset();
	void Clock();
	void Clock(int times);

private:
	void LdaIm();
	void LdaZp();
	void LdaZpX();
	void LdaAbs();
	void LdaAbsX();
	void LdaAbsY();
	void LdaIndX();
	void LdaIndY();

	void LdxIm();
	void LdxZp();
	void LdxZpY();
	void LdxAbs();
	void LdxAbsY();

	void Nop();

private:
	void SetRegister(uint8_t& r, uint8_t value);
	bool AddressPageWillBeCrossed(uint8_t lo, uint8_t hi, uint8_t offset) const;

	uint8_t ReadByte(uint16_t address);
	uint16_t ReadWord(uint16_t address);
	uint16_t ReadWord(uint16_t address, uint8_t* outLo, uint8_t* outHi);
};