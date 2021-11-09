	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
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
	movl	$0, -4(%rbp)
	movl	$2, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jge	LBB0_2
## %bb.1:
	movl	$1000, -4(%rbp)         ## imm = 0x3E8
	jmp	LBB0_3
LBB0_2:
	movl	$2000, -4(%rbp)         ## imm = 0x7D0
LBB0_3:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
