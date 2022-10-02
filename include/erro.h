#ifndef erro_h
#define erro_h
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

//define a struct for error echo
typedef struct Error
{
    void (*error_die)(const char *str);
} Error, *Error_p;

//if you only need one error in your peogram, you can init it in head file.
//only statement not define the variable in head file, this variable will
//be share in all file included this head file. 
extern Error error;

#endif