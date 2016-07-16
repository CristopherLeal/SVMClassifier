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
                         CFG_STR("model_filename", "", CFGF_NONE),
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

   free(cfg);

   return info;
}

void free_svm_model_info(svm_model_info * info){
  free(info);
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
   
