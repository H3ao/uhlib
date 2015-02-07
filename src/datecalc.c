
#include <stdio.h>
#include "hdatecalc.h"

#define AYEAR	365
#define LEAPMONTH(x) (isLeap(x)?1:0)

static int monthdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int isLeap(int y)
{
	if ( y <= 0 ) return 0;
	return ((y%4 == 0) && (y%100 != 0) || (y%400 == 0));
}

int dayofweek(int y, int m, int d)/* 0 = Sunday*/
{
	static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
	y -= m < 3;
	return (y+y/4-y/100+y/400+t[m-1]+d)%7;
}

st_time days2date(int days)
{
	st_time tm = {0};
	int leapdays = 0;
	int idx = 1;
	int mdays = 0;
	int sumdays = 0;

	// calculate year
	tm.tm_year = days/AYEAR+1;
	for(; idx <= tm.tm_year; idx ++ ) {
		if ( isLeap(idx) ) leapdays++;
	}

	mdays = days - (tm.tm_year-1)*AYEAR;
	if ( mdays <= leapdays ) {
		leapdays -= LEAPMONTH(tm.tm_year);
		mdays = AYEAR+mdays-leapdays;
		tm.tm_year--;
	} else {
		mdays -= leapdays;
	}

	//calculate month
	idx = 1;
	for (;idx <= 12; idx++ ) {
		if ( sumdays < mdays 
			&& mdays <= (sumdays+monthdays[idx+1])) {
				break;
		}
		sumdays +=monthdays[idx];
	}

	tm.tm_mon = idx;

	//calculate day
	tm.tm_mday = mdays - sumdays;

	return tm;
}

int date2days(st_time tm)
{
	int days = 0;
	int index = 1;

	// calculate year to days
	for (;index < tm.tm_year;index++) {
		days += AYEAR+LEAPMONTH(index);
	}
	index = 1;
	// calculate month to days
	for(;index < tm.tm_mon; index++ ) {
		days += monthdays[index];
	}

	//plus leap year days
	if ( tm.tm_mon > 2 ) {
		days += LEAPMONTH(tm.tm_year);
	}

	// plus days
	return (days+tm.tm_mday);
}

st_time dateplusdays(st_time tm, int days)
{
	return days2date((date2days(tm)+days));
}

int daysof2date(st_time tm_s,st_time tm_e)
{
	return (date2days(tm_e)-date2days(tm_s));
}