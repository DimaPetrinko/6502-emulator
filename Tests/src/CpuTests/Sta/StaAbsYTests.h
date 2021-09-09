#pragma once

#include "CpuTests/CpuTests.h"

struct StaAbsYTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaAbsY_Works);
		RUN_TEST(StaAbsY_IncreasesProgramCounterBy3);
		RUN_TEST(StaAbsY_SetsValueToTheReadWord);
		RUN_TEST(StaAbsY_Takes5Cycles);
		RUN_TEST(StaAbsY_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbsY_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbsY_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaAbsY_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x032b), StaAbsY_Works);
	}

	void StaAbsY_IncreasesProgramCounterBy3()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(3, pc, StaAbsY_IncreasesProgramCounterBy3);
	}

	void StaAbsY_SetsValueToTheReadWord()
	{
		uint16_t value = 0x0328;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, value);
		mBus->WriteByte(0x8002, value >> 8);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaAbsY_SetsValueToTheReadWord);
	}

	void StaAbsY_Takes5Cycles()
	{
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(5, cycles, StaAbsY_Takes5Cycles);
	}

	void StaAbsY_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
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
		END_ASSERT(StaAbsY_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaAbsY_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
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
		END_ASSERT(StaAbsY_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaAbsY_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
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
		END_ASSERT(StaAbsY_WithPositiveValue_DoesntSetAnyFlags);
	}
};
