	.file	"/homes/pollack0/LLVMProj/test_code/example3.bc"
	.text
	.globl	pop_direct_branch
	.align	16, 0x90
	.type	pop_direct_branch,@function
pop_direct_branch:                      # @pop_direct_branch
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp2:
	.cfi_def_cfa_offset 16
.Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp4:
	.cfi_def_cfa_register %rbp
	#APP
	popq %rbp
	addq $8, %rsp
	leave
	movq (%rsp), %rax
	addq $8, %rsp
	jmp *%rax
	
	#NO_APP
	popq	%rbp
	ret
.Ltmp5:
	.size	pop_direct_branch, .Ltmp5-pop_direct_branch
	.cfi_endproc

	.globl	scan_int
	.align	16, 0x90
	.type	scan_int,@function
scan_int:                               # @scan_int
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp8:
	.cfi_def_cfa_offset 16
.Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp10:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, %rcx
	movq	%rcx, -8(%rbp)
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movq	%rcx, %rsi
	callq	__isoc99_scanf
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp11:
	.size	scan_int, .Ltmp11-scan_int
	.cfi_endproc

	.globl	pow2
	.align	16, 0x90
	.type	pow2,@function
pow2:                                   # @pow2
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp14:
	.cfi_def_cfa_offset 16
.Ltmp15:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp16:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	imull	%edi, %edi
	movl	%edi, %eax
	popq	%rbp
	ret
.Ltmp17:
	.size	pow2, .Ltmp17-pow2
	.cfi_endproc

	.globl	pow3
	.align	16, 0x90
	.type	pow3,@function
pow3:                                   # @pow3
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp20:
	.cfi_def_cfa_offset 16
.Ltmp21:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp22:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%edi, %eax
	imull	%eax, %eax
	imull	%edi, %eax
	popq	%rbp
	ret
.Ltmp23:
	.size	pow3, .Ltmp23-pow3
	.cfi_endproc

	.globl	polynomial
	.align	16, 0x90
	.type	polynomial,@function
polynomial:                             # @polynomial
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp26:
	.cfi_def_cfa_offset 16
.Ltmp27:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp28:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	callq	pow2
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %edi
	callq	pow3
	movl	%eax, -12(%rbp)
	imull	$3, -8(%rbp), %ecx
	addl	%eax, %ecx
	imull	$3, -4(%rbp), %eax
	leal	1(%rcx,%rax), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp29:
	.size	polynomial, .Ltmp29-polynomial
	.cfi_endproc

	.globl	print_int
	.align	16, 0x90
	.type	print_int,@function
print_int:                              # @print_int
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp32:
	.cfi_def_cfa_offset 16
.Ltmp33:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp34:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, %ecx
	movl	%ecx, -4(%rbp)
	movl	$.L.str1, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	printf
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp35:
	.size	print_int, .Ltmp35-print_int
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp38:
	.cfi_def_cfa_offset 16
.Ltmp39:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp40:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	leaq	-8(%rbp), %rdi
	callq	scan_int
	movl	-8(%rbp), %edi
	callq	polynomial
	movl	%eax, -12(%rbp)
	movl	$.L.str2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	-12(%rbp), %edi
	callq	print_int
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp41:
	.size	main, .Ltmp41-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	"%d \n"
	.size	.L.str1, 5

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	"(x+1)^3 = "
	.size	.L.str2, 11


	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.section	".note.GNU-stack","",@progbits
