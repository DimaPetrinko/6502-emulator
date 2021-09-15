#pragma once

#include "CpuTests/CpuTests.h"

struct StyZpTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(StyZp_Works);
		RUN_TEST(StyZp_IncreasesProgramCounterBy2);
		RUN_TEST(StyZp_SetsValueToTheReadByte);
		RUN_TEST(StyZp_Takes3Cycles);
		RUN_TEST(StyZp_WithNegativeValue_DoesntSetAnyFlags);
		RUN_TEST(StyZp_WithZeroValue_DoesntSetAnyFlags);
		RUN_TEST(StyZp_WithPositiveValue_DoesntSetAnyFlags);
	}

	void StyZp_Works()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->y = value;
		mCpu->Clock();

		ASSERT_EQUAL(value, mBus->ReadByte(0x0028), StyZp_Works);
	}

	void StyZp_IncreasesProgramCounterBy2()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		mCpu->y = value;
		uint16_t pc = mCpu->pc;
		
		mCpu->Clock();
		pc = mCpu->pc - pc;

		ASSERT_EQUAL(2, pc, StyZp_IncreasesProgramCounterBy2);
	}

	void StyZp_SetsValueToTheReadByte()
	{
		uint8_t value = 0x28;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, value);

		mCpu->Reset();
		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, StyZp_SetsValueToTheReadByte);
	}

	void StyZp_Takes3Cycles()
	{
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;
		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(3, cycles, StyZp_Takes3Cycles);
	}

	void StyZp_WithNegativeValue_DoesntSetAnyFlags()
	{
		uint8_t value = -42;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StyZp_WithNegativeValue_DoesntSetAnyFlags);
	}

	void StyZp_WithZeroValue_DoesntSetAnyFlags()
	{
		uint8_t value = 0;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StyZp_WithZeroValue_DoesntSetAnyFlags);
	}

	void StyZp_WithPositiveValue_DoesntSetAnyFlags()
	{
		uint8_t value = 42;
		mBus->WriteByte(0x8000, sty_zp);
		mBus->WriteByte(0x8001, 0x28);

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
		END_ASSERT(StyZp_WithPositiveValue_DoesntSetAnyFlags);
	}
};