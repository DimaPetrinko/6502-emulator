#pragma once

#include "CpuTests/CpuTests.h"

struct StaIndYTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaIndY_Works);
		RUN_TEST(StaIndY_IncreasesProgramCounterBy2);
		RUN_TEST(StaIndY_SetsValueToTheReadByte);
		RUN_TEST(StaIndY_Takes6Cycles);
		RUN_TEST(StaIndY_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaIndY_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaIndY_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaIndY_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, 0x00);
		mBus->WriteByte(0x0029, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->a = value;
		mCpu->Clock();

		uint8_t v = mBus->ReadByte(0x0300);
		ASSERT_EQUAL(value, mBus->ReadByte(0x0303), StaIndY_Works);
	}

	void StaIndY_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, 0x00);
		mBus->WriteByte(0x0029, 0x03);

		mCpu->Reset();
		mCpu->y = 3;
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StaIndY_IncreasesProgramCounterBy2);
	}

	void StaIndY_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaIndY_SetsValueToTheReadByte);
	}

	void StaIndY_Takes6Cycles()
	{
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(6, cycles, StaIndY_Takes6Cycles);
	}

	void StaIndY_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, 0x00);
		mBus->WriteByte(0x0029, 0x03);

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
		END_ASSERT(StaIndY_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaIndY_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, 0x00);
		mBus->WriteByte(0x0029, 0x03);

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
		END_ASSERT(StaIndY_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaIndY_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_indy);
		mBus->WriteByte(0x8001, 0x28);
		mBus->WriteByte(0x0028, 0x00);
		mBus->WriteByte(0x0029, 0x03);

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
		END_ASSERT(StaIndY_WithPositiveValue_DoesntSetAnyFlags);
	}
};
