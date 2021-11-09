	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
	.globl	d
	.type	d, @function
d:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$8, %rsp
# mov parameter
	movl	20(%rbp), %eax
	movl	%eax, -4(%rbp)
# mov parameter
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
	movl	-8(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
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
	movq	%rbp, %rsp
	popq	%rbp
	ret	
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$4, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$6, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
	call	d
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
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
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
