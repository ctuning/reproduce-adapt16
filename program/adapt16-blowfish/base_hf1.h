#ifndef _HOT_FUNCTION_1_
#define _HOT_FUNCTION_1_

#include "__ic__helper__.h"

void hot_function1(unsigned char *in, unsigned char *out, long length,
		BF_KEY *schedule, unsigned char *ivec, int *num, int encrypt);

#endif
