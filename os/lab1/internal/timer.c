#include "timer.h"
#include <time.h>

void Timer_Init(Timer *timer) { timer->Total = 0; }

void Timer_Start(Timer *timer) {
  clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

void Timer_End(Timer *timer) {
  clock_gettime(CLOCK_MONOTONIC, &timer->end);

  double time = (timer->end.tv_sec - timer->start.tv_sec)*1e6 +
                (timer->end.tv_nsec - timer->start.tv_nsec) / 1e3;

  timer->Total += time;
}
