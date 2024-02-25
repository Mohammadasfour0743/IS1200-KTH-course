  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii ""
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # You can write your own code for hexasc here
  #
  hexasc: 
  	
  	PUSH($a1)
   	li $a1, 9
  	ble $a0, $a1, number
  	nop
  	
  	addi $v0, $a0, 55
  	
  	j done
  	nop	
  number: addi $v0, $a0, 48
  	
  	POP($a1)
  done: jr $ra
  
  
  delay:
     
nop	
    addi $t7, $zero, 120 # constant inside for loop
    
    addi $t5, $zero, 1

while:
nop
    blez $a0, exitWhile       # if ms = 0, exit while loop
nop


    sub $a0, $a0, $t5          # ms = ms - 1
	addi $t3, $zero, 0        # $t3 = i = 0
    for:
nop
        bne $t3, $t7, continueFor # if i < constant, continue for loop
        nop                      # Do nothing
        
        j while                   # jump to beginning of the for loop
	nop

    continueFor:
nop
    	addi $t3, $t3, 1         # i = i + 1
        j for                   
	nop

exitWhile:
nop
    jr $ra                      
    nop


		
  	
  time2string:
  	nop
  	PUSH($ra)
  	
  	#NULL
  	li $t3, 0x00
  	sb $t3, 5($a0)
  	
  	PUSH($a0) #hide address then POP it when we need to store in the address (because $a0 is also the parameter for hexasc)
  	
  	#seconds right
  	
  	andi $a0, $a1, 0xf #isolate the LSB and store in $a0
  	
  	jal hexasc #get the ascii for LSB
  	nop
  	POP($a0)	
  	sb $v0, 4($a0)
  	
  	PUSH($a0)
  	
  	#seconds left
	srl $a1, $a1, 4
  	andi $a0, $a1, 0xf
  		
  	jal hexasc
  	nop
  	POP($a0)
  	sb $v0, 3($a0)	
  	
  	# position of ":" :
  	li $t4, 0x3A
  	sb $t4, 2($a0)
  	
  	PUSH($a0)
  	#minutes right
  	srl $a1, $a1, 4  
  	andi $a0, $a1, 0xf
  	
  	jal hexasc
  	nop
  	POP($a0)
  	sb $v0, 1($a0)
  	PUSH($a0)
  	
  	#minutes left
  	srl $a1, $a1, 4
  	andi $a0, $a1, 0xf
  	
  	
  	jal hexasc
  	nop
  	
  	POP($a0)
  
  	sb $v0, 0($a0)
  	

  	POP($ra)
  	jr $ra
  	nop
  	
  	
  	
 	
 	
  			
  		
  		
  		
  		
  		
  		
  		
  		
  		
  		
  
