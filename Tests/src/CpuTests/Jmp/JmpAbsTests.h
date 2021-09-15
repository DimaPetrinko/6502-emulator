#pragma once

#include "CpuTests/CpuTests.h"

struct JmpAbsTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(JmpAbs_Works);
		RUN_TEST(JmpAbs_SetsValueToTheReadWord);
		RUN_TEST(JmpAbs_Takes3Cycles);
		RUN_TEST(JmpAbs_DoesntSetAnyFlags);
	}

	void JmpAbs_Works()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, jmp_abs);
		mBus->WriteByte(0x8001, lo);
		mBus->WriteByte(0x8002, hi);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->pc, JmpAbs_Works);
	}

	void JmpAbs_SetsValueToTheReadWord()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, jmp_abs);
		mBus->WriteByte(0x8001, lo);
		mBus->WriteByte(0x8002, hi);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->Value, JmpAbs_SetsValueToTheReadWord);
	}

	void JmpAbs_Takes3Cycles()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, jmp_abs);
		mBus->WriteByte(0x8001, lo);
		mBus->WriteByte(0x8002, hi);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(3, cycles, JmpAbs_Takes3Cycles);
	}

	void JmpAbs_DoesntSetAnyFlags()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		mBus->WriteByte(0x8000, jmp_abs);
		mBus->WriteByte(0x8001, lo);
		mBus->WriteByte(0x8002, hi);

		mCpu->Reset();
		
		mCpu->Clock();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(JmpAbs_DoesntSetAnyFlags);
	}
};