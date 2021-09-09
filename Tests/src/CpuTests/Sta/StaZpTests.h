#pragma once

#include "CpuTests/CpuTests.h"

struct StaZpTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StaZp_Works);
		RUN_TEST(StaZp_IncreasesProgramCounterBy2);
		RUN_TEST(StaZp_SetsValueToTheReadByte);
		RUN_TEST(StaZp_Takes3Cycles);
		RUN_TEST(StaZp_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StaZp_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StaZp_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StaZp_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->a = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0028), StaZp_Works);
	}

	void StaZp_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->a = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StaZp_IncreasesProgramCounterBy2);
	}

	void StaZp_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, sta_zp);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StaZp_SetsValueToTheReadByte);
	}

	void StaZp_Takes3Cycles()
	{
		mBus->WriteByte(0x8000, sta_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(3, cycles, StaZp_Takes3Cycles);
	}

	void StaZp_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sta_zp);
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
		END_ASSERT(StaZp_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StaZp_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sta_zp);
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
		END_ASSERT(StaZp_WithZeroValue_DoesntSetAnyFlags);
	}

	void StaZp_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sta_zp);
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
		END_ASSERT(StaZp_WithPositiveValue_DoesntSetAnyFlags);
	}
};
