#include "config.h"

int main(void)
{
/*
  svm_model_info * model_info;
  model_info = get_svm_model_info("bothunter.conf");
  printf("\nparameters %d | %d | %f | %f \n",model_info->svm_type,
  	model_info->kernel_type,
  	model_info->C,
  	model_info->gamma );
	
  db_info * info ;
  info = get_db_info("bothunter.conf");
  printf("%s\n",info->dbname );
  char  conninfo[100];

sprintf(conninfo,"user=%s password=%s dbname=%s",info->user,info->password,info->dbname);
printf("%s\n", conninfo);

   free_db_info(info);
   free_svm_model_info(model_info);
*/

   model_access_list * ma_list;
   ma_list = get_model_access_list("bothunter.conf");
   printf("%s\n",ma_list->path);
   printf("%d\n",ma_list->size);
   int i;
   for(i=0;i<ma_list->size;i++){
   	printf("%s\n",ma_list->model_access_info[i].model_filename);
   	printf("%s\n",ma_list->model_access_info[i].query);
   }
   free_model_access_list(ma_list);

   return 0;
}