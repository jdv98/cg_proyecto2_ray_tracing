#ifndef READ_FILE_H
#define READ_FILE_H

#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>


char *read_file(const char *filename,int * size);
void asignar_iter(char * origen,int size);
bool seguir_iter();
void inc_iter();
char get_char_iter();
bool cmp_iter_char(char c);
bool inc_iter_if_cmp(char c);
#endif