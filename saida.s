	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
L0:
main:
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -16(%rbp)
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -20(%rbp)
	movl	-5(%rbp), %eax
	subq	$4, %rsp
	mov	(%eax), %rsp
	movl	-6(%rbp), %eax
	subq	$4, %rsp
	mov	(%eax), %rsp
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	(%rsp), %edx
	addq	$4, %rsp
	addl	%edx, %eax
	subq	$4, %rsp
	mov	(%eax), %rsp
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -24(%rbp)
