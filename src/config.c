#ifndef _CONFIG_C_
#define _CONFIG_C_

#include "config.h"



cfg_opt_t * get_opt(){
  static cfg_opt_t opts[] = {
                         CFG_STR("user", "root", CFGF_NONE),
                         CFG_STR("password", "", CFGF_NONE),
                         CFG_STR("dbname", "", CFGF_NONE),
                         CFG_STR("ip", "", CFGF_NONE),
                         CFG_INT("port", 0, CFGF_NONE),
                         CFG_STR("db_query", "", CFGF_NONE),
                         CFG_INT("svm_type",0, CFGF_NONE),
                         CFG_INT("kernel_type",0,CFGF_NONE),
                         CFG_FLOAT("gamma",0,CFGF_NONE),
                         CFG_FLOAT("C",1,CFGF_NONE),
                         CFG_STR("model_filename", "file.model", CFGF_NONE),
                         CFG_STR("model_list_path","",CFGF_NONE),
                         CFG_STR_LIST("model_list","{}",CFGF_NONE),
                         CFG_STR_LIST("query_list","{}",CFGF_NONE),
                         CFG_END()
                        };
      return opts;                  
}

db_info * get_db_info(const char * filename){

   cfg_opt_t * opts = get_opt();

   cfg_t *cfg;

   cfg = cfg_init(opts, CFGF_NONE);
   cfg_parse(cfg, filename);

   db_info * info;
   info = (db_info*)malloc(sizeof(db_info));

   char * user = cfg_getstr(cfg, "user");
   char * password = cfg_getstr(cfg,"password");
   char * dbname = cfg_getstr(cfg,"dbname");
   char * ip = cfg_getstr(cfg,"ip");
   
   info->user = (char*)malloc(strlen(user)*sizeof(char));
   info->password = (char*)malloc(strlen(user)*sizeof(char));
   info->dbname = (char*)malloc(strlen(user)*sizeof(char));
   info->ip = (char*)malloc(strlen(user)*sizeof(char));
   
   strcpy(info->user,user);
   strcpy(info->password,password);
   strcpy(info->dbname,dbname);
   strcpy(info->ip,ip);
   info->port = cfg_getint(cfg,"port");

   cfg_free(cfg);

   return info;
}

void free_db_info(db_info * info){
  free(info->user);
  free(info->password);
  free(info->dbname);
  free(info->ip);
  free(info);
}

svm_model_info * get_svm_model_info(const char * filename){
  cfg_opt_t * opts = get_opt();
  cfg_t *cfg;

  cfg = cfg_init(opts, CFGF_NONE);
  cfg_parse(cfg, filename);

  svm_model_info * info;
  info = (svm_model_info*)malloc(sizeof(svm_model_info));

  info->svm_type = cfg_getint(cfg,"svm_type");
  info->kernel_type = cfg_getint(cfg,"kernel_type");
  info->C = cfg_getfloat(cfg,"C");
  info->gamma = cfg_getfloat(cfg,"gamma");

  cfg_free(cfg);

   return info;
}

void free_svm_model_info(svm_model_info * info){
  free(info);
}

model_access_list * get_model_access_list(const char * filename){

  int i;
  cfg_opt_t * opts = get_opt();
  cfg_t *cfg;

  cfg = cfg_init(opts, CFGF_NONE);
  cfg_parse(cfg, filename);
  
  model_access_list * ma_list = (model_access_list*)malloc(sizeof(model_access_list));

  char *path, *model_list_item, *query_list_item;

  path = cfg_getstr(cfg,"model_list_path");

  ma_list->path = (char *)malloc(sizeof(char)*strlen(path));
  strcpy(ma_list->path,path);
  

  for(i=0;i< cfg_size(cfg,"model_list");i++){

    model_list_item = cfg_getnstr(cfg,"model_list",i);
    ma_list->model_access_info[i].model_filename =(char*)malloc(sizeof(char)*strlen(model_list_item));
    strcpy(ma_list->model_access_info[i].model_filename,model_list_item);

    query_list_item=cfg_getnstr(cfg,"query_list",i);
    ma_list->model_access_info[i].query =(char*)malloc(sizeof(char)*strlen(query_list_item));
    strcpy(ma_list->model_access_info[i].query,query_list_item);
  }
  ma_list->size=i;
  
  free(cfg);
  return ma_list;

}

void free_model_access_list(model_access_list * ma_list){
  free(ma_list->path);
  int i;
  for(i=0; i< ma_list->size;i++){
    free(ma_list->model_access_info[i].model_filename);
    free(ma_list->model_access_info[i].query);
  }
  free(ma_list);
}


void get_model_filename(const char * filename, char * model_filename){

  cfg_opt_t * opts = get_opt();
  cfg_t *cfg;

  cfg = cfg_init(opts, CFGF_NONE);
  cfg_parse(cfg, filename);

  strcpy(model_filename ,cfg_getstr(cfg, "model_filename"));

  free(cfg);
}

void get_db_query(const char * filename, char * query){

  cfg_opt_t * opts = get_opt();
  cfg_t *cfg;

  cfg = cfg_init(opts, CFGF_NONE);
  cfg_parse(cfg, filename);

  strcpy(query,cfg_getstr(cfg, "db_query"));

  free(cfg); 
}

#endif
   
