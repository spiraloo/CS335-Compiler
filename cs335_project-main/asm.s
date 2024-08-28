.data
		integer_format:	.asciz,	"%ld\n"
.global	main
.text

		# ginfunc bubbleSort_intfunc1:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		subq	$256,	%rsp

		# pparam array
		# ackptr -4
		# = 0		movq	$0,	%rdx
		movq	%rdx,	-64(%rbp)

		# ram array		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	-72(%rbp)

		# ackptr +4
		# ll len@any 1		call	func2
		add	$8,	%rsp

		#  return_value		movq	%rax,	0(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax

		# = t0		movq	-80(%rbp),	%rdx
		movq	%rdx,	-88(%rbp)

		# = 0		movq	$0,	%rdx
		movq	%rdx,	-64(%rbp)

		#  = l		movq	-96(%rbp),	%rdx
		movq	%rdx,	-104(%rbp)

		#  = i < t1		movq	-64(%rbp),	%rdx
		movq	-104(%rbp),	%rcx
		cmp	%rdx,	%rcx
		jg	1f
		movq	$0,	%rdx
		jmp	2f
1:
		movq	$1,	%rdx
		jmp	2f
2:
		movq	%rdx,	-112(%rbp)

		#  t2 goto 14		movq	-112(%rbp),	%rdx
		cmp	$0,	%rdx
		jne	L14

		# to 		jmp	L52

		# apped = False		movq	-120(%rbp),	%rdx
		movq	%rdx,	0(%rbp)

		# = 0		movq	$0,	%rdx
		movq	%rdx,	-128(%rbp)

		#  = l - i
		#  = l - i		movq	%rdx,	-136(%rbp)

		#  = t3 - 1
		#  = t3 - 1		movq	%rdx,	-144(%rbp)

		# = t4		movq	-144(%rbp),	%rdx
		movq	%rdx,	-152(%rbp)

		# = 0		movq	-160(%rbp),	%rdx
		movq	%rdx,	-128(%rbp)

		#  = m		movq	-168(%rbp),	%rdx
		movq	%rdx,	-176(%rbp)

		#  = j < t5		movq	-128(%rbp),	%rdx
		movq	-176(%rbp),	%rcx
		cmp	%rdx,	%rcx
		jg	1f
		movq	$0,	%rdx
		jmp	2f
1:
		movq	$1,	%rdx
		jmp	2f
2:
		movq	%rdx,	-184(%rbp)

		#  t6 goto 24		movq	-184(%rbp),	%rdx
		cmp	$0,	%rdx
		jne	L24

		# to 		jmp	L49

		#  = j * 4		movq	-128(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-192(%rbp)

		#  = array + t7		movq	-200(%rbp),	%rdx
		add	-192(%rbp),	%rdx
		movq	%rdx,	-192(%rbp)

		#  = j + 1
		#  = j + 1		movq	%rdx,	-208(%rbp)

		#  = t8 * 4		movq	-208(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-216(%rbp)

		#  = array + t9		movq	-200(%rbp),	%rdx
		add	-216(%rbp),	%rdx
		movq	%rdx,	-216(%rbp)

		# 0 = *t7 > *t9
		# 0 = *t7 > *t9		movq	%rdx,	-224(%rbp)

		#  t10 goto 32		movq	-224(%rbp),	%rdx
		cmp	$0,	%rdx
		jne	L32

		# to 		jmp	L46

		# 1 = j * 4		movq	-128(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-232(%rbp)

		# 1 = array + t11		movq	-200(%rbp),	%rdx
		add	-232(%rbp),	%rdx
		movq	%rdx,	-232(%rbp)

		# mp = *t11		movq	-232(%rbp),	%rdx
		movq	(%rdx),	%rdx
		movq	%rdx,	-240(%rbp)

		# 2 = j + 1
		# 2 = j + 1		movq	%rdx,	-248(%rbp)

		# 3 = t12 * 4		movq	-248(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-256(%rbp)

		# 3 = array + t13		movq	-200(%rbp),	%rdx
		add	-256(%rbp),	%rdx
		movq	%rdx,	-256(%rbp)

		# 4 = j * 4		movq	-128(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-264(%rbp)

		# 4 = array + t14		movq	-200(%rbp),	%rdx
		add	-264(%rbp),	%rdx
		movq	%rdx,	-264(%rbp)

		# 14 = *t13		movq	-256(%rbp),	%rdx
		movq	(%rdx),	%rdx
		movq	-264(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 5 = j + 1
		# 5 = j + 1		movq	%rdx,	-272(%rbp)

		# 6 = t15 * 4		movq	-272(%rbp),	%rdx
		imul	$4,	%rdx
		movq	%rdx,	-280(%rbp)

		# 6 = array + t16		movq	-200(%rbp),	%rdx
		add	-280(%rbp),	%rdx
		movq	%rdx,	-280(%rbp)

		# 16 = temp		movq	-240(%rbp),	%rdx
		movq	-280(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# apped = True		movq	-288(%rbp),	%rdx
		movq	%rdx,	0(%rbp)

		# 7 = j + 1		movq	-128(%rbp),	%rdx
		add	$1,	%rdx
		movq	%rdx,	-296(%rbp)

		# = t17		movq	-296(%rbp),	%rdx
		movq	%rdx,	-128(%rbp)

		# to 21		jmp	L21

		# 8 = i + 1		movq	-64(%rbp),	%rdx
		add	$1,	%rdx
		movq	%rdx,	-304(%rbp)

		# = t18		movq	-304(%rbp),	%rdx
		movq	%rdx,	-64(%rbp)

		# to 11		jmp	L11

		# dfunc bubbleSort_int
		# ginfunc mainmain:
func3:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		subq	$152,	%rsp

		# ram 20		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	$20

		# ll memalloc 1		call	func4
		add	$8,	%rsp

		# pparam t19
		# ta = t19		movq	-64(%rbp),	%rdx
		movq	%rdx,	-112(%rbp)

		# 19 = 2		movq	-72(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 9 = t19 + 4		movq	-64(%rbp),	%rdx
		add	$4,	%rdx
		movq	%rdx,	-64(%rbp)

		# 19 = 45		movq	-80(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 9 = t19 + 4		movq	-64(%rbp),	%rdx
		add	$4,	%rdx
		movq	%rdx,	-64(%rbp)

		# 19 = 0		movq	-88(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 9 = t19 + 4		movq	-64(%rbp),	%rdx
		add	$4,	%rdx
		movq	%rdx,	-64(%rbp)

		# 19 = 11		movq	-96(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 9 = t19 + 4		movq	-64(%rbp),	%rdx
		add	$4,	%rdx
		movq	%rdx,	-64(%rbp)

		# 19 = 9		movq	-104(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	(%rcx)

		# 9 = t19 + 4		movq	-64(%rbp),	%rdx
		add	$4,	%rdx
		movq	%rdx,	-64(%rbp)

		# ram data		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	-112(%rbp)

		# ackptr +4
		# ll bubbleSort_int 1		call	func1
		add	$8,	%rsp

		# 0 return_value		movq	%rax,	0(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax

		# ram 'Sorted:'		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	-128(%rbp)

		# ackptr +8
		# ll print@any 1		call	func5
		add	$8,	%rsp

		# 1 return_value		movq	%rax,	0(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax

		# = 0		movq	$0,	%rdx
		movq	%rdx,	-144(%rbp)

		# ram data		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	-112(%rbp)

		# ackptr +4
		# ll len@any 1		call	func2
		add	$8,	%rsp

		# 2 return_value		movq	%rax,	0(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax

		# = t22		movq	-152(%rbp),	%rdx
		movq	%rdx,	-160(%rbp)

		# = 0		movq	$0,	%rdx
		movq	%rdx,	-144(%rbp)

		# 3 = l		movq	-168(%rbp),	%rdx
		movq	%rdx,	-176(%rbp)

		# 4 = i < t23		movq	-144(%rbp),	%rdx
		movq	-176(%rbp),	%rcx
		cmp	%rdx,	%rcx
		jg	1f
		movq	$0,	%rdx
		jmp	2f
1:
		movq	$1,	%rdx
		jmp	2f
2:
		movq	%rdx,	-184(%rbp)

		#  t24 goto 87		movq	-184(%rbp),	%rdx
		cmp	$0,	%rdx
		jne	L87

		# to 		jmp	L94

		# ram data		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		pushq	-112(%rbp)

		# ackptr +4
		# ll print@any 1		call	func5
		add	$8,	%rsp

		# 5 return_value		movq	%rax,	0(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax

		# 6 = i + 1		movq	-144(%rbp),	%rdx
		add	$1,	%rdx
		movq	%rdx,	-200(%rbp)

		# = t26		movq	-200(%rbp),	%rdx
		movq	%rdx,	-144(%rbp)

		# to 84		jmp	L84

		# dfunc main