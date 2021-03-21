.data
hell: .word 0x6c6c6568
o:    .word 0x0000006f
.text
addi $v0, $zero, 4
lui   $at, 80
ori   $a0, $at, 0
syscall