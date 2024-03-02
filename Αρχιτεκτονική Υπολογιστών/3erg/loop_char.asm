.data
     promt: .asciiz "Enter a charachter: "
     result: .asciiz "\n Result user_input:"
     user_input: .space 1 #space for storing user input

     
.text
     main:
      input_loop:
              #promt user to enter a char
              li $v0,4
              la $a0,promt
              syscall
              
              li $v0,12
              syscall
              sb $v0,user_input
              
              li $v0,4          
              la $a0,result
              syscall
              
              li $v0,4
              lb $a0,result
              syscall
              
              li $v0,11
              lb $a0,user_input
              syscall
              
              #check if the entered char is 'x' to exit the loop
              li $v0,'x'         #load ACII code for x int $t0
              beq $v0,$t0,exit_loop
              
              j input_loop #jump back to the begining of the loop
              
         exit_loop:
               li $v0,10
               syscall    