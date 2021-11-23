	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
# pop 0 parameters
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$8, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$3, (%rsp)
L1:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	negl	%eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$234, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
# compare
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	cmpl	%edx, %eax
	jg	AL0
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
	jmp	AL1
AL0:
# push
	subq	$4, %rsp
	movl	$1, (%rsp)
AL1:
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
	je	L3
	jmp	L2
L2:
# load I
# push
	subq	$4, %rsp
	movl	$393, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
	jmp	L4
L3:
# load I
# push
	subq	$4, %rsp
	movl	$432, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
L4:
	movl	-8(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L6:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
