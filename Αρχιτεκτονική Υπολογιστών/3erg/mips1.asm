.data
     promt: .asciiz "Enter a charachter: "
     result: .asciiz "\n Result user_input:"
     user_input: .space 1 #space for storing user input

     
.text
     main:
     #promt user to emter a characther
     
          li $v0,4 #syscall for printing a string
          la $a0,promt
          syscall
          
          li $v0,12 #syscall fo rreadind a char
          syscall
          sb $v0,user_input #store the enter char in user inmput
          
          li $v0,4
          la $a0,result
          syscall
          
          li $v0,11
          lb $a0,user_input
          syscall
          
                        
          li $v0,10
          syscall              