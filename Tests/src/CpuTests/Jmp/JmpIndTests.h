#pragma once

#include "CpuTests/CpuTests.h"

struct JmpIndTests : public CpuTests
{
	void RunAll() override
	{
		RUN_TEST(JmpInd_Works);
		#ifdef INCLUDE_JMP_IND_BUG
		RUN_TEST(JmpInd_WhenAddressOnPageBoudary_RetainsOriginalBug);
		#endif
		RUN_TEST(JmpInd_SetsValueToTheReadWord);
		RUN_TEST(JmpInd_Takes5Cycles);
		RUN_TEST(JmpInd_DoesntSetAnyFlags);
	}

	void JmpInd_Works()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		uint16_t address = 0x0355;
		uint8_t addresLo = address;
		uint8_t addresHi = address >> 8;
		mBus->WriteByte(0x8000, jmp_ind);
		mBus->WriteByte(0x8001, addresLo);
		mBus->WriteByte(0x8002, addresHi);
		mBus->WriteByte(address, lo);
		mBus->WriteByte(address + 1, hi);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->pc, JmpInd_Works);
	}

	#ifdef INCLUDE_JMP_IND_BUG
	void JmpInd_WhenAddressOnPageBoudary_RetainsOriginalBug()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		uint16_t address = 0x03FF;
		uint16_t faultyMSBAddress = 0x0300;
		uint8_t addresLo = address;
		uint8_t addresHi = address >> 8;
		mBus->WriteByte(0x8000, jmp_ind);
		mBus->WriteByte(0x8001, addresLo);
		mBus->WriteByte(0x8002, addresHi);
		mBus->WriteByte(address, lo);
		mBus->WriteByte(faultyMSBAddress, hi);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(value, mCpu->pc, JmpInd_WhenAddressOnPageBoudary_RetainsOriginalBug);
	}
	#endif

	void JmpInd_SetsValueToTheReadWord()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		uint16_t address = 0x0355;
		uint8_t addresLo = address;
		uint8_t addresHi = address >> 8;
		mBus->WriteByte(0x8000, jmp_ind);
		mBus->WriteByte(0x8001, addresLo);
		mBus->WriteByte(0x8002, addresHi);
		mBus->WriteByte(address, lo);
		mBus->WriteByte(address + 1, hi);

		mCpu->Reset();

		mCpu->Clock();

		ASSERT_EQUAL(address, mCpu->Value, JmpInd_SetsValueToTheReadWord);
	}

	void JmpInd_Takes5Cycles()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		uint16_t address = 0x0355;
		uint8_t addresLo = address;
		uint8_t addresHi = address >> 8;
		mBus->WriteByte(0x8000, jmp_ind);
		mBus->WriteByte(0x8001, addresLo);
		mBus->WriteByte(0x8002, addresHi);
		mBus->WriteByte(address, lo);
		mBus->WriteByte(address + 1, hi);

		mCpu->Reset();
		auto cycles = mCpu->Cycles;

		mCpu->Clock();
		cycles = mCpu->Cycles - cycles;

		ASSERT_EQUAL(5, cycles, JmpInd_Takes5Cycles);
	}

	void JmpInd_DoesntSetAnyFlags()
	{
		uint16_t value = 0x8028;
		uint8_t lo = value;
		uint8_t hi = value >> 8;
		uint16_t address = 0x0355;
		uint8_t addresLo = address;
		uint8_t addresHi = address >> 8;
		mBus->WriteByte(0x8000, jmp_ind);
		mBus->WriteByte(0x8001, addresLo);
		mBus->WriteByte(0x8002, addresHi);
		mBus->WriteByte(address, lo);
		mBus->WriteByte(address + 1, hi);

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
		END_ASSERT(JmpInd_DoesntSetAnyFlags);
	}
};