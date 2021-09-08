#include "CpuTests/ResetTests.h"
#include "CpuTests/LdaImTests.h"
#include "CpuTests/LdaZpTests.h"
#include "CpuTests/LdaZpXTests.h"

int main()
{
	ResetTests ResetTests;
	LdaImTests LdaImTests;
	LdaZpTests LdaZpTests;
	LdaZpXTests LdaZpXTests;
	
	RUN_BATCH(ResetTests);
	RUN_BATCH(LdaImTests);
	RUN_BATCH(LdaZpTests);
	RUN_BATCH(LdaZpXTests);
}