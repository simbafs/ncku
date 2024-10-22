#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct {
  struct timespec start;
  struct timespec end;

  double Total;
} Timer;

void Timer_Start(Timer *timer);
void Timer_End(Timer *timer);

#endif
