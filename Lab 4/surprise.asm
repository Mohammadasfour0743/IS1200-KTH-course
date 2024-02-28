.text	
	addi $a0,$0,4    # set $a0 to 4
	addi $v1,$0,1	  
	
	
loop:	beq $0, $a0, end
	add $a1,$0,$a0
	add $a2,$0,$v1
	mul $v0,$a1,$a2
	add $v1,$v0,$0
	addi $a0,$a0,-1
	beq $0,$0,loop
	nop


end:	add $v0, $v1, $0

stop:	nop
	beq $0,$0,stop

