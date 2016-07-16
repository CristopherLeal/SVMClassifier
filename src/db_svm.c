#ifndef _DB_SVM_C_
#define _DB_SVM_C_


#include "db_svm.h"

static char * G_config_file;

void init_config(char * file){
    int len = strlen(file);
    G_config_file = (char *)malloc(len*sizeof(char));
    strcpy(G_config_file,file); 
}

void print_config_file_name(){
    printf("FILE:%s\n",G_config_file);
}

void print_svm_problem(struct svm_problem * problem){

    struct svm_node **x;
    double *y; 
    x = problem->x;
    y= problem->y;    

    for(int i=0; i < problem->l; i++){
            printf("\n%s\n","------------------------------------------------------" );
            printf("[%f]->",y[i] );
            for (int j = 0; x[i][j].index != -1; j++){
                printf("(%d ,%f )",x[i][j].index,x[i][j].value);
            }
    }
    printf("\n\n");        
}


void free_problem(struct svm_problem * problem){

    struct svm_node **x;
    double *y;

    x=problem->x;
    y=problem->y;

    for (int i = 0; i < problem->l; ++i)
        free(x[i]);

    free(x);
    free(y);
    free(problem);
}

PGresult * get_result_from_db(char * query){

    PGconn *conn = get_connection(G_config_file);

    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        do_exit(conn);
    }

    PGresult *res = PQexec(conn, query);    
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        printf("No data retrieved\n");        
        PQclear(res);
        do_exit(conn);
    }    
    
    PQfinish(conn);

    return res;
}


struct svm_problem * get_problem_from_db(){

    PGresult *res;
    struct svm_node **x;
    double *y;
    struct svm_node end_node; 
    end_node.index=-1;
    struct svm_problem * problem;
    char query[100];

    get_db_query(G_config_file,query);
    res = get_result_from_db(query);

    int rows =  PQntuples(res);
    int ncols = PQnfields(res);
    
    x = (struct svm_node **)malloc(rows*sizeof(struct svm_node *));
    y = (double*)malloc(rows*sizeof(double));

    for(int i=0; i<rows; i++) {

        x[i] = (struct svm_node *)malloc(ncols*sizeof(struct svm_node));

        for (int j = 0; j < ncols; j++){
            
            if(j==0){
                y[i] = atof(PQgetvalue(res, i, j));
            }
            else {
                x[i][j-1].value = atof(PQgetvalue(res, i, j)); 
                x[i][j-1].index=j;
            }
        }  
    }    
        
    for(int i=0; i<rows; i++){
        x[i][ncols-1] = end_node;
    }

    problem = (struct svm_problem *)malloc(sizeof(struct svm_problem));
    problem->l= rows;
    problem->x = x;
    problem->y = y;

    PQclear(res);

    return problem;
}


struct svm_parameter * get_svm_parameter_from_db(){

    struct svm_parameter * param;
    param = (struct svm_parameter *)malloc(sizeof(struct svm_parameter));

    param->svm_type = C_SVC;
    param->kernel_type = RBF;
    param->degree = 3;
    param->gamma = 0;    // 1/num_features
    param->coef0 = 0;
    param->nu = 0.5;
    param->cache_size = 100;
    param->C = 1;
    param->eps = 1e-3;
    param->p = 0.1;
    param->shrinking = 1;
    param->probability = 0;
    param->nr_weight = 0;
    param->weight_label = NULL;
    param->weight = NULL;
    

    svm_model_info * info = get_svm_model_info(G_config_file);
    if(info->svm_type == 1)
        param->svm_type=ONE_CLASS;
    if(info->kernel_type == 0)
        param->kernel_type = LINEAR;

    param->gamma = info->gamma;
    param->C= info->C;

    free_svm_model_info(info);
    return param;
}


void save_model(struct svm_model * model){
    char model_filename[100];
    get_model_filename(G_config_file, model_filename);
    if(svm_save_model(model_filename,model))
    {
        fprintf(stderr, "can't save model to file %s\n",model_filename);
        exit(1);
    }
}


void print_svm_parameter(struct svm_parameter *param){
                            
                    printf("svm_paramter:\n\n"
                            "svm_type = %d\n"
                            "kernel_type = %d\n"
                            "degree = %d\n"
                            "gamma = %f\n"    
                            "coef0 = %f\n"
                            "nu = %f\n"
                            "cache_size = %f\n"
                            "C = %f\n"
                            "eps = %f\n"
                            "p = %f\n"
                            "shrinking = %d\n"
                            "probability = %d\n"
                            "nr_weight = %f\n\n",
                            param->svm_type,
                            param->kernel_type,
                            param->degree,
                            param->gamma,    // 1/num_features
                            param->coef0,
                            param->nu,
                            param->cache_size,
                            param->C,
                            param->eps,
                            param->p ,
                            param->shrinking ,
                            param->probability ,
                            param->nr_weight);
}



#endif





