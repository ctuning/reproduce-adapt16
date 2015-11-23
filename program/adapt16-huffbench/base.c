#include "base_hf1.h"
#include "__ic__helper__.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>


// embedded random number generator; ala Park and Miller
static       long seed = 1325;
static const long IA   = 16807;
static const long IM   = 2147483647;
static const long IQ   = 127773;
static const long IR   = 2836;
static const long MASK = 123459876;

// return index between 0 and 3
static size_t random4()
{
	long k;
	size_t result;

	seed ^= MASK;
	k = seed / IQ;
	seed = IA * (seed - k * IQ) - IR * k;

	if (seed < 0L)
		seed += IM;

	result = (size_t)(seed % 32L);
	seed ^= MASK;

	return result;
}


// compressed (encoded) data

byte * generate_test_data(size_t n)
{
	char * codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345";

	byte * result = (byte *)malloc(n);
	byte * ptr = result;

	int i;
	for (i = 0; i < n; ++i)
	{
		*ptr = (byte)codes[random4()];
		++ptr;
	}

	return result;
}




/*
 * PROXY HF1
 */
void compdecomp(byte * data, size_t data_len){
   static unsigned int __hfrun  = 0;
   unsigned long long s,e;

   // On first invocation
   ++__hfrun;
   s = current_time_in_nanos();


	hot_function1(data, data_len);

   e = current_time_in_nanos();
   if(__hfrun==1){ 
      printf("Exec time: %llu\n", (e-s));
   }

}




int main(){
	// initialization
	byte * test_data = generate_test_data(TEST_SIZE);

	// what we're timing
	int j;
	for(j=0; j<100; j++){
		compdecomp(test_data,TEST_SIZE);
	}

	// release resources
	free(test_data);

	// done
	return 0;
}

