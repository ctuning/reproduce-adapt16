#include "__ic__helper__.h"

unsigned long long current_time_in_nanos(){
  struct timespec res;
  // CLOCK_THREAD_CPUTIME_ID, CLOCK_MONOTONIC
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &res);

  return 1e9 * res.tv_sec + (long) res.tv_nsec;
}
double fabs(double n){
  double f;

  if (n >= 0) f = n;
  else f = -n;
  return f;
}


double sin(double rad){
  double app;

  double diff;
  int inc = 1;

  while (rad > 2*PI)
	rad -= 2*PI;
  while (rad < -2*PI)
    rad += 2*PI;
  app = diff = rad;
   diff = (diff * (-(rad*rad))) /
      ((2.0 * inc) * (2.0 * inc + 1.0));
    app = app + diff;
    inc++;
  while(fabs(diff) >= 0.00001) {
    diff = (diff * (-(rad*rad))) /
      ((2.0 * inc) * (2.0 * inc + 1.0));
    app = app + diff;
    inc++;
  }

  return(app);
}
double cos(double rad)
{
  double sin();

  return (sin (PI / 2.0 - rad));
}
