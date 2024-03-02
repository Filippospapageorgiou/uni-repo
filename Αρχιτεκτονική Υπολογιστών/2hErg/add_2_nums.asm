.data
value:.word 0,0,0
message1:.asciiz "Result\n"
message2:.asciiz "addition= "

.text
.globl main
main:
la $t0,value
li $v0,5 #dwse ton 1o arithmo
syscall
sw $v0,0($t0) #apouikeuse ton arithmo stin thesi value
li $v0,5
syscall
sw $v0,4($t0) #apouikeuse ton arihmo sto vlue+4
lw $t1,0($t0)
lw $t2,4($t0)
add $t3,$t2,$t1
sw $t3,8($t0)
li $v0,4
la $a0,message1
syscall
li $v0,4
la $a0,message2
syscall
li $v0,1
move $a0,$t3
syscall
li $v0,10
syscall