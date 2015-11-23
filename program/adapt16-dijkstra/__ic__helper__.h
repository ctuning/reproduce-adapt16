#ifndef _IC_HELPER_H_
#define _IC_HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_NODES                          60
#define NONE                               9999

struct _NODE
{
   int iDist;
   int iPrev;
};
typedef struct _NODE NODE;

struct _QITEM
{
   int iNode;
   int iDist;
   int iPrev;
   struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;

extern QITEM *qHead;

extern int g_qCount;
int i, iCost, iDist;
unsigned long long current_time_in_nanos();

#endif
