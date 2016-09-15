#include "config.h"
#include "db_svm.h"
#include "utils.h"
#include <libpq-fe.h>

int main(int argc, char ** argv)
{

  test_error(argc != 2, "parametros errados");
  char * config_file_name;
  config_file_name = argv[1];
  
  init_config(config_file_name);
  PGresult *res = get_result_from_db("select format_netflow()");
  printf("%s\n",PQresStatus(PQresultStatus(res)) );     



 
   return 0;
}