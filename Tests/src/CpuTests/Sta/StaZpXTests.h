#pragma once

#include "CpuTests/CpuTests.h"

struct StaZpXTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaZpX_Works);
		RUN_TEST(StaZpX_WhenAddressWraps_Works);
		RUN_TEST(StaZpX_IncreasesProgramCounterBy2);
		RUN_TEST(StaZpX_SetsValueToTheReadByte);
		RUN_TEST(StaZpX_Takes4Cycles);
		RUN_TEST(StaZpX_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaZpX_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaZpX_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaZpX_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x002b), StaZpX_Works);
	}

	void StaZpX_WhenAddressWraps_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 60);

		mCpu->Reset();
		mCpu->x = 200;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(4), StaZpX_WhenAddressWraps_Works);
	}

	void StaZpX_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StaZpX_IncreasesProgramCounterBy2);
	}

	void StaZpX_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaZpX_SetsValueToTheReadByte);
	}

	void StaZpX_Takes4Cycles()
	{
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(4, cycles, StaZpX_Takes4Cycles);
	}

	void StaZpX_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StaZpX_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaZpX_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StaZpX_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaZpX_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zpx);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StaZpX_WithPositiveValue_DoesntSetAnyFlags);
	}
};
