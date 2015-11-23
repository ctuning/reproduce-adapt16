#ifndef _IC_HELPER_H_
#define _IC_HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* COMPLEX STRUCTURE */
typedef struct {
	int real, imag;
} COMPLEX;

extern int qq2_code2_table[];
extern int ilb_table[];

/* variables for transimit quadrature mirror filter here */
int tqmf[24];
int xl,xh;
int il,szl,spl,sl,el;
int         nbl;                  /* delay line */
int         plt,plt1,plt2;
int         al1,al2;
int         rs;
int         dlt;
int         rlt,rlt1,rlt2;
int         ah1,ah2;
int         ph1,ph2;
int         rh1,rh2;
int         sh;         /* this comes from adaptive predictor */
int         delay_bph[6];
int         delay_dhx[6];
int         sph,ph,yh,rh;
int         eh;
int         dh,ih;
int         deth;
int         nbh,szh;

extern int wh_code_table[];
extern int h[];

/* variables for receive quadrature mirror filter here */
int accumc[11],accumd[11];

/* outputs of decode() */
int xout1,xout2;

int xs,xd;

/* variables for encoder (hi and lo) here */


extern int qq4_code4_table[];

extern int qq5_code5_table[];
extern int qq6_code6_table[];

extern int ilb_table[];

int delay_bpl[6];
extern int wl_code_table[];
extern int wl_table[];

int delay_dltx[6];



int         detl;



extern int quant26bt_pos[];
extern int quant26bt_neg[];

/* variables for decoder here */
int         ilr,yl,rl;
int         dec_deth,dec_detl,dec_dlt;

int         dec_del_bpl[6];

int         dec_del_dltx[6];

int     dec_plt,dec_plt1,dec_plt2;
int     dec_szl,dec_spl,dec_sl;
int     dec_rlt1,dec_rlt2,dec_rlt;
int     dec_al1,dec_al2;
int     dl;
int     dec_nbl,dec_yh,dec_dh,dec_nbh;

/* variables used in filtez */
int         dec_del_bph[6];

int         dec_del_dhx[6];

int         dec_szh;
/* variables used in filtep */
int         dec_rh1,dec_rh2;
int         dec_ah1,dec_ah2;
int         dec_ph,dec_sph;

int     dec_sh,dec_rh;

int     dec_ph1,dec_ph2;



int uppol2(int al1,int al2,int plt,int plt1,int plt2);
int uppol1(int al1,int apl2,int plt,int plt1);


int my_abs(int n);
int filtez(int *bpl,int *dlt);
int logscl(int il,int nbl);
int filtep(int rlt1,int al1,int rlt2,int al2);
int quantl(int el,int detl);
int scalel(int nbl,int shift_constant);
void upzero(int dlt,int *dlti,int *bli);
int logsch(int ih,int nbh);
//void setup_codec(int),key_down(),int_enable(),int_disable();
//int flags(int);

unsigned long long current_time_in_nanos();

#endif
