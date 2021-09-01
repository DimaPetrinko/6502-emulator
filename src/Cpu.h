#pragma once

#include <stdint.h>
#include "CpuConstants.h"
#include "Bus.h"

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

	void LdaIm();
	void LdaZp();
	void Nop();
};