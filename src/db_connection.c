#ifndef _DB_CONN_C_
#define _DB_CONN_C_

#include "db_connection.h"


void get_conninfo(char * conninfo,const  char * filename){

    db_info *info;
    info = get_db_info(filename);

    sprintf(conninfo,"user=%s password=%s dbname=%s hostaddr=%s port=%d",
                                                            info->user,
                                                            info->password,
                                                            info->dbname,
                                                            info->ip,
                                                            info->port);
    free_db_info(info);
}

PGconn * get_connection( char * filename){
    
    char conninfo[100];
    get_conninfo(conninfo,filename);
    PGconn *conn = PQconnectdb(conninfo);
    return conn;
} 


void do_exit(PGconn *conn) {
    
    PQfinish(conn);
    exit(1);
}


#endif