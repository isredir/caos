	.global rop
rop:
	push $str2
	push $f1+1
	push $str1
	push $f1+1
ret
