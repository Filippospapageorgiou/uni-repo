.data
str: .asciiz "Hello world\n"
number: .word 256

.text
.globl main
main:
li $v0,4
la $a0,str
syscall
la $t0,number 
lw $s1,0($t0) 
addi $t2,$s1,8 
sw $t2,0($t0)
move $a0,$t0
li $v0,1
syscall

li $v0,10
syscall