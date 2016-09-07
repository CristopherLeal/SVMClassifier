#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <confuse.h>

#define MAX_MODEL_LST_SIZE 10

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

typedef struct model_test_access
{
	char * model_filename;
	char * query;
	char * model_label;
} model_access;

typedef struct model_test_access_list
{
	int size;
	char * path;
	model_access model_access_info[MAX_MODEL_LST_SIZE];

} model_access_list;


# ifdef  __cplusplus
}
# endif


extern cfg_opt_t * get_opt();

extern db_info * get_db_info(const char * filename);

extern void free_db_info(db_info * info);

extern svm_model_info * get_svm_model_info(const char * filename);

extern void free_svm_model_info(svm_model_info * info);

extern model_access_list * get_model_access_list(const char * filename);

extern void free_model_access_list(model_access_list * ma_list);

extern void get_model_filename(const char * filename,char * model_filename);

extern void get_db_query(const char * filename,char * query);




#endif
