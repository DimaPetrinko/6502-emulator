#pragma once

#define MaskableInterruptLocation 0xfffa
#define ResetLocation 0xfffc
#define InterruptLocation 0xfffe

#define ZeroPageStart 0x0000
#define ZeroPageEnd 0x00ff

#define StackStart 0x0100
#define StackEnd 0x01ff

#include "Cpu/Instructions/Lda/Codes.h"
#include "Cpu/Instructions/Ldx/Codes.h"
#include "Cpu/Instructions/Ldy/Codes.h"
#include "Cpu/Instructions/Sta/Codes.h"
#include "Cpu/Instructions/Stx/Codes.h"
#include "Cpu/Instructions/Sty/Codes.h"
#include "Cpu/Instructions/Adc/Codes.h"
#include "Cpu/Instructions/Jmp/Codes.h"

#define nop 0xea