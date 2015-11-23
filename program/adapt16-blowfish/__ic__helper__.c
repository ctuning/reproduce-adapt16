#include "__ic__helper__.h"

unsigned long long current_time_in_nanos(){
  struct timespec res;
  // CLOCK_THREAD_CPUTIME_ID, CLOCK_MONOTONIC
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &res);

  return 1e9 * res.tv_sec + (long) res.tv_nsec;
}

void BF_ENC(BF_LONG LL, BF_LONG R, BF_LONG *S, BF_LONG P)
{
   LL^=P;
   LL^=(((  S[        (R>>24L)]       +
               S[0x0100+((R>>16L)&0xff)])^
            S[0x0200+((R>> 8L)&0xff)])+
         S[0x0300+((R     )&0xff)])&0xffffffff;
}
void BF_encrypt(data,key,encrypt)
   BF_LONG *data;
   BF_KEY *key;
   int encrypt;
{
   register BF_LONG l,r,*p,*s;

   p=key->P;
   s= &(key->S[0]);
   l=data[0];
   r=data[1];

   if (encrypt)
   {
      l^=p[0];
      BF_ENC(r,l,s,p[ 1]);
      BF_ENC(l,r,s,p[ 2]);
      BF_ENC(r,l,s,p[ 3]);
      BF_ENC(l,r,s,p[ 4]);
      BF_ENC(r,l,s,p[ 5]);
      BF_ENC(l,r,s,p[ 6]);
      BF_ENC(r,l,s,p[ 7]);
      BF_ENC(l,r,s,p[ 8]);
      BF_ENC(r,l,s,p[ 9]);
      BF_ENC(l,r,s,p[10]);
      BF_ENC(r,l,s,p[11]);
      BF_ENC(l,r,s,p[12]);
      BF_ENC(r,l,s,p[13]);
      BF_ENC(l,r,s,p[14]);
      BF_ENC(r,l,s,p[15]);
      BF_ENC(l,r,s,p[16]);
#if BF_ROUNDS == 20
      BF_ENC(r,l,s,p[17]);
      BF_ENC(l,r,s,p[18]);
      BF_ENC(r,l,s,p[19]);
      BF_ENC(l,r,s,p[20]);
#endif
      r^=p[BF_ROUNDS+1];
   }
   else
   {
      l^=p[BF_ROUNDS+1];
#if BF_ROUNDS == 20
      BF_ENC(r,l,s,p[20]);
      BF_ENC(l,r,s,p[19]);
      BF_ENC(r,l,s,p[18]);
      BF_ENC(l,r,s,p[17]);
#endif
      BF_ENC(r,l,s,p[16]);
      BF_ENC(l,r,s,p[15]);
      BF_ENC(r,l,s,p[14]);
      BF_ENC(l,r,s,p[13]);
      BF_ENC(r,l,s,p[12]);
      BF_ENC(l,r,s,p[11]);
      BF_ENC(r,l,s,p[10]);
      BF_ENC(l,r,s,p[ 9]);
      BF_ENC(r,l,s,p[ 8]);
      BF_ENC(l,r,s,p[ 7]);
      BF_ENC(r,l,s,p[ 6]);
      BF_ENC(l,r,s,p[ 5]);
      BF_ENC(r,l,s,p[ 4]);
      BF_ENC(l,r,s,p[ 3]);
      BF_ENC(r,l,s,p[ 2]);
      BF_ENC(l,r,s,p[ 1]);
      r^=p[0];
   }
   data[1]=l&0xffffffff;
   data[0]=r&0xffffffff;
}
