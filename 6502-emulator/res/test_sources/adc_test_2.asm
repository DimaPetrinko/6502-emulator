  lda #$ff ; resets v, n, a. sets c to 1
  adc #$01

  lda #127
  adc #1 ; 127 + 1 + c = 129/-127 ; c = 0, v = 1, n = 1


  lda #$ff ; resets v, n, a. sets c to 1
  adc #$01

  lda #126
  adc #1 ; 126 + 1 + c = 128/-128 ; c = 0, v = 1, n = 1


  lda #$ff ; resets v, n, a. sets c to 1
  adc #$01

  lda #128
  adc #255 ; 128(-128) + 255(-1) + c = 384 -> 128/-128 ; c = 1, v = 0, n = 1


  lda #$ff ; resets v, n, a. sets c to 1
  adc #$01

  lda #128
  adc #254 ; 128(-128) + 254(-2) + c = 383 -> 127 ; c = 1, v = 1, n = 0