"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t0, zero, 0 \n\t" // init t0 = i = 0
"loop: \n\t"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"bge t0, %[arr_size], end \n\t" // if i >= arr_size, end loop

"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"lw t1, 0(%[h]) \n\t"
"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"lw t2, 0(%[x]) \n\t"
"addi %[mul_cnt], %[mul_cnt], 1\n\t"
"mul t1, t1, t2 \n\t"

"addi %[add_cnt], %[add_cnt], 1\n\t"
"add t1, t1, %[id] \n\t"

"addi %[sw_cnt], %[sw_cnt], 1\n\t"
"sw t1, 0(%[y]) \n\t"

"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[h], %[h], 2 \n\t"
"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[x], %[x], 2 \n\t"
"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[y], %[y], 2 \n\t"

"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t0, t0, 1 \n\t" // i++
"addi %[others_cnt], %[others_cnt], 1\n\t"
"jal zero, loop \n\t"

"end: \n\t"
