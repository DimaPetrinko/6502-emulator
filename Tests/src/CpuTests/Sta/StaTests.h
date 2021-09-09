#pragma once

#include "CpuTests/CpuTests.h"

#include "StaZpTests.h"
#include "StaZpXTests.h"
#include "StaAbsTests.h"
#include "StaAbsXTests.h"
#include "StaAbsYTests.h"
#include "StaIndXTests.h"
#include "StaIndYTests.h"

struct StaTests : public CpuTests
{
	void RunAll() override
	{
		StaZpTests StaZpTests;
		StaZpXTests StaZpXTests;
		StaAbsTests StaAbsTests;
		StaAbsXTests StaAbsXTests;
		StaAbsYTests StaAbsYTests;
		StaIndXTests StaIndXTests;
		StaIndYTests StaIndYTests;

		RUN_BATCH(StaZpTests);
		RUN_BATCH(StaZpXTests);
		RUN_BATCH(StaAbsTests);
		RUN_BATCH(StaAbsXTests);
		RUN_BATCH(StaAbsYTests);
		RUN_BATCH(StaIndXTests);
		RUN_BATCH(StaIndYTests);
	}
};