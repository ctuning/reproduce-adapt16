#include "__ic__helper__.h"

unsigned long long current_time_in_nanos(){
  struct timespec res;
  // CLOCK_THREAD_CPUTIME_ID, CLOCK_MONOTONIC
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &res);

  return 1e9 * res.tv_sec + (long) res.tv_nsec;
}
