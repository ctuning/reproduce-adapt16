#ifdef XOPENME
#include <xopenme.h>
#endif

#include "base_hf1.h"
#include "__ic__helper__.h"

int fft1(int n, int flag);


/*
 * PROXY HF1
 */
int fft1(int n, int flag){
   static unsigned int __hfrun  = 0;
   unsigned long long s,e;

   // On first invocation
   ++__hfrun;
   s = current_time_in_nanos();

	int res = hot_function1(n, flag);

   e = current_time_in_nanos();
   if(__hfrun==1){ 
      printf("Exec time: %llu\n", (e-s));
   }


	return res;
}




int main(){
  long ct_repeat=0;
  long ct_repeat_max=1;
  int ct_return=0;

    int  i, n = 64, flag, chkerr;

#ifdef XOPENME
  xopenme_init(1,2);
#endif

  if (getenv("CT_REPEAT_MAIN")!=NULL) ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));

    /* ar  */
    for(i = 0; i < n; i++)
      ar[i] = cos(2*M_PI*i/n);

#ifdef XOPENME
  xopenme_clock_start(0);
#endif

  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
    /* forward fft */
    flag = 0;
    chkerr = fft1(n, flag);

    /* inverse fft */
    flag = 1;
    chkerr = fft1(n, flag);

  }

#ifdef XOPENME
  xopenme_clock_end(0);
  xopenme_dump_state();
  xopenme_finish();
#endif

    (void) chkerr; /* Silence compiler about unused 'chkerr'.  */

    return 0;
}
