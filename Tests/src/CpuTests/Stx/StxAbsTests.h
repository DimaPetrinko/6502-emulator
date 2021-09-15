#pragma once

#include "CpuTests/CpuTests.h"

struct StxAbsTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StxAbs_Works);
		RUN_TEST(StxAbs_IncreasesProgramCounterBy3);
		RUN_TEST(StxAbs_SetsValueToTheReadWord);
		RUN_TEST(StxAbs_Takes4Cycles);
		RUN_TEST(StxAbs_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StxAbs_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StxAbs_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StxAbs_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = value;

		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0328), StxAbs_Works);
	}

	void StxAbs_IncreasesProgramCounterBy3()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(3, pc, StxAbs_IncreasesProgramCounterBy3);
	}

	void StxAbs_SetsValueToTheReadWord()
	{
		uint16_t value = 0x0328;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, value);
		mBus->WriteByte(0x8002, value >> 8);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StxAbs_SetsValueToTheReadWord);
	}

	void StxAbs_Takes4Cycles()
	{
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, StxAbs_Takes4Cycles);
	}

	void StxAbs_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StxAbs_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StxAbs_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StxAbs_WithZeroValue_DoesntSetAnyFlags);
	}

	void StxAbs_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StxAbs_WithPositiveValue_DoesntSetAnyFlags);
	}
};