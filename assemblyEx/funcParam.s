	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_f                      ## -- Begin function f
	.p2align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movl	88(%rbp), %eax
	movl	80(%rbp), %r10d
	movl	72(%rbp), %r11d
	movl	64(%rbp), %ebx
	movl	56(%rbp), %r14d
	movl	48(%rbp), %r15d
	movl	40(%rbp), %r12d
	movl	32(%rbp), %r13d
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	movl	24(%rbp), %eax
	movl	%eax, -72(%rbp)         ## 4-byte Spill
	movl	16(%rbp), %eax
	movl	%edi, -44(%rbp)
	movl	%esi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movl	%ecx, -56(%rbp)
	movl	%r8d, -60(%rbp)
	movl	%r9d, -64(%rbp)
	movl	-44(%rbp), %ecx
	addl	-48(%rbp), %ecx
	addl	-52(%rbp), %ecx
	addl	-56(%rbp), %ecx
	addl	-60(%rbp), %ecx
	addl	-64(%rbp), %ecx
	addl	16(%rbp), %ecx
	addl	24(%rbp), %ecx
	addl	32(%rbp), %ecx
	addl	40(%rbp), %ecx
	addl	48(%rbp), %ecx
	addl	56(%rbp), %ecx
	addl	64(%rbp), %ecx
	addl	72(%rbp), %ecx
	addl	80(%rbp), %ecx
	addl	88(%rbp), %ecx
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movl	$0, -44(%rbp)
	movl	$10, -48(%rbp)
	movl	$20, -52(%rbp)
	movl	-48(%rbp), %edi
	movl	-52(%rbp), %esi
	movl	-48(%rbp), %edx
	movl	-52(%rbp), %ecx
	movl	-48(%rbp), %r8d
	movl	-52(%rbp), %r9d
	movl	-48(%rbp), %eax
	movl	-48(%rbp), %r10d
	movl	-48(%rbp), %r11d
	movl	-52(%rbp), %ebx
	movl	-48(%rbp), %r14d
	movl	-52(%rbp), %r15d
	movl	-48(%rbp), %r12d
	movl	-52(%rbp), %r13d
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	movl	-48(%rbp), %eax
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	movl	-48(%rbp), %eax
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	movl	-56(%rbp), %eax         ## 4-byte Reload
	movl	%eax, (%rsp)
	movl	%r10d, 8(%rsp)
	movl	%r11d, 16(%rsp)
	movl	%ebx, 24(%rsp)
	movl	%r14d, 32(%rsp)
	movl	%r15d, 40(%rsp)
	movl	%r12d, 48(%rsp)
	movl	%r13d, 56(%rsp)
	movl	-60(%rbp), %eax         ## 4-byte Reload
	movl	%eax, 64(%rsp)
	movl	-64(%rbp), %eax         ## 4-byte Reload
	movl	%eax, 72(%rsp)
	callq	_f
	xorl	%ecx, %ecx
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
