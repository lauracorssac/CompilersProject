	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$4, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$2000, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$1, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
L1:
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
L4:
# load I
# push
	subq	$4, %rsp
	movl	$1000, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
L6:
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L7:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
