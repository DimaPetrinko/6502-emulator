#pragma once

#include "CpuTests/CpuTests.h"

struct StxZpYTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StxZpY_Works);
		RUN_TEST(StxZpY_WhenAddressWraps_Works);
		RUN_TEST(StxZpY_IncreasesProgramCounterBy2);
		RUN_TEST(StxZpY_SetsValueToTheReadByte);
		RUN_TEST(StxZpY_Takes4Cycles);
		RUN_TEST(StxZpY_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StxZpY_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StxZpY_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StxZpY_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zpy);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->x = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x002b), StxZpY_Works);
	}

	void StxZpY_WhenAddressWraps_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zpy);
		mBus->WriteByte(0x8001, 60);

		mCpu->Reset();
		mCpu->y = 200;
		mCpu->x = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(4), StxZpY_WhenAddressWraps_Works);
	}

	void StxZpY_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zpy);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->x = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StxZpY_IncreasesProgramCounterBy2);
	}

	void StxZpY_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, stx_zpy);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StxZpY_SetsValueToTheReadByte);
	}

	void StxZpY_Takes4Cycles()
	{
		mBus->WriteByte(0x8000, stx_zpy);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, StxZpY_Takes4Cycles);
	}

	void StxZpY_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, stx_zpy);
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
		END_ASSERT(StxZpY_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StxZpY_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, stx_zpy);
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
		END_ASSERT(StxZpY_WithZeroValue_DoesntSetAnyFlags);
	}

	void StxZpY_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, stx_zpy);
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
		END_ASSERT(StxZpY_WithPositiveValue_DoesntSetAnyFlags);
	}
};