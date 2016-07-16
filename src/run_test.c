#include "db_svm.h"
#include "config.h"




int main(int argc, char**argv) {

	if(argc != 2){
		printf("%s\n","parametro errado");
		exit(1);	
	}

	char * config_file_name;
	config_file_name = argv[1];
	printf("config_file_name : %s\n",config_file_name );

	char model_filename[100];
	char query[100];
	get_model_filename(config_file_name,model_filename);
	printf("model_filename:%s\n",model_filename );

	get_db_query(config_file_name,query);
	printf("db_query:%s\n",query);

	
    struct svm_problem * problem;
    problem = get_problem_from_db(query);
    print_svm_problem(problem);


    struct svm_model * model;
	
	model = svm_load_model(model_filename);

	FILE * out_file;
	out_file= fopen("outfile.txt","w");


	int max,i;
	double real;
	double predicted;
	int positivos=0, negativos=0, falso_positivos=0, falsos_negativos=0;

	max = problem->l;
	fprintf(out_file,"%s\n", "test:\n");
	for(i=0;i<max;i++){
		real=problem->y[i];
		predict=svm_predict(model,problem->x[i]);
		fprintf(out_file,"(%f)->(%f)\n",real, predicted);
	}
	
	svm_free_and_destroy_model(&model);

    free_problem(problem);

    printf("%s\n","terminou" );

    return 0;
}