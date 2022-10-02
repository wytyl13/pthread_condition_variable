#include "../include/erro.h"

void error_die(const char *str) 
{
    perror(str);
    exit(1);
}