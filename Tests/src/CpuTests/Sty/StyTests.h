#pragma once

#include "CpuTests/CpuTests.h"

#include "StyZpTests.h"
#include "StyZpXTests.h"
#include "StyAbsTests.h"

struct StyTests : public CpuTests
{
	void RunAll() override
	{
		StyZpTests StyZpTests;
		StyZpXTests StyZpXTests;
		StyAbsTests StyAbsTests;

		RUN_BATCH(StyZpTests);
		RUN_BATCH(StyZpXTests);
		RUN_BATCH(StyAbsTests);
	}
};