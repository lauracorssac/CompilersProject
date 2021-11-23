	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
# pop 0 parameters
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$4, %rsp
L7:
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
	je	L9
	jmp	L8
L8:
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
	je	L4
	jmp	L2
L2:
# load I
# push
	subq	$4, %rsp
	movl	$30, (%rsp)
L1:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L4:
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
L6:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
	jmp	L7
L9:
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
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
# load I
# push
	subq	$4, %rsp
	movl	$4, (%rsp)
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
# load I
# push
	subq	$4, %rsp
	movl	$5, (%rsp)
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
# load I
# push
	subq	$4, %rsp
	movl	$6, (%rsp)
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
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
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
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L11:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L12:
