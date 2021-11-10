	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$8, %rsp
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
	je	L2
	jmp	L1
L1:
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
# load I
# push
	subq	$4, %rsp
	movl	$3, (%rsp)
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	addl	%edx, %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L5:
	jmp	L3
L2:
# load I
# push
	subq	$4, %rsp
	movl	$3, (%rsp)
L6:
L3:
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
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
	je	L8
	jmp	L7
L7:
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
L11:
	jmp	L9
L8:
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
L12:
L9:
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	subl	%edx, %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L13:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
