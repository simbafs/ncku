"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi t0, zero, 8 \n\t"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"vsetvli t0, t0, e16, m1\n\t" // init vector

"addi %[others_cnt], %[others_cnt], 1\n\t"
"slli t0, %[arr_size], 1 \n\t"
"addi %[add_cnt], %[add_cnt], 1\n\t"
"add t0, %[y], t0 \n\t"

"loop: \n\t"

"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"vle16.v v1, (%[h])\n\t" // Load vector from h
"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"vle16.v v2, (%[x])\n\t" // Load vector from x

"addi %[mul_cnt], %[mul_cnt], 1\n\t"
"vmul.vv v3, v1, v2\n\t" // v3 = v1 * v2
"addi %[add_cnt], %[add_cnt], 1\n\t"
"vadd.vx v3, v3, %[id]\n\t" // v4 = v3 + id

"addi %[sw_cnt], %[sw_cnt], 1\n\t"
"vse16.v v3, (%[y])\n\t" // Store the result vector to y

"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[h], %[h], 16 \n\t"
"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[x], %[x], 16 \n\t"
"addi %[add_cnt], %[add_cnt], 1\n\t"
"addi %[y], %[y], 16 \n\t"

"addi %[others_cnt], %[others_cnt], 1\n\t"
"bgt t0, %[y], loop \n\t" // if t0 >= y, loop
