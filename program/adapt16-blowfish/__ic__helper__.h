#ifndef _IC_HELPER_H_
#define _IC_HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BF_ENCRYPT	1
#define BF_DECRYPT	0

/* If you make this 'unsigned int' the pointer variants will work on
 * the Alpha, otherwise they will not.  Strangly using the '8 byte'
 * BF_LONG and the default 'non-pointer' inner loop is the best configuration
 * for the Alpha */
#define BF_LONG unsigned long

#define BF_ROUNDS	16
#define BF_BLOCK	8

typedef struct bf_key_st
{
   BF_LONG P[BF_ROUNDS+2];
   BF_LONG S[4*256];
} BF_KEY;

void BF_ENC(BF_LONG LL, BF_LONG R, BF_LONG *S, BF_LONG P);
void BF_encrypt(BF_LONG *data,BF_KEY *key,int encrypt);
unsigned long long current_time_in_nanos();

#undef n2l
#define n2l(c,l)        (l =((unsigned long)(*((c)++)))<<24L, \
      l|=((unsigned long)(*((c)++)))<<16L, \
      l|=((unsigned long)(*((c)++)))<< 8L, \
      l|=((unsigned long)(*((c)++))))

#undef l2n
#define l2n(l,c)        (*((c)++)=(unsigned char)(((l)>>24L)&0xff), \
      *((c)++)=(unsigned char)(((l)>>16L)&0xff), \
      *((c)++)=(unsigned char)(((l)>> 8L)&0xff), \
      *((c)++)=(unsigned char)(((l)     )&0xff))


#endif

