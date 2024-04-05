#include <stdio.h>
int main() {
  int f, i, j;
  int h[9] = {0}, x[6] = {0}, y[6] = {0};
  FILE *input = fopen("../input/3.txt", "r");
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
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      for (f = 0; f < 3; f++)
        asm volatile(

            // t0 = 2 * i + j
            "add t0, %[i], %[i] \n\t"
            "add t0, t0, %[j] \n\t"
            "slli t0, t0, 2 \n\t"
            "add t0, t0, %[p_y] \n\t"

            // t1 = 3 * i + k
            "add t1, %[i], %[i] \n\t"
            "add t1, t1, %[i] \n\t"
            "add t1, t1, %[k] \n\t"
            "slli t1, t1, 2 \n\t"
            "add t1, t1, %[p_h] \n\t"

            // t2 = 2 * k + j
            "add t2, %[k], %[k] \n\t"
            "add t2, t2, %[j] \n\t"
            "slli t2, t2, 2 \n\t"
            "add t2, t2, %[p_x] \n\t"

            "lw t3, 0(t0) \n\t" // y[2 * i + j]
            "lw t4, 0(t1) \n\t" // h[3 * i + k]
            "lw t5, 0(t2) \n\t" // x[j + 2 * k]

            "mul t4, t4, t5 \n\t" // t3 = t1 * t2"
            "add t3, t3, t4 \n\t" // t0 = t0 + t3"

            "sw t3, 0(t0) \n\t" // y[2 * i + j] = t0"
            : [p_y] "+r"(p_y), [p_h] "+r"(p_h), [p_x] "+r"(p_x)
            : [i] "r"(i), [j] "r"(j), [k] "r"(f)

        );
    }
  }
  p_y = &y[0];
  for (i = 0; i < 6; i++)
    printf("%d ", *p_y++);
  printf("\n");
  return 0;
}
