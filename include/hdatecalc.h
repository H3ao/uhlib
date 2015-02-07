#ifndef _DATECALC_H_
#define _DATECALC_H_

#include "time.h"

typedef struct tm st_time;

int dayofweek(int y, int m, int d);

st_time dateplusdays(st_time tm, int days);

int daysof2date(st_time tm_s,st_time tm_e);

#endif