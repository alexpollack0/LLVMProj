	.file	"/homes/pollack0/LLVMProj/test_code/example3_cloned.bc"
	.text
	.globl	_cloned_print_int
	.align	16, 0x90
	.type	_cloned_print_int,@function
_cloned_print_int:                      # @_cloned_print_int
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
	subq	$16, %rsp
	movl	%edi, %ecx
	movl	%ecx, -4(%rbp)
	movl	$.L.str1, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	printf
	callq	pop_direct_branch
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp5:
	.size	_cloned_print_int, .Ltmp5-_cloned_print_int
	.cfi_endproc

	.globl	_cloned_polynomial
	.align	16, 0x90
	.type	_cloned_polynomial,@function
_cloned_polynomial:                     # @_cloned_polynomial
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp9:
	.cfi_def_cfa_offset 16
.Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp11:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$24, %rsp
.Ltmp12:
	.cfi_offset %rbx, -24
	movl	%edi, -12(%rbp)
	callq	_cloned_pow2
	movl	g(%rip), %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %edi
	callq	_cloned_pow3
	movl	g(%rip), %eax
	movl	%eax, -20(%rbp)
	imull	$3, -16(%rbp), %ecx
	addl	%eax, %ecx
	imull	$3, -12(%rbp), %eax
	leal	1(%rcx,%rax), %ebx
	movl	%ebx, g(%rip)
	callq	pop_direct_branch
	movl	%ebx, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	ret
.Ltmp13:
	.size	_cloned_polynomial, .Ltmp13-_cloned_polynomial
	.cfi_endproc

	.globl	_cloned_pow3
	.align	16, 0x90
	.type	_cloned_pow3,@function
_cloned_pow3:                           # @_cloned_pow3
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp17:
	.cfi_def_cfa_offset 16
.Ltmp18:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp19:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
.Ltmp20:
	.cfi_offset %rbx, -24
	movl	%edi, -12(%rbp)
	movl	%edi, %ebx
	imull	%ebx, %ebx
	imull	%edi, %ebx
	movl	%ebx, g(%rip)
	callq	pop_direct_branch
	movl	%ebx, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.Ltmp21:
	.size	_cloned_pow3, .Ltmp21-_cloned_pow3
	.cfi_endproc

	.globl	_cloned_pow2
	.align	16, 0x90
	.type	_cloned_pow2,@function
_cloned_pow2:                           # @_cloned_pow2
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp25:
	.cfi_def_cfa_offset 16
.Ltmp26:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp27:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
.Ltmp28:
	.cfi_offset %rbx, -24
	movl	%edi, %ebx
	movl	%ebx, -12(%rbp)
	imull	%ebx, %ebx
	movl	%ebx, g(%rip)
	callq	pop_direct_branch
	movl	%ebx, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.Ltmp29:
	.size	_cloned_pow2, .Ltmp29-_cloned_pow2
	.cfi_endproc

	.globl	pop_direct_branch
	.align	16, 0x90
	.type	pop_direct_branch,@function
pop_direct_branch:                      # @pop_direct_branch
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
.Ltmp35:
	.size	pop_direct_branch, .Ltmp35-pop_direct_branch
	.cfi_endproc

	.globl	scan_int
	.align	16, 0x90
	.type	scan_int,@function
scan_int:                               # @scan_int
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
	movq	%rdi, %rcx
	movq	%rcx, -8(%rbp)
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movq	%rcx, %rsi
	callq	__isoc99_scanf
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp41:
	.size	scan_int, .Ltmp41-scan_int
	.cfi_endproc

	.globl	pow2
	.align	16, 0x90
	.type	pow2,@function
pow2:                                   # @pow2
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp44:
	.cfi_def_cfa_offset 16
.Ltmp45:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp46:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	imull	%edi, %edi
	movl	%edi, %eax
	popq	%rbp
	ret
.Ltmp47:
	.size	pow2, .Ltmp47-pow2
	.cfi_endproc

	.globl	pow3
	.align	16, 0x90
	.type	pow3,@function
pow3:                                   # @pow3
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp50:
	.cfi_def_cfa_offset 16
.Ltmp51:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp52:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%edi, %eax
	imull	%eax, %eax
	imull	%edi, %eax
	popq	%rbp
	ret
.Ltmp53:
	.size	pow3, .Ltmp53-pow3
	.cfi_endproc

	.globl	polynomial
	.align	16, 0x90
	.type	polynomial,@function
polynomial:                             # @polynomial
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp56:
	.cfi_def_cfa_offset 16
.Ltmp57:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp58:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	callq	_cloned_pow2
	movl	g(%rip), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %edi
	callq	_cloned_pow3
	movl	g(%rip), %eax
	movl	%eax, -12(%rbp)
	imull	$3, -8(%rbp), %ecx
	addl	%eax, %ecx
	imull	$3, -4(%rbp), %eax
	leal	1(%rcx,%rax), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp59:
	.size	polynomial, .Ltmp59-polynomial
	.cfi_endproc

	.globl	print_int
	.align	16, 0x90
	.type	print_int,@function
print_int:                              # @print_int
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp62:
	.cfi_def_cfa_offset 16
.Ltmp63:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp64:
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
.Ltmp65:
	.size	print_int, .Ltmp65-print_int
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp68:
	.cfi_def_cfa_offset 16
.Ltmp69:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp70:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	leaq	-8(%rbp), %rdi
	callq	scan_int
	movl	-8(%rbp), %edi
	callq	_cloned_polynomial
	movl	g(%rip), %eax
	movl	%eax, -12(%rbp)
	movl	$.L.str2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	-12(%rbp), %edi
	callq	_cloned_print_int
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp71:
	.size	main, .Ltmp71-main
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

	.type	g,@object               # @g
	.bss
	.globl	g
	.align	4
g:
	.long	0                       # 0x0
	.size	g, 4


	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.section	".note.GNU-stack","",@progbits
