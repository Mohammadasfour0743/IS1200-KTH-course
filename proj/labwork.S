  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

	.global hexasc
	.global delay
	.global time2string

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii ""
	.text


.global enable_interrupt
enable_interrupt:
		ei
		jr $ra

		
.global hexasc
hexasc: 
  	
  	PUSH $a1
   	li $a1, 9
  	ble $a0, $a1, number
  	nop
  	
  	addi $v0, $a0, 55
  	
  	j done
  	nop	
  number: addi $v0, $a0, 48
  	
  	POP $a1
  done: jr $ra
  
 .global delay
 delay: 
nop	
    addi $t7, $zero, 3811  # constant inside for loop
    
    addi $t5, $zero, 1

while:
nop
    beqz $a0, exitWhile       # if ms == 0, exit while loop
nop


    sub $a0, $a0, $t5          # ms = ms - 1
	addi $t3, $zero, 0        # i = 0
    for:
nop
        bne $t3, $t7, continueFor # if i < const, continue for loop
        nop                      # Do nothing
        
        j while                   # jump to beginning of the for loop
	nop

    continueFor:
nop
    	addi $t3, $t3, 1         # i = i + 1
        j for                   # jump to the beginning of the while loop 
	nop

exitWhile:
nop
    jr $ra                      # Return from the function
    nop

		
		
  	
 .global time2string 	
time2string:

  	nop
  	PUSH $ra
  	
  	#NULL
  	li $t3, 0x00
  	sb $t3, 2($a0)
  	
  	 #hide address then POP it when we need to store in the address (because $a0 is also the parameter for hexasc)
  	

	li $t3, 0x20
	
  	sb $t3, 1($a0)
  	#seconds right
	PUSH $a0
  	
  	andi $t6, $a1, 0xf #isolate the LSB
  	or $a0, $t6, $zero #a0 has the LSB
  	jal hexasc #get the ascii for LSB
  	nop
  	POP $a0	
  	sb $v0, 0($a0)

	
  	
  	
  	

  	POP $ra
  	jr $ra
  	nop
  	
  
  
  
  	
