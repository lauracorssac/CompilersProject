	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
	.globl	f
	.type	f, @function
L1:
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$4, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
	call	f
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L2:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
