#include "db_svm.h"
#include "config.h"
#include "utils.h"


int main(int argc, char**argv) {

	test_error(argc != 2,"parametro errado");
	
	char * config_file_name;
	config_file_name = argv[1];
	init_config(config_file_name);
	
	timer();

	struct svm_parameter * param;
	param = get_svm_parameter_from_db();
	print_svm_parameter(param);
	print_time("Carregar parametros");

    struct svm_problem * problem;
    problem = get_problem_from_db();
    //print_svm_problem(problem);

    print_time("Carregar dados");

    struct svm_model * model;
	const char *error_msg;

	error_msg = svm_check_parameter(problem,param);
	test_error(error_msg?1:0,error_msg);
    
	print_time("Testar parametros");

	model = svm_train(problem,param);

	print_time("Treinar modelo");

    save_model(model);
	
	svm_free_and_destroy_model(&model);

    free_problem(problem);

    print_time("Salvar modelo e encerrar");

    return 0;
    
}