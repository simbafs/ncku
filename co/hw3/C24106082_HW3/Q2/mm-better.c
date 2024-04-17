void matrix_multiplication(int *a, int *b, int *output, int I, int K, int J) {
  int ii = 0;
  for (int i = 0; i < I; i += 2) {
    ii = i + 1;
    if (ii == I) {
      for (int j = 0; j < J; j++) {
        int sum1 = 0;
        // printf("i: %d, j: %d, k: %d, J-1: %d\n", i, j, K, J - 1);

        for (int k = 0; k < K; k++) {
          sum1 += a[i * K + k] * b[k * J + j];
        }
        output[i * J + j] = sum1;
      }
    } else {
      for (int j = 0; j < J; j++) {
        int sum1 = 0;
        int sum2 = 0;
        // printf("i: %d, j: %d, k: %d, J-1: %d\n", i, j, K, J - 1);

        for (int k = 0; k < K; k++) {
          sum1 += a[i * K + k] * b[k * J + j];
          sum2 += a[ii * K + k] * b[k * J + j];
        }
        output[i * J + j] = sum1;
        output[ii * J + j] = sum2;
      }
    }
  }
  return;
}
