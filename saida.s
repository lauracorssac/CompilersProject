	.file	"etatpa6.c"
	.text
	.globl	main
	.type	main, @function
# pop 0 parameters
L0:
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$20, %rsp
# load I
# push
	subq	$4, %rsp
	movl	$10, (%rsp)
L1:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
# load I
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -4(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$1, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -8(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$2, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -12(%rbp)
# load I
# push
	subq	$4, %rsp
	movl	$3, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
	movl	-8(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# compare
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	cmpl	%edx, %eax
	jl	AL0
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
	je	L2
	jmp	L5
L2:
	movl	-12(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
	movl	-16(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
# compare
# pop
	movl	(%rsp), %edx
	addq	$4, %rsp
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	cmpl	%edx, %eax
	jl	AL2
# push
	subq	$4, %rsp
	movl	$0, (%rsp)
	jmp	AL3
AL2:
# push
	subq	$4, %rsp
	movl	$1, (%rsp)
AL3:
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
	je	L7
	jmp	L5
L5:
# load I
# push
	subq	$4, %rsp
	movl	$293, (%rsp)
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movl	%eax, -20(%rbp)
L7:
	movl	-20(%rbp), %eax
# push
	subq	$4, %rsp
	movl	%eax, (%rsp)
L8:
# pop
	movl	(%rsp), %eax
	addq	$4, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret	
L9:
