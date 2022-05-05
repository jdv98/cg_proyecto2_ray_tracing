#include "include/read_file.h"
#include <malloc.h>

char * iter;
char * iter_end;

static void error(int num);

char *read_file(const char *filename,int * size)
{
    int file;
    double *data=0;
    struct stat buff_stat;
    size_t bytes_read;

    #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    if ((file = open(filename, O_RDONLY)) < 0)
    {
        error(1);
    }
    else if (fstat(file, &buff_stat) < 0)
    {
        error(2);
    }
    else if ((data = malloc(buff_stat.st_size+sizeof(char *))) == NULL)
    {
        error(3);
    }
    else if ((bytes_read = read(file, data, buff_stat.st_size)) < 0)
    {
        error(4);
    }
    else
    {
        (*size)=buff_stat.st_size;
        char * text= (char *)data;
        text[(*size)]='\0';
        return text;
    }
    #pragma GCC diagnostic pop
}

void asignar_iter(char * origen,int size){
    iter=&origen[0];
    iter_end=&origen[size];
}

bool seguir_iter(){
    if(get_char_iter()==' ')
        error(5);
    return iter!=iter_end;
}

void inc_iter(){
    if(seguir_iter())
        iter++;
}

char get_char_iter(){
    return (*iter);
}

bool cmp_iter_char(char c){
    return (*iter)==c;
}

bool inc_iter_if_cmp(char c){
    if(cmp_iter_char(c)){
        inc_iter();
        return true;
    }
    return false;
}

static void error(int num){
    (void)fprintf(stdout, "READ_FILE #%i\n",num);
    exit(0);
}