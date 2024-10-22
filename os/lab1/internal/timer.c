#include "timer.h"
#include <time.h>

void Timer_Start(Timer *timer) {
  clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

void Timer_End(Timer *timer) {
  clock_gettime(CLOCK_MONOTONIC, &timer->end);

  timer->Total += (timer->end.tv_sec - timer->start.tv_sec) +
                  (timer->end.tv_nsec - timer->start.tv_nsec) / 1e9;
}
