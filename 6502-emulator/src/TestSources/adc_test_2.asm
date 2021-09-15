	lda #$ff			; resets v, n, a. sets c to 1
	adc #$01

	lda #127			; 127 + 1 + c = 129/-127
	adc #1				; c = 0, v = 1, n = 1


	lda #$ff			; resets v, n, a. sets c to 1
	adc #$01

	lda #126			; 126 + 1 + c = 128/-128
	adc #1				; c = 0, v = 1, n = 1


	lda #$ff			; resets v, n, a. sets c to 1
	adc #$01

	lda #128			; 128(-128) + 255(-1) + c
	adc #255			; = 384 -> 128/-128 ; c = 1, v = 0, n = 1


	lda #$ff			; resets v, n, a. sets c to 1
	adc #$01

	lda #128			; 128(-128) + 254(-2) + c 
	adc #254			; = 383 -> 127 ; c = 1, v = 1, n = 0