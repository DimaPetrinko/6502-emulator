#include "CpuVisualizer.h"

#include "Cpu/CpuConstants.h"

CpuVisualizer::CpuVisualizer()
{
	mInstructionNames[lda_im] = "lda im";
	mInstructionNames[lda_zp] = "lda zp";
	mInstructionNames[lda_zpx] = "lda zp x";
	mInstructionNames[lda_abs] = "lda abs";
	mInstructionNames[lda_absx] = "lda abs x";
	mInstructionNames[lda_absy] = "lda abs y";
	mInstructionNames[lda_indx] = "lda ind x";
	mInstructionNames[lda_indy] = "lda ind y";
	mInstructionNames[ldx_im] = "ldx im";
	mInstructionNames[ldx_zp] = "ldx zp";
	mInstructionNames[ldx_zpy] = "ldx zp y";
	mInstructionNames[ldx_abs] = "ldx abs";
	mInstructionNames[ldx_absy] = "ldx abs y";
	mInstructionNames[ldy_im] = "ldy im";
	mInstructionNames[ldy_zp] = "ldy zp";
	mInstructionNames[ldy_zpx] = "ldy zp x";
	mInstructionNames[ldy_abs] = "ldy abs";
	mInstructionNames[ldy_absx] = "ldy abs x";
	mInstructionNames[adc_im] = "adc im";
	mInstructionNames[adc_zp] = "adc zp";
	mInstructionNames[adc_zpx] = "adc zp x";
	mInstructionNames[adc_abs] = "adc abs";
	mInstructionNames[adc_absx] = "adc abs x";
	mInstructionNames[adc_absy] = "adc abs y";
	mInstructionNames[adc_indx] = "adc ind x";
	mInstructionNames[adc_indy] = "adc ind y";
	mInstructionNames[nop] = "nop";
}

void CpuVisualizer::Visualize(Cpu* cpu)
{
	auto instructionName = mInstructionNames.find(cpu->Instruction) != mInstructionNames.end()
							? mInstructionNames[cpu->Instruction]
							: "undef";
	printf("cycles: | %4i |\n", cpu->Cycles);
	printf("pc:     | %4.4x |\n", cpu->pc);
	printf("sp:     | %4.2x |\n", cpu->sp);
	printf("instrt: | %4.2x | %s\n", cpu->Instruction, instructionName);
	printf("value:  | %4.4x | %5i | %i\n", cpu->Value, cpu->Value, (int8_t)cpu->Value);
	printf("a:      | %4.2x | %5i | %i\n", cpu->a, cpu->a, (int8_t)cpu->a);
	printf("x:      | %4.2x | %5i | %i\n", cpu->x, cpu->x, (int8_t)cpu->x);
	printf("y:      | %4.2x | %5i | %i\n", cpu->y, cpu->y, (int8_t)cpu->y);
	printf("     _____________\n");
	printf("     c z i d b v n\n");
	printf("     %i %i %i %i %i %i %i \n", cpu->c, cpu->z, cpu->i, cpu->d, cpu->b, cpu->v, cpu->n);
}