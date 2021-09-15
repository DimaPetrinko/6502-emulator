#include "CpuTests/ResetTests.h"
#include "CpuTests/Lda/LdaTests.h"
#include "CpuTests/Sta/StaTests.h"
#include "CpuTests/Stx/StxTests.h"
#include "CpuTests/Sty/StyTests.h"
#include "CpuTests/Jmp/JmpTests.h"

int main()
{
	ResetTests ResetTests;
	LdaTests LdaTests;
	StaTests StaTests;
	StxTests StxTests;
	StyTests StyTests;
	JmpTests JmpTests;
	
	RUN_BATCH(ResetTests);
	RUN_BATCH(LdaTests);
	RUN_BATCH(StaTests);
	RUN_BATCH(StxTests);
	RUN_BATCH(StyTests);
	RUN_BATCH(JmpTests);
}