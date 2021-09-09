#pragma once

#include "CpuTests/CpuTests.h"

#include "LdaImTests.h"
#include "LdaZpTests.h"
#include "LdaZpXTests.h"

struct LdaTests : public CpuTests
{
	void RunAll() override
	{
		LdaImTests LdaImTests;
		LdaZpTests LdaZpTests;
		LdaZpXTests LdaZpXTests;
		
		RUN_BATCH(LdaImTests);
		RUN_BATCH(LdaZpTests);
		RUN_BATCH(LdaZpXTests);
	}
};