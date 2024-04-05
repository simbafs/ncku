#include <stdio.h>
int main() {
  int a[10] = {0}, b[10] = {0}, c[10] = {0};
  int i, arr_size = 10;
  FILE *input = fopen("../input/2.txt", "r");
  for (i = 0; i < arr_size; i++)
    fscanf(input, "%d", &a[i]);
  for (i = 0; i < arr_size; i++)
    fscanf(input, "%d", &b[i]);
  for (i = 0; i < arr_size; i++)
    fscanf(input, "%d", &c[i]);
  fclose(input);
  int *p_a = &a[0];
  int *p_b = &b[0];
  int *p_c = &c[0];
  /* Original C code segment
  for (int i = 0; i < arr_size; i++){
      *p_c++ = *p_a++ * *p_b++;
  }
  */
  for (int i = 0; i < arr_size; i++)
    asm volatile(

        "lw t0, 0(%[pa]) \n\t"
        "lw t1, 0(%[pb]) \n\t"
        "mul t2, t0, t1 \n\t"
        "sw t2, 0(%[pc]) \n\t"
        "addi %[pc], %[pc], 4 \n\t"
        "addi %[pa], %[pa], 4 \n\t"
        "addi %[pb], %[pb], 4 \n\t"
        : [pc] "+r"(p_c), [pa] "+r"(p_a), [pb] "+r"(p_b)

    );
  p_c = &c[0];
  for (int i = 0; i < arr_size; i++)
    printf("%d ", *p_c++);
  printf("\n");
  return 0;
}
