#include "include/read_file.h"

char * iter;
char * iter_end;


char *read_file(const char *filename,int * size)
{
    int file;
    double *data=0;
    struct stat buff_stat;
    size_t bytes_read;

    if ((file = open(filename, O_RDONLY)) < 0)
    {
        return NULL;
    }
    else if (fstat(file, &buff_stat) < 0)
    {
        return NULL;
    }
    else if ((data = malloc(buff_stat.st_size+sizeof(char *))) == NULL)
    {
        return NULL;
    }
    else if ((bytes_read = read(file, data, buff_stat.st_size)) < 0)
    {
        return NULL;
    }
    else
    {
        (*size)=buff_stat.st_size;
        char * text= (char *)data;
        text[(*size)]='\0';
        return text;
    }
}

void asignar_iter(char * origen,int size){
    iter=&origen[0];
    iter_end=&origen[size];
}

bool seguir_iter(){
    return iter!=iter_end;
}

bool inc_iter(){
    if(seguir_iter()){
        iter++;
        return true;
    }
    return false;
}

char get_char_iter(){
    return (*iter);
}

bool cmp_iter_char(char c){
    return (*iter)==c;
}