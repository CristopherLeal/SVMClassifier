#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <confuse.h>



# ifdef  __cplusplus
extern "C" {
# endif

typedef struct database_info 
{
	char *ip;
	int port;
	char *user;
	char *dbname;
	char *password;	
} db_info;

typedef struct svm_parameter_model_info
{
	int svm_type;
	int kernel_type;
	double C;
	double gamma;
}svm_model_info;


# ifdef  __cplusplus
}
# endif

extern cfg_opt_t * get_opt();

extern db_info * get_db_info(const char * filename);

extern void free_db_info(db_info * info);

extern svm_model_info * get_svm_model_info(const char * filename);

extern void free_svm_model_info(svm_model_info * info);

extern void get_model_filename(const char * filename,char * model_filename);

extern void get_db_query(const char * filename,char * query);


#endif
