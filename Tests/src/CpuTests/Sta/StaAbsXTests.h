#pragma once

#include "CpuTests/CpuTests.h"

struct StaAbsXTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaAbsX_Works);
		RUN_TEST(StaAbsX_IncreasesProgramCounterBy3);
		RUN_TEST(StaAbsX_SetsValueToTheReadWord);
		RUN_TEST(StaAbsX_Takes5Cycles);
		RUN_TEST(StaAbsX_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbsX_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaAbsX_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaAbsX_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x032b), StaAbsX_Works);
	}

	void StaAbsX_IncreasesProgramCounterBy3()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(3, pc, StaAbsX_IncreasesProgramCounterBy3);
	}

	void StaAbsX_SetsValueToTheReadWord()
	{
		uint16_t value = 0x0328;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, value);
		mBus->WriteByte(0x8002, value >> 8);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaAbsX_SetsValueToTheReadWord);
	}

	void StaAbsX_Takes5Cycles()
	{
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(5, cycles, StaAbsX_Takes5Cycles);
	}

	void StaAbsX_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
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
		END_ASSERT(StaAbsX_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaAbsX_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
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
		END_ASSERT(StaAbsX_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaAbsX_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_absx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x8002, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
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
		END_ASSERT(StaAbsX_WithPositiveValue_DoesntSetAnyFlags);
	}
};
