#pragma once

#define MaskableInterruptLocation 0xfffa
#define ResetLocation 0xfffc
#define InterruptLocation 0xfffe

#define ZeroPageStart 0x0000
#define ZeroPageEnd 0x00ff

#define StackStart 0x0100
#define StackEnd 0x01ff

#include "Cpu/Instructions/Cpu_lda_codes.h"
#include "Cpu/Instructions/Cpu_ldx_codes.h"
#include "Cpu/Instructions/Cpu_ldy_codes.h"
#include "Cpu/Instructions/Cpu_sta_codes.h"
#include "Cpu/Instructions/Cpu_stx_codes.h"
#include "Cpu/Instructions/Cpu_sty_codes.h"
#include "Cpu/Instructions/Cpu_adc_codes.h"

#define nop 0xea