#include <stdio.h>
int main() {
  int i = 0;
  int h[9] = {0}, x[6] = {0}, y[6] = {0};
  FILE *input = fopen("../input/4.txt", "r");
  for (i = 0; i < 9; i++)
    fscanf(input, "%d", &h[i]);
  for (i = 0; i < 6; i++)
    fscanf(input, "%d", &x[i]);
  for (i = 0; i < 6; i++)
    fscanf(input, "%d", &y[i]);
  fclose(input);

  int *p_x = &x[0];
  int *p_h = &h[0];
  int *p_y = &y[0];

  asm volatile(

      "addi s1, zero, 0 \n\t" // i = 0"
      "addi s2, zero, 3 \n\t" // upper bound of i
      "loop1:"
      "bge s1, s2, end1 \n\t"

      "addi s3, zero, 0 \n\t" // j = 0"
      "addi s4, zero, 2 \n\t" // upper bound of j
      "loop2:"
      "bge s3, s4, end2 \n\t"

      "addi s5, zero, 0 \n\t" // k = 0"
      "addi s6, zero, 3 \n\t" // upper bound of j
      "loop3:"
      "bge s5, s6, end3 \n\t"

      // begin of loop body

      // t0 = 2 * i + j
      "add t0, s1, s1 \n\t"
      "add t0, t0, s3 \n\t"
      "slli t0, t0, 2 \n\t"
      "add t0, t0, %[p_y] \n\t"

      // t1 = 3 * i + k
      "add t1, s1, s1 \n\t"
      "add t1, t1, s1 \n\t"
      "add t1, t1, s5 \n\t"
      "slli t1, t1, 2 \n\t"
      "add t1, t1, %[p_h] \n\t"

      // t2 = 2 * k + j
      "add t2, s5, s5 \n\t"
      "add t2, t2, s3 \n\t"
      "slli t2, t2, 2 \n\t"
      "add t2, t2, %[p_x] \n\t"

      "lw t3, 0(t0) \n\t" // y[2 * i + j]
      "lw t4, 0(t1) \n\t" // h[3 * i + k]
      "lw t5, 0(t2) \n\t" // x[j + 2 * k]

      "mul t4, t4, t5 \n\t" // t3 = t1 * t2"
      "add t3, t3, t4 \n\t" // t0 = t0 + t3"

      "sw t3, 0(t0) \n\t" // y[2 * i + j] = t0"

      // end of loop body

      "addi s5, s5, 1 \n\t" // k++"
      "jal zero, loop3 \n\t"
      "end3:"

      "addi s3, s3, 1 \n\t" // j++"
      "jal zero, loop2 \n\t"
      "end2:"

      "addi s1, s1, 1 \n\t" // i++"
      "jal zero, loop1 \n\t"
      "end1:"

      : [p_y] "+r"(p_y), [p_h] "+r"(p_h), [p_x] "+r"(p_x)

  );

  p_y = &y[0];
  for (i = 0; i < 6; i++)
    printf("%d ", *p_y++);
  printf("\n");
  return 0;
}
