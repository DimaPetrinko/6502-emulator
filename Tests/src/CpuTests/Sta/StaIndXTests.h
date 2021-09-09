#pragma once

#include "CpuTests/CpuTests.h"

struct StaIndXTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaIndX_Works);
		RUN_TEST(StaIndX_WhenAddressWraps_Works);
		RUN_TEST(StaIndX_IncreasesProgramCounterBy2);
		RUN_TEST(StaIndX_SetsValueToTheReadByte);
		RUN_TEST(StaIndX_Takes6Cycles);
		RUN_TEST(StaIndX_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaIndX_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaIndX_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaIndX_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002b, 0x00);
		mBus->WriteByte(0x002c, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0300), StaIndX_Works);
	}

	void StaIndX_WhenAddressWraps_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0004, 0x00);
		mBus->WriteByte(0x0005, 0x03);

		mCpu->Reset();
		mCpu->x = 220;
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0300), StaIndX_WhenAddressWraps_Works);
	}

	void StaIndX_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002b, 0x00);
		mBus->WriteByte(0x002c, 0x03);

		mCpu->Reset();
		mCpu->x = 3;
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StaIndX_IncreasesProgramCounterBy2);
	}

	void StaIndX_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaIndX_SetsValueToTheReadByte);
	}

	void StaIndX_Takes6Cycles()
	{
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(6, cycles, StaIndX_Takes6Cycles);
	}

	void StaIndX_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002b, 0x00);
		mBus->WriteByte(0x002c, 0x03);

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
		END_ASSERT(StaIndX_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaIndX_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002b, 0x00);
		mBus->WriteByte(0x002c, 0x03);

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
		END_ASSERT(StaIndX_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaIndX_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indx);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x002b, 0x00);
		mBus->WriteByte(0x002c, 0x03);

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
		END_ASSERT(StaIndX_WithPositiveValue_DoesntSetAnyFlags);
	}
};
