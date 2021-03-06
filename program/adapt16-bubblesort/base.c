#ifdef XOPENME
#include <xopenme.h>
#endif

#include "base_hf1.h"
#include "__ic__helper__.h"

#define SCALE_FACTOR    (REPEAT_FACTOR >> 4)

#define MAXDIM   (NUMELEMS+1)

void Initialize(int Array []);
void BubbleSort(int Array []);

/* BUBBLESORT BENCHMARK PROGRAM:
 * This program tests the basic loop constructs, integer comparisons,
 * and simple array handling of compilers by sorting 10 arrays of
 * randomly generated integers.
 */

int Array[MAXDIM], Seed;
int factor;

void BubbleSort(int Array[]);
void Initialize(int Array[]);


void Initialize(int Array[])
/*
 * Initializes given array with randomly generated integers.
 */
{
   int  Index, fact;

#ifdef WORSTCASE
   factor = -1;
#else
   factor = 1;
#endif

fact = factor;
for (Index = 1; Index <= NUMELEMS; Index ++)
    Array[Index] = Index*fact;
}


/*
 * PROXY HF1
 */
void BubbleSort(int Array[]){
   static unsigned int __hfrun  = 0;
   unsigned long long s,e;

   // On first invocation
   ++__hfrun;
   s = current_time_in_nanos();


	hot_function1(Array);

   e = current_time_in_nanos();
   if(__hfrun==1){ 
      printf("Exec time: %llu\n", (e-s));
   }
}




int main(){
  long ct_repeat=0;
  long ct_repeat_max=1;
  int ct_return=0;

#ifdef XOPENME
  xopenme_init(1,2);
#endif

  if (getenv("CT_REPEAT_MAIN")!=NULL) ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));

#ifdef XOPENME
  xopenme_clock_start(0);
#endif

  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
   Initialize(Array);
   BubbleSort(Array);
  }

#ifdef XOPENME
  xopenme_clock_end(0);
  xopenme_dump_state();
  xopenme_finish();
#endif

   return 0;
}


