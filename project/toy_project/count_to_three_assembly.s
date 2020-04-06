	.arch msp430g2553
	
	.data
num:	.word 0
	
	.text
jt:	.word case0
	.word case1
	.word case2
	.word case3
	
	.global count_to_three
count_to_three:
	cmp #4, &num
	mov &num, r12
	add r12, r12
	mov jt(r12), r0

case0:	mov #0, &red_on
	mov #0, &green_on
	mov #7644, r12
	jmp end
	
case1:	xor #1, &red_on
	mov #6067, r12
	jmp end
	
case2:	xor #1, &red_on
	xor #1, &green_on
	mov #5102, r12
	jmp end
	
case3:	xor #1, &red_on
	mov #3822, r12
	jmp end

end:	call #buzzer_set_period
	add #1, &num
	cmp #4, &num
	jge reset
	ret

reset:	mov #0, &num
	ret
