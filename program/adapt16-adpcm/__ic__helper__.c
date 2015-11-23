#include "__ic__helper__.h"

int qq4_code4_table[16] = {
	0,  -20456,  -12896,   -8968,   -6288,   -4240,   -2584,   -1200,
	20456,   12896,    8968,    6288,    4240,    2584,    1200,       0
};

int qq5_code5_table[32] = {
	-280,    -280,  -23352,  -17560,  -14120,  -11664,   -9752,   -8184,
	-6864,   -5712,   -4696,   -3784,   -2960,   -2208,   -1520,    -880,
	23352,   17560,   14120,   11664,    9752,    8184,    6864,    5712,
	4696,    3784,    2960,    2208,    1520,     880,     280,    -280
};

int qq6_code6_table[64] = {
	-136,    -136,    -136,    -136,  -24808,  -21904,  -19008,  -16704,
	-14984,  -13512,  -12280,  -11192,  -10232,   -9360,   -8576,   -7856,
	-7192,   -6576,   -6000,   -5456,   -4944,   -4464,   -4008,   -3576,
	-3168,   -2776,   -2400,   -2032,   -1688,   -1360,   -1040,    -728,
	24808,   21904,   19008,   16704,   14984,   13512,   12280,   11192,
	10232,    9360,    8576,    7856,    7192,    6576,    6000,    5456,
	4944,    4464,    4008,    3576,    3168,    2776,    2400,    2032,
	1688,    1360,    1040,     728,     432,     136,    -432,    -136
};
int qq2_code2_table[4] = {
	-7408,   -1616,   7408,  1616
};


int ilb_table[32] = {
	2048,  2093,  2139,  2186,  2233,  2282,  2332,  2383,
	2435,  2489,  2543,  2599,  2656,  2714,  2774,  2834,
	2896,  2960,  3025,  3091,  3158,  3228,  3298,  3371,
	3444,  3520,  3597,  3676,  3756,  3838,  3922,  4008
};

int wl_code_table[16] = {
	-60,  3042,  1198,   538,   334,   172,    58,   -30,
	3042,  1198,   538,   334,   172,    58,   -30,   -60
};

int wl_table[8] = {
	-60,   -30,    58,   172,   334,   538,  1198,  3042
};

int wh_code_table[4] = {
	798,   -214,    798,   -214
};
/* G722 C code */
/* QMF filter coefficients:
   scaled by a factor of 4 compared to G722 CCITT recommendation */
int h[24] = {
	12,   -44,   -44,   212,    48,  -624,   128,  1448,
	-840, -3220,  3804, 15504, 15504,  3804, -3220,  -840,
	1448,   128,  -624,    48,   212,   -44,   -44,    12
};


/* quantization table 31 long to make quantl look-up easier,
   last entry is for mil=30 case when wd is max */
int quant26bt_pos[31] = {
	61,    60,    59,    58,    57,    56,    55,    54,
	53,    52,    51,    50,    49,    48,    47,    46,
	45,    44,    43,    42,    41,    40,    39,    38,
	37,    36,    35,    34,    33,    32,    32
};

/* quantization table 31 long to make quantl look-up easier,
   last entry is for mil=30 case when wd is max */
int quant26bt_neg[31] = {
	63,    62,    31,    30,    29,    28,    27,    26,
	25,    24,    23,    22,    21,    20,    19,    18,
	17,    16,    15,    14,    13,    12,    11,    10,
	9,     8,     7,     6,     5,     4,     4
};




/* decision levels - pre-multiplied by 8, 0 to indicate end */
int decis_levl[30] = {
	280,   576,   880,  1200,  1520,  1864,  2208,  2584,
	2960,  3376,  3784,  4240,  4696,  5200,  5712,  6288,
	6864,  7520,  8184,  8968,  9752, 10712, 11664, 12896,
	14120, 15840, 17560, 20456, 23352, 32767
};

/* INVQAH: inverse adaptive quantizer for the higher sub-band */
/* returns dh, code table is pre-multiplied by 8 */

/*  int invqah(int ih,int deth) */
/*  { */
/*        long int rdh; */
/*        rdh = ((long)deth*qq2_code2_table[ih]) >> 15L ; */
/*        return((int)(rdh )); */
/*  } */

/* logsch - update log quantizer scale factor in higher sub-band */
/* note that nbh is passed and returned */

int logsch(int ih,int nbh)
{
	int wd;
	wd = ((long)nbh * 127L) >> 7L;       /* leak factor 127/128 */
	nbh = wd + wh_code_table[ih];
	if(nbh < 0) nbh = 0;
	if(nbh > 22528) nbh = 22528;
	return(nbh);
}
/* upzero - inputs: dlt, dlti[0-5], bli[0-5], outputs: updated bli[0-5] */
/* also implements delay of bli and update of dlti from dlt */

void upzero(int dlt,int *dlti,int *bli)
{
	int i,wd2,wd3;
	/*if dlt is zero, then no sum into bli */
	if(dlt == 0) {
		for(i = 0 ; i < 6 ; i++) {
			bli[i] = (int)((255L*bli[i]) >> 8L); /* leak factor of 255/256 */
		}
	}
	else {
		for(i = 0 ; i < 6 ; i++) {
			if((long)dlt*dlti[i] >= 0) wd2 = 128; else wd2 = -128;
			wd3 = (int)((255L*bli[i]) >> 8L);    /* leak factor of 255/256 */
			bli[i] = wd2 + wd3;
		}
	}
	/* implement delay line for dlt */
	dlti[5] = dlti[4];
	dlti[4] = dlti[3];
	dlti[3] = dlti[2];
	dlti[1] = dlti[0];
	dlti[0] = dlt;
	return;
}
/* scalel: compute quantizer scale factor in lower or upper sub-band*/

int scalel(int nbl,int shift_constant)
{
	int wd1,wd2,wd3;
	wd1 = (nbl >> 6) & 31;
	wd2 = nbl >> 11;
	wd3 = ilb_table[wd1] >> (shift_constant + 1 - wd2);
	return(wd3 << 3);
}
/* invqxl is either invqbl or invqal depending on parameters passed */
/* returns dlt, code table is pre-multiplied by 8 */

/*    int invqxl(int il,int detl,int *code_table,int mode) */
/*    { */
/*        long int dlt; */
/*       dlt = (long)detl*code_table[il >> (mode-1)]; */
/*        return((int)(dlt >> 15)); */
/*    } */

/* logscl - update log quantizer scale factor in lower sub-band */
/* note that nbl is passed and returned */

int logscl(int il,int nbl)
{
	long int wd;
	wd = ((long)nbl * 127L) >> 7L;   /* leak factor 127/128 */
	nbl = (int)wd + wl_code_table[il >> 2];
	if(nbl < 0) nbl = 0;
	if(nbl > 18432) nbl = 18432;
	return(nbl);
}
/* quantl - quantize the difference signal in the lower sub-band */
int quantl(int el,int detl)
{
	int ril,mil;
	long int wd,decis;

	/* abs of difference signal */
	wd = my_abs(el);
	/* determine mil based on decision levels and detl gain */
	/* MAX: 30 */
	for(mil = 0 ; mil < 30 ; mil++) {
		decis = (decis_levl[mil]*(long)detl) >> 15L;
		if(wd <= decis) break;
	}
	/* if mil=30 then wd is less than all decision levels */
	if(el >= 0) ril = quant26bt_pos[mil];
	else ril = quant26bt_neg[mil];
	return(ril);
}
/* filtep - compute predictor output signal (pole section) */
/* input rlt1-2 and al1-2, output spl */

int filtep(int rlt1,int al1,int rlt2,int al2)
{
	long int pl,pl2;
	pl = 2*rlt1;
	pl = (long)al1*pl;
	pl2 = 2*rlt2;
	pl += (long)al2*pl2;
	return((int)(pl >> 15));
}
/* filtez - compute predictor output signal (zero section) */
/* input: bpl1-6 and dlt1-6, output: szl */

int filtez(int *bpl,int *dlt)
{
	int i;
	long int zl;
	zl = (long)(*bpl++) * (*dlt++);
	/* MAX: 6 */
	for(i = 1 ; i < 6 ; i++)
		zl += (long)(*bpl++) * (*dlt++);

	return((int)(zl >> 14));   /* x2 here */
}
int my_abs(int n)
{
	int m;

	if (n >= 0) m = n;
	else m = -n;
	return m;
}



/* uppol2 - update second predictor coefficient (pole section) */
/* inputs: al1, al2, plt, plt1, plt2. outputs: apl2 */

int uppol2(int al1,int al2,int plt,int plt1,int plt2)
{
	long int wd2,wd4;
	int apl2;
	wd2 = 4L*(long)al1;
	if((long)plt*plt1 >= 0L) wd2 = -wd2;    /* check same sign */
	wd2 = wd2 >> 7;                  /* gain of 1/128 */
	if((long)plt*plt2 >= 0L) {
		wd4 = wd2 + 128;             /* same sign case */
	}
	else {
		wd4 = wd2 - 128;
	}
	apl2 = wd4 + (127L*(long)al2 >> 7L);  /* leak factor of 127/128 */

	/* apl2 is limited to +-.75 */
	if(apl2 > 12288) apl2 = 12288;
	if(apl2 < -12288) apl2 = -12288;
	return(apl2);
}

/* uppol1 - update first predictor coefficient (pole section) */
/* inputs: al1, apl2, plt, plt1. outputs: apl1 */

int uppol1(int al1,int apl2,int plt,int plt1)
{
	long int wd2;
	int wd3,apl1;
	wd2 = ((long)al1*255L) >> 8L;   /* leak factor of 255/256 */
	if((long)plt*plt1 >= 0L) {
		apl1 = (int)wd2 + 192;      /* same sign case */
	}
	else {
		apl1 = (int)wd2 - 192;
	}
	/* note: wd3= .9375-.75 is always positive */
	wd3 = 15360 - apl2;             /* limit value */
	if(apl1 > wd3) apl1 = wd3;
	if(apl1 < -wd3) apl1 = -wd3;
	return(apl1);
}

unsigned long long current_time_in_nanos(){
  struct timespec res;
  // CLOCK_THREAD_CPUTIME_ID, CLOCK_MONOTONIC
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &res);

  return 1e9 * res.tv_sec + (long) res.tv_nsec;
}
