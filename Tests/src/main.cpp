#include "CpuTests/ResetTests.h"
#include "CpuTests/Lda/LdaTests.h"

int main()
{
	ResetTests ResetTests;
	LdaTests LdaTests;
	
	RUN_BATCH(ResetTests);
	RUN_BATCH(LdaTests);
}