#ifndef _UTILS_C_
#define _UTILS_C_

#include "utils.h"

int is_equal(double d1, double d2){
	double e = 0.0000001f;
	double dif = d1-d2> 0 ? d1-d2 : d2 -d1;
	return dif < e ? 1 : 0;
}

double timer(){
	static time_t last_time = 0;
	time_t current_time = time(NULL);
	double diff = difftime(current_time,last_time);
	last_time = current_time;
	return diff;
}

void print_time(const char * msg){
	printf("RUNTIME(%s): %f seg\n",msg, timer());
}

void test_error(int condition,const char * msg){
	if(condition){
		printf("ERROR:%s\n",msg);
		exit(1);
	}
}

#endif
