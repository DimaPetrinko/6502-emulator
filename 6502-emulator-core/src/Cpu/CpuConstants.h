#pragma once

#define MaskableInterruptLocation 0xfffa
#define ResetLocation 0xfffc
#define InterruptLocation 0xfffe

#define ZeroPageStart 0x0000
#define ZeroPageEnd 0x00ff

#define StackStart 0x0100
#define StackEnd 0x01ff

#include "Cpu/Instructions/Lda/Cpu_lda_codes.h"
#include "Cpu/Instructions/Ldx/Cpu_ldx_codes.h"
#include "Cpu/Instructions/Ldy/Cpu_ldy_codes.h"
#include "Cpu/Instructions/Sta/Cpu_sta_codes.h"
#include "Cpu/Instructions/Stx/Cpu_stx_codes.h"
#include "Cpu/Instructions/Sty/Cpu_sty_codes.h"
#include "Cpu/Instructions/Adc/Cpu_adc_codes.h"

#define nop 0xea