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
    int  i, n = 64, flag, chkerr;

    /* ar  */
    for(i = 0; i < n; i++)
      ar[i] = cos(2*M_PI*i/n);

    /* forward fft */
    flag = 0;
    chkerr = fft1(n, flag);

    /* inverse fft */
    flag = 1;
    chkerr = fft1(n, flag);

    (void) chkerr; /* Silence compiler about unused 'chkerr'.  */

    return 0;
}
