	.file	"calculator.c"
	.text
	.section	.rodata
.LC1:
	.string	"r"
.LC2:
	.string	"data.txt"
.LC3:
	.string	"Error opening file"
.LC4:
	.string	"%d %d"
.LC5:
	.string	"a = %d, b = %d\n"
	.align 8
.LC6:
	.string	"Enter the operation you want to perform\n1: add\n2: subtract\n3: multiply\n4: div\n5: mod"
.LC7:
	.string	"%d"
.LC8:
	.string	"%d + %d = %0.2f\n"
.LC9:
	.string	"%d - %d = %0.2f\n"
.LC10:
	.string	"%d x %d = %0.2f\n"
.LC11:
	.string	"%d / %d = %f"
.LC12:
	.string	"%d %% %d = %0.2f\n"
.LC13:
	.string	"Enter valid operation"
.LC14:
	.string	"w"
.LC15:
	.string	"result.txt"
.LC16:
	.string	"Error opening result_data.txt"
.LC17:
	.string	"%d %c %d = %0.2f"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L14
.L2:
	leaq	-36(%rbp), %rcx
	leaq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
.L4:
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-32(%rbp), %eax
	cmpl	$5, %eax
	ja	.L5
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L7(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L7(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L7:
	.long	.L5-.L7
	.long	.L11-.L7
	.long	.L10-.L7
	.long	.L9-.L7
	.long	.L8-.L7
	.long	.L6-.L7
	.text
.L11:
	movl	-40(%rbp), %edx
	movl	-36(%rbp), %eax
	addl	%edx, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -28(%rbp)
	movb	$43, -41(%rbp)
	pxor	%xmm2, %xmm2
	cvtss2sd	-28(%rbp), %xmm2
	movq	%xmm2, %rcx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L12
.L10:
	movl	-40(%rbp), %edx
	movl	-36(%rbp), %eax
	subl	%eax, %edx
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%edx, %xmm0
	movss	%xmm0, -28(%rbp)
	movb	$45, -41(%rbp)
	pxor	%xmm3, %xmm3
	cvtss2sd	-28(%rbp), %xmm3
	movq	%xmm3, %rcx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L12
.L9:
	movl	-40(%rbp), %edx
	movl	-36(%rbp), %eax
	imull	%edx, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -28(%rbp)
	movb	$120, -41(%rbp)
	pxor	%xmm4, %xmm4
	cvtss2sd	-28(%rbp), %xmm4
	movq	%xmm4, %rcx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L12
.L8:
	movl	-40(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movl	-36(%rbp), %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -28(%rbp)
	movb	$47, -41(%rbp)
	pxor	%xmm5, %xmm5
	cvtss2sd	-28(%rbp), %xmm5
	movq	%xmm5, %rcx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L12
.L6:
	movl	-40(%rbp), %eax
	movl	-36(%rbp), %esi
	cltd
	idivl	%esi
	movl	%edx, %ecx
	movl	%ecx, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -28(%rbp)
	movb	$37, -41(%rbp)
	pxor	%xmm6, %xmm6
	cvtss2sd	-28(%rbp), %xmm6
	movq	%xmm6, %rcx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %eax
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L12
.L5:
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L4
.L12:
	leaq	.LC14(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L13
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L14
.L13:
	pxor	%xmm7, %xmm7
	cvtss2sd	-28(%rbp), %xmm7
	movq	%xmm7, %rsi
	movl	-36(%rbp), %edi
	movsbl	-41(%rbp), %ecx
	movl	-40(%rbp), %edx
	movq	-16(%rbp), %rax
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC17(%rip), %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
.L14:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 14.2.0-19ubuntu2) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
