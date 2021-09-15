#pragma once

#include "CpuTests/CpuTests.h"

struct StyAbsTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StyAbs_Works);
		RUN_TEST(StyAbs_IncreasesProgramCounterBy3);
		RUN_TEST(StyAbs_SetsValueToTheReadWord);
		RUN_TEST(StyAbs_Takes4Cycles);
		RUN_TEST(StyAbs_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StyAbs_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StyAbs_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StyAbs_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = value;

		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0328), StyAbs_Works);
	}

	void StyAbs_IncreasesProgramCounterBy3()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(3, pc, StyAbs_IncreasesProgramCounterBy3);
	}

	void StyAbs_SetsValueToTheReadWord()
	{
		uint16_t value = 0x0328;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, value);
		mBus->WriteByte(0x8002, value >> 8);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StyAbs_SetsValueToTheReadWord);
	}

	void StyAbs_Takes4Cycles()
	{
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, StyAbs_Takes4Cycles);
	}

	void StyAbs_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StyAbs_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StyAbs_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StyAbs_WithZeroValue_DoesntSetAnyFlags);
	}

	void StyAbs_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_abs);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->y = value;
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(StyAbs_WithPositiveValue_DoesntSetAnyFlags);
	}
};