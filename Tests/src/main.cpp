#include "CpuTests/ResetTests.h"
#include "CpuTests/Lda/LdaTests.h"
#include "CpuTests/Sta/StaTests.h"

int main()
{
	ResetTests ResetTests;
	LdaTests LdaTests;
	StaTests StaTests;
	
	RUN_BATCH(ResetTests);
	RUN_BATCH(LdaTests);
	RUN_BATCH(StaTests);
}