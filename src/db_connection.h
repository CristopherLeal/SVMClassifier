#ifndef _DB_CONN_H_
#define _DB_CONN_H_


#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "config.h"


extern void get_conninfo(char * conninfo, const char * filename);
extern PGconn * get_connection(char * filename);
extern void do_exit(PGconn *conn);

#endif