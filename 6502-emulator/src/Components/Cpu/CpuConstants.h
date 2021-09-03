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
#define lda_zpx 0xb5
#define lda_abs 0xad
#define lda_absx 0xbd
#define lda_absy 0xb9
#define lda_indx 0xa1
#define lda_indy 0xb1

#define ldx_im 0xa2
#define ldx_zp 0xa6
#define ldx_zpy 0xb6
#define ldx_abs 0xae
#define ldx_absy 0xbe

#define ldy_im 0xa0
#define ldy_zp 0xa4
#define ldy_zpx 0xb4
#define ldy_abs 0xac
#define ldy_absx 0xbc

#define nop 0xea