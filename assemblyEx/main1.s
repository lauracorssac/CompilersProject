	.file	"main1.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$12, %eax
	popq	%rbp
	ret
