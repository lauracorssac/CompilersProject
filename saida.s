	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$12, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$3, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
	subq	$0, %rsp
	movl	-8(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
	subq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
	addl	%edx, %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -12(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
