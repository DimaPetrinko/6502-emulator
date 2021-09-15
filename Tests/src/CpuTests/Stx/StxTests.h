#pragma once

#include "CpuTests/CpuTests.h"

#include "StxZpTests.h"
#include "StxZpYTests.h"
#include "StxAbsTests.h"

struct StxTests : public CpuTests
{
	void RunAll() override
	{
		StxZpTests StxZpTests;
		StxZpYTests StxZpYTests;
		StxAbsTests StxAbsTests;

		RUN_BATCH(StxZpTests);
		RUN_BATCH(StxZpYTests);
		RUN_BATCH(StxAbsTests);
	}
};