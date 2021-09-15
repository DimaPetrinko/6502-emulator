#pragma once

#include "CpuTests/CpuTests.h"

struct StxZpTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StxZp_Works);
		RUN_TEST(StxZp_IncreasesProgramCounterBy2);
		RUN_TEST(StxZp_SetsValueToTheReadByte);
		RUN_TEST(StxZp_Takes3Cycles);
		RUN_TEST(StxZp_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StxZp_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StxZp_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StxZp_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->x = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0028), StxZp_Works);
	}

	void StxZp_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->x = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StxZp_IncreasesProgramCounterBy2);
	}

	void StxZp_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StxZp_SetsValueToTheReadByte);
	}

	void StxZp_Takes3Cycles()
	{
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(3, cycles, StxZp_Takes3Cycles);
	}

	void StxZp_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StxZp_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StxZp_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StxZp_WithZeroValue_DoesntSetAnyFlags);
	}

	void StxZp_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StxZp_WithPositiveValue_DoesntSetAnyFlags);
	}
};