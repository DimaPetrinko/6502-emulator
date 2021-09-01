#pragma once

#define MaskableInterruptLocation 0xfffa
#define ResetLocation 0xfffc
#define InterruptLocation 0xfffe

#define ZeroPageStart 0x0000
#define ZeroPageEnd 0x00ff

#define StackStart 0x0100
#define StackEnd 0x01ff

#define lda_im 0xa9
#define lda_zp 0xa5
#define nop 0xea