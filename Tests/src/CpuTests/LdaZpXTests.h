#pragma once

#include "CpuTests.h"

struct LdaZpXTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(LdaZpX_Works);
		RUN_TEST(LdaZpX_WorksWith0X);
		RUN_TEST(LdaZpX_WorksWith0xffX);
		RUN_TEST(LdaZpX_Takes4Cycles);
		RUN_TEST(LdaZpX_SetsNegativeFlag);
		RUN_TEST(LdaZpX_SetsZeroFlag);
	}

	void LdaZpX_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0029, value);

		mCpu->Reset();
		mCpu->x = 1;

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->a, LdaZpX_Works);
	}

	void LdaZpX_WorksWith0X()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, value);

		mCpu->Reset();
		mCpu->x = 0;

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->a, LdaZpX_WorksWith0X);
	}

	void LdaZpX_WorksWith0xffX()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0027, value);

		mCpu->Reset();
		mCpu->x = 0xff;

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->a, LdaZpX_WorksWith0xffX);
	}

	void LdaZpX_Takes4Cycles()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002a, value);

		mCpu->Reset();
		mCpu->x = 2;
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, LdaZpX_Takes4Cycles);
	}

	void LdaZpX_SetsNegativeFlag()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002a, value);

		mCpu->Reset();
		mCpu->x = 2;
		mCpu->n = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->n, LdaZpX_SetsNegativeFlag);
	}

	void LdaZpX_SetsZeroFlag()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, lda_zpx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002a, value);

		mCpu->Reset();
		mCpu->x = 2;
		mCpu->z = 0;
		
		mCpu->Clock();

		ASSERT_EQUAL(1, mCpu->z, LdaZpX_SetsZeroFlag);
	}
};
