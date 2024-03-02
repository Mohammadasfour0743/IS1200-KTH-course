.data
	ms: .word 10
	const: .word 50
.text
	main:
		addi $t3, $zero, 0  # i = 0
		lw $t5, ms  # $t5 = ms
		addi $t7, $zero, 5
		
		jal delay
		
		
		
		li $a0, 111
		li $v0, 11
		syscall
		
		j main
		
		
		delay:
		while:
			beqz $t5, exitWhile # if ms = zero, exit while loop
			
			sub $t5, $t5, 1 # ms = ms - 1
			
			for:
				bge $t3, $t7, exitFor # if i => const, exit for loop
				
				nop # Do nothing
				
				addi $t3, $t3, 1  #i = i + 1
				
				j for #jump to beginning of the for loop
				
			exitFor:
				j while # jump to the beginning of the while loop 
			
							
		exitWhile:
			#Exit the program
			jr $ra
			nop
		
		
		
		
		
		
		addi $t7, $zero, 5
		
		
		while:
			beqz $a0, exitWhile # if ms = zero, exit while loop
			
			sub $a0, $a0, 1 # ms = ms - 1
			li $t3,0
			
			for:
				bge $t3, $t7, exitFor # if i => const, exit for loop
				
				nop # Do nothing
				
				addi $t3, $t3, 1  #i = i + 1
				
				j for #jump to beginning of the for loop
				
			exitFor:
				j while # jump to the beginning of the while loop 
			
							
		exitWhile:
			#Exit the program
