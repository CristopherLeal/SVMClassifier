#ifndef _DB_SVM_H_
#define _DB_SVM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#include "db_connection.h"
#include "svm.h"



extern void init_config(char * file);

extern PGresult * get_result_from_db(char * query);

extern struct svm_problem * get_problem_from_db();

extern struct svm_parameter * get_svm_parameter_from_db();

extern void print_svm_parameter(struct svm_parameter *param);

extern void print_config_file_name();

extern void print_svm_problem(struct svm_problem * problem);

extern void save_model(struct svm_model * model);

extern void free_problem(struct svm_problem * problem);

#endif
