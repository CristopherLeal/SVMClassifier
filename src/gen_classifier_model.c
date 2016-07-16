#include "db_svm.h"
#include "config.h"


int main(int argc, char**argv) {

	if(argc != 2){
		printf("%s\n","parametro errado");
		exit(1);	
	}
	
	char * config_file_name;
	config_file_name = argv[1];
	init_config(config_file_name);
	
	struct svm_parameter * param;
	param = get_svm_parameter_from_db();
	print_svm_parameter(param);


    struct svm_problem * problem;
    problem = get_problem_from_db();
    print_svm_problem(problem);

    struct svm_model * model;
	const char *error_msg;

	error_msg = svm_check_parameter(problem,param);
	if(error_msg)
	{
		printf("ERROR: %s\n",error_msg);
		exit(1);
	}    

	model = svm_train(problem,param);

    save_model(model);
	
	svm_free_and_destroy_model(&model);

    free_problem(problem);

    return 0;
    
}