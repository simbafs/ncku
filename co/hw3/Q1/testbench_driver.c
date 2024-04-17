#define W 256
#define H 256
// #define W 5
// #define H 5
#define K 3

#include <stdio.h>

#define GOLDEN_RATIO_32 0x61C88647
static inline int hash_32(int val) { return (val * GOLDEN_RATIO_32) >> 22; }

extern void conv2d(int (*input)[W], int (*kernel)[K], int w, int h, int ksize,
                   int s);

int main(int argc, char *argv[]) {
  // int input[H][W] = {{1, 2, 3, 4, 5},
  //                    {6, 7, 8, 9, 10},
  //                    {11, 12, 13, 14, 15},
  //                    {16, 17, 18, 19, 20},
  //                    {21, 22, 23, 24, 25}};
  int input[H][W];
  int kernel[K][K];

  // the start and the end of input
  // printf("%p, %p, %d\n", input, &(input[H - 1][W - 1]), input[H - 1][W - 1]);
  // int *p = (int *)input + 5;
  // printf("%p -> %d\n", p, *p);

  int seed = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++)
      input[i][j] = hash_32(i * W + j);
  }

  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++)
      kernel[i][j] = 1;
  }

  conv2d(input, kernel, W, H, K, 1);

  if (argc == 2) {
    FILE *f = fopen(argv[1], "w");
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        fprintf(f, "%d ", input[i][j]);
      }
      fprintf(f, "\n");
    }
    fclose(f);
  }

  return 0;
}
