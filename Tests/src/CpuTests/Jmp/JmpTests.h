#pragma once

#include "CpuTests/CpuTests.h"

#include "JmpIndTests.h"
#include "JmpAbsTests.h"

struct JmpTests : public CpuTests
{
	void RunAll() override
	{
		JmpAbsTests JmpAbsTests;
		JmpIndTests JmpIndTests;

		RUN_BATCH(JmpAbsTests);
		RUN_BATCH(JmpIndTests);
	}
};