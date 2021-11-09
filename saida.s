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
	movl	$10, (%rsp)
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
# CMNE
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
	cmpl	%edx, %eax
# CBR
	je	L3
	jmp	L1
L1:
# load I
# push
	subq	$4, %rsp
	movl	$100, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
L3:
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L5:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
