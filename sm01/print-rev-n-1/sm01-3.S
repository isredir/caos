	.global main
main:
	call readi32
loop:
	cmpl $0, %eax
	jl negative
	call writei32
	subl $1, %eax
	cmpl $-1, %eax
	jne loop
	call finish
negative:
	call finish
