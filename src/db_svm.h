#ifndef _DB_SVM_H_
#define _DB_SVM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#include "db_connection.h"
#include "svm.h"
#include "utils.h"

#define MAX_LABEL_SIZE 20

# ifdef  __cplusplus
extern "C" {
# endif

typedef struct s_scenario
{
	svm_model * model;
	svm_node ** sample;
	char ** label;
	char * model_label;
	int size;
} scenario;

typedef struct s_diagnostic
{
	char * addr;
	char * date;
	char * model_label;
}diagnostic;

# ifdef  __cplusplus
}
# endif



extern void init_config(char * file);

extern PGresult * get_result_from_db(char * query);

extern struct svm_problem * get_problem_from_db();

extern struct svm_parameter * get_svm_parameter_from_db();

extern void print_svm_parameter(struct svm_parameter *param);

extern void print_config_file_name();

extern void print_svm_problem(struct svm_problem * problem);

extern void save_model(struct svm_model * model);

extern struct svm_model * get_model();

extern void free_problem(struct svm_problem * problem);

extern scenario * get_next_scenario();

extern void free_scenario(scenario * obj);

extern void load_scanario_model(char * path,model_access ma, scenario * obj);

extern void load_scanario_data(model_access ma , scenario * obj);

extern void load_scanario_model_label(model_access ma, scenario * obj);

extern int save_diagnostic( diagnostic * diag);

#endif
