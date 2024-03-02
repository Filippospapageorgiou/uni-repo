# The hello proggram
.text
.globl main
main:
#print the message
li $v0,4
la $a0,himsg
syscall
li $v0,10
syscall
.data
himsg: .asciiz "Hello Mips! \n"