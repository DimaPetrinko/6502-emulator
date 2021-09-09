#pragma once

#include "CpuTests/CpuTests.h"

struct LdaImTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(LdaIm_Works);
		RUN_TEST(LdaIm_Takes2Cycles);
		RUN_TEST(LdaIm_SetsNegativeFlag);
		RUN_TEST(LdaIm_SetsZeroFlag);
	}

	void LdaIm_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_im);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->a, LdaIm_Works);
	}

	void LdaIm_Takes2Cycles()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_im);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(2, cycles, LdaIm_Takes2Cycles);
	}

	void LdaIm_SetsNegativeFlag()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, lda_im);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->n = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->n, LdaIm_SetsNegativeFlag);
	}

	void LdaIm_SetsZeroFlag()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, lda_im);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->z = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->z, LdaIm_SetsZeroFlag);
	}
};
