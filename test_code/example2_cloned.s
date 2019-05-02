	.file	"/homes/pollack0/LLVMProj/test_code/example2_cloned.bc"
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

	.globl	_cloned_pow2
	.align	16, 0x90
	.type	_cloned_pow2,@function
_cloned_pow2:                           # @_cloned_pow2
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
	pushq	%rax
.Ltmp12:
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
.Ltmp13:
	.size	_cloned_pow2, .Ltmp13-_cloned_pow2
	.cfi_endproc

	.globl	pop_direct_branch
	.align	16, 0x90
	.type	pop_direct_branch,@function
pop_direct_branch:                      # @pop_direct_branch
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp16:
	.cfi_def_cfa_offset 16
.Ltmp17:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp18:
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
.Ltmp19:
	.size	pop_direct_branch, .Ltmp19-pop_direct_branch
	.cfi_endproc

	.globl	scan_int
	.align	16, 0x90
	.type	scan_int,@function
scan_int:                               # @scan_int
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp22:
	.cfi_def_cfa_offset 16
.Ltmp23:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp24:
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
.Ltmp25:
	.size	scan_int, .Ltmp25-scan_int
	.cfi_endproc

	.globl	pow2
	.align	16, 0x90
	.type	pow2,@function
pow2:                                   # @pow2
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp28:
	.cfi_def_cfa_offset 16
.Ltmp29:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp30:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	imull	%edi, %edi
	movl	%edi, %eax
	popq	%rbp
	ret
.Ltmp31:
	.size	pow2, .Ltmp31-pow2
	.cfi_endproc

	.globl	foo
	.align	16, 0x90
	.type	foo,@function
foo:                                    # @foo
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp34:
	.cfi_def_cfa_offset 16
.Ltmp35:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp36:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	(%rdi), %edi
	callq	_cloned_pow2
	movl	g(%rip), %eax
	movl	%eax, -12(%rbp)
	movq	-8(%rbp), %rcx
	movl	(%rcx), %edx
	leal	1(%rax,%rdx,2), %eax
	movl	%eax, (%rcx)
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp37:
	.size	foo, .Ltmp37-foo
	.cfi_endproc

	.globl	print_int
	.align	16, 0x90
	.type	print_int,@function
print_int:                              # @print_int
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp40:
	.cfi_def_cfa_offset 16
.Ltmp41:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp42:
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
.Ltmp43:
	.size	print_int, .Ltmp43-print_int
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp47:
	.cfi_def_cfa_offset 16
.Ltmp48:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp49:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
.Ltmp50:
	.cfi_offset %rbx, -24
	movl	$0, -12(%rbp)
	leaq	-16(%rbp), %rbx
	movq	%rbx, %rdi
	callq	scan_int
	movq	%rbx, %rdi
	callq	foo
	movl	$.L.str2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	-16(%rbp), %edi
	callq	_cloned_print_int
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.Ltmp51:
	.size	main, .Ltmp51-main
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
	.asciz	"(x+1)^2 = "
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
