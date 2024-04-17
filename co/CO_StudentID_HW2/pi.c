"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"li t1, 0 \n\t" // t1 = i = 0

"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t3, zero, -1 \n\t" // t3 = 1
"loop: \n\t"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"bge t1, %[N], end \n\t" // if i >= N, end

"addi %[add_cnt], %[add_cnt], 1\n\t"
"add t2, zero, t1 \n\t" // t2 = i
"addi %[others_cnt], %[others_cnt], 1\n\t"
"slli t2, t2, 1 \n\t" // t2 = 2 * i
"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t2, t2, 1 \n\t" // t2 = 2 * i + 1

"addi %[sub_cnt], %[sub_cnt], 1\n\t"
"sub t3, zero, t3 \n\t" // t3 = -t3

"addi %[others_cnt], %[others_cnt], 1\n\t"
"fcvt.d.w f1, t2 \n\t" // f1 = t2
"addi %[others_cnt], %[others_cnt], 1\n\t"
"fcvt.d.w f2, t3 \n\t" // f2 = t3

"addi %[div_cnt], %[div_cnt], 1\n\t"
"fdiv.d f1, f2, f1 \n\t" // f1 = f2 / f1

"addi %[add_cnt], %[add_cnt], 1\n\t"
"fadd.d %[pi], %[pi], f1 \n\t" // pi += f1

"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t1, t1, 1 \n\t" // i++"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"jal zero, loop \n\t"

"end: \n\t"
