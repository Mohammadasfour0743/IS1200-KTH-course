.text	
	addi $a0,$0,3    # This is the input
	addi $v1,$0,1	  
loop:	beq $0, $a0, end
	add $a1,$0,$a0
	add $a2,$0,$v1
	beq $0,$0, multt
	ret:
	add $v1,$v0,$0
	addi $a0,$a0,-1
	beq $0,$0,loop
end:	add $v0, $v1, $0
stop:	nop
	beq $0,$0,stop
	multt:#mult a1,a2 to v0
	add $v0,$0,$0
	loopo:
	beq $a1,$0,ret
	add $v0,$v0,$a2
	addi $a1,$a1,-1
	beq $0,$0,loopo
