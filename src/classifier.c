#include "config.h"
#include "db_svm.h"
#include "utils.h"

void predict_scenario(scenario * obj){
    int i,j;
    double result;
    struct svm_node **x;
    char **y; 
    char * date;
    diagnostic * diag;

    diag = (diagnostic*)malloc(sizeof(diagnostic));
    current_date(&date);
       
    diag->model_label = obj->model_label;

    x = obj->sample;
    y = obj->label;


    for(i=0 ; i < obj -> size ;i++){
      result = svm_predict(obj->model, obj->sample[i]);

      if(!is_equal(result,0.0f)){
        diag->addr = y[i];
        diag->date = date;

        if(!save_diagnostic(diag))
          printf("%s\n","erro ao salvar diagnostico" );
      }
    }
    free(date);
    free(diag);
}

int main(int argc, char ** argv)
{

  test_error(argc != 2, "parametros errados");
  char * config_file_name;
  config_file_name = argv[1];
  
  init_config(config_file_name);
 
  scenario * obj; 
  obj = get_next_scenario();



  while(obj != NULL){

    predict_scenario(obj);

    obj = get_next_scenario();
  }

   return 0;
}