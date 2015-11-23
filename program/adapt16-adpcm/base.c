#ifdef XOPENME
#include <xopenme.h>
#endif

#include "base_hf1.h"
#include "__ic__helper__.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


/* To be able to run with printouts
#include <stdio.h> */

/* common sampling rate for sound cards on IBM/PC */
#define SAMPLE_RATE 11025

#define PI 3141
#define SIZE 5
#define IN_END 4



/* function prototypes for fft and filter functions */
void fft(COMPLEX *,int);
int fir_filter(int input,int *coef,int n,int *history);
int iir_filter(int input,int *coef,int n,int *history);
int gaussian(void);
int getinput(void);
void sendout(int),flush();

void decode(int);
/* int invqxl(int il,int detl,int *code_table,int mode); */
/* int invqah(int ih,int deth); */
void reset();
int my_fabs(int n);
int my_cos(int n);
int my_sin(int n);


/* G722 encode function two ints in, one 8 bit output */

/* put input samples in xin1 = first value, xin2 = second value */
/* returns il and ih stored together */

/* MAX: 1 */
/* MAX: 1 */
int my_fabs(int n)
{
	int f;

	if (n >= 0) f = n;
	else f = -n;
	return f;
}

int my_sin(int rad)
{
	int diff;
	int app=0;

	int inc = 1;

	/* MAX dependent on rad's value, say 50 */
	while (rad > 2*PI)
		rad -= 2*PI;
	/* MAX dependent on rad's value, say 50 */
	while (rad < -2*PI)
		rad += 2*PI;
	diff = rad;
	app = diff;
	diff = (diff * (-(rad*rad))) /
		((2 * inc) * (2 * inc + 1));
	app = app + diff;
	inc++;
	/* REALLY: while(my_fabs(diff) >= 0.00001) { */
	/* MAX: 1000 */
	while(my_fabs(diff) >= 1) {
		diff = (diff * (-(rad*rad))) /
			((2 * inc) * (2 * inc + 1));
		app = app + diff;
		inc++;
	}

	return app;
}


int my_cos(int rad)
{
	return (my_sin (PI / 2 - rad));
}




/*
 * PROXY HF1
 */
int encode(int xin1,int xin2){
   static unsigned int __hfrun  = 0;
   unsigned long long s,e;

   // On first invocation
   ++__hfrun;
   s = current_time_in_nanos();

	int res = hot_function1(xin1, xin2);

   e = current_time_in_nanos();
   if(__hfrun==1){ 
      printf("Exec time: %llu\n", (e-s));
   }


	return res;
}





/* decode function, result in xout1 and xout2 */

void decode(int input)
{
	int i;
	long int xa1,xa2;    /* qmf accumulators */
	int *h_ptr,*ac_ptr,*ac_ptr1,*ad_ptr,*ad_ptr1;

	/* split transmitted word from input into ilr and ih */
	ilr = input & 0x3f;
	ih = input >> 6;

	/* LOWER SUB_BAND DECODER */

	/* filtez: compute predictor output for zero section */
	dec_szl = filtez(dec_del_bpl,dec_del_dltx);

	/* filtep: compute predictor output signal for pole section */
	dec_spl = filtep(dec_rlt1,dec_al1,dec_rlt2,dec_al2);

	dec_sl = dec_spl + dec_szl;

	/* invqxl: compute quantized difference signal for adaptive predic */
	dec_dlt = ((long)dec_detl*qq4_code4_table[ilr >> 2]) >> 15;

	/* invqxl: compute quantized difference signal for decoder output */
	dl = ((long)dec_detl*qq6_code6_table[il]) >> 15;

	rl = dl + dec_sl;

	/* logscl: quantizer scale factor adaptation in the lower sub-band */
	dec_nbl = logscl(ilr,dec_nbl);

	/* scalel: computes quantizer scale factor in the lower sub band */
	dec_detl = scalel(dec_nbl,8);

	/* parrec - add pole predictor output to quantized diff. signal */
	/* for partially reconstructed signal */
	dec_plt = dec_dlt + dec_szl;

	/* upzero: update zero section predictor coefficients */
	upzero(dec_dlt,dec_del_dltx,dec_del_bpl);

	/* uppol2: update second predictor coefficient apl2 and delay it as al2 */
	dec_al2 = uppol2(dec_al1,dec_al2,dec_plt,dec_plt1,dec_plt2);

	/* uppol1: update first predictor coef. (pole setion) */
	dec_al1 = uppol1(dec_al1,dec_al2,dec_plt,dec_plt1);

	/* recons : compute recontructed signal for adaptive predictor */
	dec_rlt = dec_sl + dec_dlt;

	/* done with lower sub band decoder, implement delays for next time */
	dec_rlt2 = dec_rlt1;
	dec_rlt1 = dec_rlt;
	dec_plt2 = dec_plt1;
	dec_plt1 = dec_plt;

	/* HIGH SUB-BAND DECODER */

	/* filtez: compute predictor output for zero section */
	dec_szh = filtez(dec_del_bph,dec_del_dhx);

	/* filtep: compute predictor output signal for pole section */
	dec_sph = filtep(dec_rh1,dec_ah1,dec_rh2,dec_ah2);

	/* predic:compute the predictor output value in the higher sub_band decoder */
	dec_sh = dec_sph + dec_szh;

	/* invqah: in-place compute the quantized difference signal */
	dec_dh = ((long)dec_deth*qq2_code2_table[ih]) >> 15L ;

	/* logsch: update logarithmic quantizer scale factor in hi sub band */
	dec_nbh = logsch(ih,dec_nbh);

	/* scalel: compute the quantizer scale factor in the higher sub band */
	dec_deth = scalel(dec_nbh,10);

	/* parrec: compute partially recontructed signal */
	dec_ph = dec_dh + dec_szh;

	/* upzero: update zero section predictor coefficients */
	upzero(dec_dh,dec_del_dhx,dec_del_bph);

	/* uppol2: update second predictor coefficient aph2 and delay it as ah2 */
	dec_ah2 = uppol2(dec_ah1,dec_ah2,dec_ph,dec_ph1,dec_ph2);

	/* uppol1: update first predictor coef. (pole setion) */
	dec_ah1 = uppol1(dec_ah1,dec_ah2,dec_ph,dec_ph1);

	/* recons : compute recontructed signal for adaptive predictor */
	rh = dec_sh + dec_dh;

	/* done with high band decode, implementing delays for next time here */
	dec_rh2 = dec_rh1;
	dec_rh1 = rh;
	dec_ph2 = dec_ph1;
	dec_ph1 = dec_ph;

	/* end of higher sub_band decoder */

	/* end with receive quadrature mirror filters */
	xd = rl - rh;
	xs = rl + rh;

	/* receive quadrature mirror filters implemented here */
	h_ptr = h;
	ac_ptr = accumc;
	ad_ptr = accumd;
	xa1 = (long)xd * (*h_ptr++);
	xa2 = (long)xs * (*h_ptr++);
	/* main multiply accumulate loop for samples and coefficients */
	for(i = 0 ; i < 10 ; i++) {
		xa1 += (long)(*ac_ptr++) * (*h_ptr++);
		xa2 += (long)(*ad_ptr++) * (*h_ptr++);
	}
	/* final mult/accumulate */
	xa1 += (long)(*ac_ptr) * (*h_ptr++);
	xa2 += (long)(*ad_ptr) * (*h_ptr++);

	/* scale by 2^14 */
	xout1 = xa1 >> 14;
	xout2 = xa2 >> 14;

	/* update delay lines */
	ac_ptr1 = ac_ptr - 1;
	ad_ptr1 = ad_ptr - 1;
	for(i = 0 ; i < 10 ; i++) {
		*ac_ptr-- = *ac_ptr1--;
		*ad_ptr-- = *ad_ptr1--;
	}
	*ac_ptr = xd;
	*ad_ptr = xs;

	return;
}

/* clear all storage locations */

void reset()
{
	int i;

	detl = dec_detl = 32;   /* reset to min scale factor */
	deth = dec_deth = 8;
	nbl = al1 = al2 = plt1 = plt2 = rlt1 = rlt2 = 0;
	nbh = ah1 = ah2 = ph1 = ph2 = rh1 = rh2 = 0;
	dec_nbl = dec_al1 = dec_al2 = dec_plt1 = dec_plt2 = dec_rlt1 = dec_rlt2 = 0;
	dec_nbh = dec_ah1 = dec_ah2 = dec_ph1 = dec_ph2 = dec_rh1 = dec_rh2 = 0;

	for(i = 0 ; i < 6 ; i++) {
		delay_dltx[i] = 0;
		delay_dhx[i] = 0;
		dec_del_dltx[i] = 0;
		dec_del_dhx[i] = 0;
	}

	for(i = 0 ; i < 6 ; i++) {
		delay_bpl[i] = 0;
		delay_bph[i] = 0;
		dec_del_bpl[i] = 0;
		dec_del_bph[i] = 0;
	}

	for(i = 0 ; i < 23 ; i++) tqmf[i] = 0;

	for(i = 0 ; i < 11 ; i++) {
		accumc[i] = 0;
		accumd[i] = 0;
	}
	return;
}



int main(){
  long ct_repeat=0;
  long ct_repeat_max=1;
  int ct_return=0;


	int i,j,f/*,answer*/;
	static int test_data[SIZE*2],compressed[SIZE],result[SIZE*2];

#ifdef XOPENME
  xopenme_init(1,2);
#endif

  if (getenv("CT_REPEAT_MAIN")!=NULL) ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));

	/* reset, initialize required memory */
	reset();

	/* read in amplitude and frequency for test data */
	j = 10; f = 2000;  /* körs men, används inte */

	/* 16 KHz sample rate */
	for(i = 0 ; i < SIZE ; i++) {
		test_data[i] = (int)j*my_cos(f*PI*i);
	}



	/* MAX: 2 */

	/*******Antar att test_data[0] = 10 och test_data[1]=-6 från ovan,          *******
	  och att anropet i forloopen blir encode(test_data[0],test_data[0]);
	  och encode(test_data[1],test_data[1]), eftersom att den annars går
	 *******över array gränsen                                                  *******/

#ifdef XOPENME
  xopenme_clock_start(0);
#endif

  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
	for(i = 0 ; i < IN_END ; i += 2)
		compressed[i/2] = encode(test_data[i],test_data[i+1]);
	/* MAX: 2 */
	for(i = 0 ; i < IN_END ; i += 2) {
		decode(compressed[i/2]);
		result[i] = xout1;
		result[i+1] = xout2;
	}

//	printf("%d\n", result[i]+result[i+1]);
  }

#ifdef XOPENME
  xopenme_clock_end(0);
  xopenme_dump_state();
  xopenme_finish();
#endif


	return 0;
}
