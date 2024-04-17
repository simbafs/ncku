/*
 * This file is just for illustrate the concept of the conv2d.S code.
 * There is no need to modify this file.
 */
// void conv2d(int *input, int *kernel, int w, int h, int ksize, int s) {
//   for (int j = 0; j <= w - ksize; j++) {
//     for (int i = 0; i <= h - ksize; i++) {
//       int sum = 0;
//       for (int n = 0; n < ksize; n += s) {
//         for (int m = 0; m < ksize; m += s) {
//           sum += input[(i + m) * w + j + n] * kernel[m * ksize + n];
//         }
//       }
//       input[i * w + j] = sum;
//     }
//   }
// }

void conv2d(int *input, int *kernel, int w, int h, int ksize, int s) {
  int w_ksize = w - ksize;
  int h_ksize = h - ksize;

  int s0 = kernel[0];
  int s1 = kernel[1];
  int s2 = kernel[2];
  int s3 = kernel[3];
  int s4 = kernel[4];
  int s5 = kernel[5];
  int s6 = kernel[6];
  int s7 = kernel[7];
  int s8 = kernel[8];

  for (int j = 0; j <= w_ksize; j++) {
    for (int i = 0; i <= h_ksize; i++) {
      int sum = 0;
      int idx = i * w + j;

      int k = idx;
      sum += input[k] * s0;
      k = k + 1;
      sum += input[k] * s1;
      k = k + 1;
      sum += input[k] * s2;

      k = idx + w;
      sum += input[k] * s3;
      k = k + 1;
      sum += input[k] * s4;
      k = k + 1;
      sum += input[k] * s5;

      k = idx + w + w;
      sum += input[k] * s6;
      k = k + 1;
      sum += input[k] * s7;
      k = k + 1;
      sum += input[k] * s8;

      input[idx] = sum;
    }
  }
}
