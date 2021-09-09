#pragma once

#include "CpuTests/CpuTests.h"

struct StaAbsTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaAbs_Works);
		RUN_TEST(StaAbs_IncreasesProgramCounterBy3);
		RUN_TEST(StaAbs_SetsValueToTheReadWord);
		RUN_TEST(StaAbs_Takes4Cycles);
		RUN_TEST(StaAbs_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbs_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbs_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaAbs_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->a = value;

		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0328), StaAbs_Works);
	}

	void StaAbs_IncreasesProgramCounterBy3()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(3, pc, StaAbs_IncreasesProgramCounterBy3);
	}

	void StaAbs_SetsValueToTheReadWord()
	{
		uint16_t value = 0x0328;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, value);
		mBus->WriteByte(0x8002, value >> 8);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaAbs_SetsValueToTheReadWord);
	}

	void StaAbs_Takes4Cycles()
	{
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, StaAbs_Takes4Cycles);
	}

	void StaAbs_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->a = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StaAbs_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaAbs_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->a = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StaAbs_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaAbs_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->a = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StaAbs_WithPositiveValue_DoesntSetAnyFlags);
	}
};
