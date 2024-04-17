.global conv2d
conv2d:
# a0: address of input
# a1: address of kernel
# a2: w
# a3: h
# a4: ksize
# a5: s

# content
	addi sp, sp, -48
	sw a6, 44(sp) # debug flag
	sw s11, 40(sp)
	sw s10, 36(sp)
	sw s9, 32(sp)
	sw s8, 28(sp)
	sw s7, 24(sp)
	sw s6, 20(sp)
	sw s5, 16(sp)
	sw s4, 12(sp)
	sw s3, 8(sp)
	sw s2, 4(sp)
	sw s1, 0(sp)

	li a6, 0

	# load kernal elements
	lw s1, 0(a1)
	lw s2, 4(a1)
	lw s3, 8(a1)
	lw s4, 12(a1)
	lw s5, 16(a1)
	lw s6, 20(a1)
	lw s7, 24(a1)
	lw s8, 28(a1)
	lw s9, 32(a1)

	sub t0, a2, a4 # w - ksize
	sub t1, a3, a4 # h - ksize

	li  t2, 0 # j = 0
one:
	li  t3, 0 # i = 0
two:
	li  t4, 0 # sum = 0

	li a6, 0x123 # a flag for debugging

	# idx = i * w + j
	mul t5, t3, a2
	add t5, t5, t2
	slli t5, t5, 2 # idx = idx * 4
	add t5, t5, a0 # input[idx]

	slli a2, a2, 2 # w = w * 4

	add t6, t5, zero # k = idx

	lw s10, 0(t6) # input[k]

	mul s10, s10, s1 # input[k] * kernel[0]
	add t4, t4, s10 # sum += input[k] * kernel[0]
	
	lw s10, 4(t6) # input[k+1]
	mul s10, s10, s2 # input[k+1] * kernel[1]
	add t4, t4, s10 # sum += input[k+1] * kernel[1]
	
	lw s10, 8(t6) # input[k+2]
	mul s10, s10, s3 # input[k+2] * kernel[2]
	add t4, t4, s10 # sum += input[k+2] * kernel[2]
	
	add t6, t6, a2 # k = k + w
	
	lw s10, 0(t6) # input[k+w]
	mul s10, s10, s4 # input[k+w] * kernel[3]
	add t4, t4, s10 # sum += input[k+w] * kernel[3]
	
	lw s10, 4(t6) # input[k+w+1]
	mul s10, s10, s5 # input[k+w+1] * kernel[4]
	add t4, t4, s10 # sum += input[k+w+1] * kernel[4]
	
	lw s10, 8(t6) # input[k+w+2]
	mul s10, s10, s6 # input[k+w+2] * kernel[5]
	add t4, t4, s10 # sum += input[k+w+2] * kernel[5]
	
	add t6, t6, a2 # k = k + w
	
	lw s10, 0(t6) # input[k+2w]
	mul s10, s10, s7 # input[k+2w] * kernel[6]
	add t4, t4, s10 # sum += input[k+2w] * kernel[6]
	
	lw s10, 4(t6) # input[k+2w+1]
	mul s10, s10, s8 # input[k+2w+1] * kernel[7]
	add t4, t4, s10 # sum += input[k+2w+1] * kernel[7]
	
	lw s10, 8(t6) # input[k+2w+2]
	mul s10, s10, s9 # input[k+2w+2] * kernel[8]
	add t4, t4, s10 # sum += input[k+2w+2] * kernel[8]
	
	sw t4, 0(t5) # input[idx] = sum
	
	srli a2, a2, 2 # w = w / 4

	li a6, 0x456 # a flag for debugging

	addi t3, t3, 1 # i++
	ble t3, t1, two # if i < h-ksize then goto tag 2
	
	addi t2, t2, 1 # j++
	ble t2, t0, one # if j < w-ksize then goto tag 1

	# lw zero, 0(zero)
	
	lw a6, 44(sp)
	lw s11, 40(sp)
	lw s10, 36(sp)
	lw s9, 32(sp)
	lw s8, 28(sp)
	lw s7, 24(sp)
	lw s6, 20(sp)
	lw s5, 16(sp)
	lw s4, 12(sp)
	lw s3, 8(sp)
	lw s2, 4(sp)
	lw s1, 0(sp)
	
	addi sp, sp, 48

	ret
