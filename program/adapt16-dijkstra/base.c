#ifdef XOPENME
#include <xopenme.h>
#endif

#include "base_hf1.h"
#include "__ic__helper__.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * PROXY HF1
 */
int dijkstra(int a, int b) {
   static unsigned int __hfrun  = 0;
   unsigned long long s,e;

   // On first invocation
   ++__hfrun;
   s = current_time_in_nanos();

   int res = hot_function1(a, b);

   e = current_time_in_nanos();
   if(__hfrun==1){ 
      printf("Exec time: %llu\n", (e-s));
   }


   return res;
}

int output[NUM_NODES * NUM_NODES];
int output_count = 0;

int main(){
  long ct_repeat=0;
  long ct_repeat_max=1;
  int ct_return=0;

   int i,j;

#ifdef XOPENME
  xopenme_init(1,2);
#endif

  if (getenv("CT_REPEAT_MAIN")!=NULL) ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));

#ifdef XOPENME
  xopenme_clock_start(0);
#endif

  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {

   output_count = 0;

   /* finds 10 shortest paths between nodes */
   for(j = 0; j < NUM_NODES; j++) {
      for (i=0; i < NUM_NODES; i++) {
         output[output_count] = dijkstra(i,j);
         output_count++;
      }
   }

  }

#ifdef XOPENME
  xopenme_clock_end(0);
  xopenme_dump_state();
  xopenme_finish();
#endif

   return 0;
}



/* vim: set ts=3 sw=3 et: */
