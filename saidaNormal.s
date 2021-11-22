	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
	.globl	oi
	.type	oi, @function
# pop 0 parameters
L1:
oi:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$1, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
# compare
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
	cmpl	%edx, %eax
# CBR
	je	L5
	jmp	L3
L3:
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
L2:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L5:
# load I
# push
	subq	$4, %rsp
	movl	$40, (%rsp)
L7:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L8:
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
