#pragma once

#include "CpuTests/CpuTests.h"

struct LdaZpTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(LdaZp_Works);
		RUN_TEST(LdaZp_Takes3Cycles);
		RUN_TEST(LdaZp_SetsNegativeFlag);
		RUN_TEST(LdaZp_SetsZeroFlag);
	}

	void LdaZp_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zp);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->a, LdaZp_Works);
	}

	void LdaZp_Takes3Cycles()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zp);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, value);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(3, cycles, LdaZp_Takes3Cycles);
	}

	void LdaZp_SetsNegativeFlag()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, lda_zp);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, value);

		mCpu->Reset();
		mCpu->n = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->n, LdaZp_SetsNegativeFlag);
	}

	void LdaZp_SetsZeroFlag()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, lda_zp);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, value);

		mCpu->Reset();
		mCpu->z = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->z, LdaZp_SetsZeroFlag);
	}
};
