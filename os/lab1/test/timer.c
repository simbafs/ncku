#include "../internal/timer.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  Timer timer;

  int testCase[] = {1, 2, 3};
  int n = sizeof(testCase) / sizeof(int);

  int total = 0;

  for (int i = 0; i < n; i++) {
    total += testCase[i];
    Timer_Start(&timer);
    sleep(testCase[i]);
    Timer_End(&timer);
  }

  printf("expected: %d, got: %lf\n", total, timer.Total);
}
