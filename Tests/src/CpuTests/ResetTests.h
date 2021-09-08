#pragma once

#include "CpuTests.h"

struct ResetTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(Reset_Works);
		RUN_TEST(Reset_Takes9Cycles);
	}

	void Reset_Works()
	{
		mCpu->pc = 0xff;
		mCpu->sp = 0x7f;
		mCpu->a = 0xff;
		mCpu->x = 0xff;
		mCpu->y = 0xff;
		mCpu->c = 1;
		mCpu->z = 1;
		mCpu->i = 1;
		mCpu->d = 1;
		mCpu->b = 1;
		mCpu->v = 1;
		mCpu->n = 1;

		mCpu->Reset();

		BEGIN_ASSERT
		ADD_ASSERT_EQUAL(0x8000, mCpu->pc)
		ADD_ASSERT_EQUAL(0xff, mCpu->sp)
		ADD_ASSERT_EQUAL(0, mCpu->a)
		ADD_ASSERT_EQUAL(0, mCpu->x)
		ADD_ASSERT_EQUAL(0, mCpu->y)
		ADD_ASSERT_EQUAL(0, mCpu->c)
		ADD_ASSERT_EQUAL(0, mCpu->z)
		ADD_ASSERT_EQUAL(0, mCpu->i)
		ADD_ASSERT_EQUAL(0, mCpu->d)
		ADD_ASSERT_EQUAL(0, mCpu->b)
		ADD_ASSERT_EQUAL(0, mCpu->v)
		ADD_ASSERT_EQUAL(0, mCpu->n)
		END_ASSERT(Reset_Works);
	}

	void Reset_Takes9Cycles()
	{
		mCpu->Cycles = 0;

		mCpu->Reset();
		
		ASSERT_EQUAL(9, mCpu->Cycles, Reset_Takes9Cycles);
	}
};
