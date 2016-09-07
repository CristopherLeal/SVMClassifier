#include "config.h"
#include "db_svm.h"


void predict_scenario(scenario * obj){
    int i,j;
    double result;
    struct svm_node **x;
    char **y; 
       
    printf("%s\n", obj->model_label);

    x = obj->sample;
    y = obj->label;

    for(i=0 ; i < obj -> size ;i++){
      result = svm_predict(obj->model, obj->sample[i]);
      if(!is_equal(result,0.0f)){
        printf("%s | %s \n", y[i], obj->model_label);
      }
    }

/*
    for(int i=0; i < obj->size; i++){
            printf("\n%s\n","------------------------------------------------------" );
            printf("[%s]->",y[i] );
            for (int j = 0; x[i][j].index != -1; j++){
                printf("(%d ,%f )",x[i][j].index,x[i][j].value);
            }
    }
    printf("\n\n");   

    if(obj->model != NULL)
      printf("%s\n","carregou model" );
      */
   
}

int main(void)
{

 

  init_config("bothunter.conf");
  scenario * obj; 
  obj = get_next_scenario();

  while(obj != NULL){

    predict_scenario(obj);

    obj = get_next_scenario();
  }

   return 0;
}