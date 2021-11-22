	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
# pop 0 parameters
L1:
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$20, (%rsp)
L9:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L10:
