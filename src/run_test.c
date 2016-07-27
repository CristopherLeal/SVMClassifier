#include "db_svm.h"
#include "config.h"
#include <time.h>
#include "utils.h"

int main(int argc, char**argv) {

	/*if(argc != 2){
		printf("%s\n","parametro errado");
		exit(1);	
	}*/

	test_error(argc != 2, "parametros errados");
	
	timer();

	char * config_file_name;
	config_file_name = argv[1];
	
	init_config(config_file_name);
	
    struct svm_problem * problem;

    timer();

    problem = get_problem_from_db();

    print_time("Carregar os dados");
    //print_svm_problem(problem);

    

    struct svm_model * model;
	
	model = get_model();

	print_time("Carregar modelo");
/*
	FILE * out_file;
	out_file= fopen("outfile.txt","w");
*/

	int max,i;
	double real;
	double predicted;
	int positivos=0, negativos=0, falso_positivos=0, falsos_negativos=0;

	max = problem->l;
	//fprintf(out_file,"%s\n", "test:\n");
	for(i=0;i<max;i++){
		real=problem->y[i];
		predicted=svm_predict(model,problem->x[i]);

		if(is_equal(predicted,real)){
			if(is_equal(real,1.0))
				positivos++;
			else
				negativos++;
		}
		else{
			if(is_equal(real,1.0))
				falsos_negativos++;
			else
				falso_positivos++;
		}

		//fprintf(out_file,"(%f)->(%f)\n",real, predicted);
	}
	
	svm_free_and_destroy_model(&model);

    free_problem(problem);

    print_time("Executar os testes");
    printf("terminou\n\n");
    printf("positivos:%d\n",positivos );
    printf("negativos:%d\n",negativos);
    printf("falso_positivos:%d\n",falso_positivos);
    printf("falsos_negativos:%d\n",falsos_negativos );
    printf("precisao:%f\n",(float)positivos/(float)(positivos+falso_positivos));
    
    return 0;
}