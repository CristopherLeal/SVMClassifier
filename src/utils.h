#ifndef _UTILS_H_
#define _UTILS_H_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int is_equal(double d1, double d2);
extern double timer();
extern void print_time(const char * msg);
extern void test_error(int condition,const char * msg);
extern void concat_path(char * path, char * file , char ** final);
extern void current_date(char ** date);



#endif