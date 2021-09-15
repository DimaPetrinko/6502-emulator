#include "CpuTests/ResetTests.h"
#include "CpuTests/Lda/LdaTests.h"
#include "CpuTests/Sta/StaTests.h"
#include "CpuTests/Stx/StxTests.h"

int main()
{
	ResetTests ResetTests;
	LdaTests LdaTests;
	StaTests StaTests;
	StxTests StxTests;
	
	RUN_BATCH(ResetTests);
	RUN_BATCH(LdaTests);
	RUN_BATCH(StaTests);
	RUN_BATCH(StxTests);
}