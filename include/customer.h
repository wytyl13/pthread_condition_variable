#ifndef pthread_c_h
#define pthread_c_h

#include <pthread.h>
#include "product.h"
#include "erro.h"

//define a struct for customer pthread, involved pid and product
//and the recall function, because of the features of c language
//you can just define the pointer function in struct and bind the function
//to the pointer function out of the struct.
typedef struct Pthread_c
{
    pthread_t pid;
    void *(*pthread_function_c)(void *arg);
    ProductPointer product;
} Pthread_c, *Pthread_c_p;
// if only one struct object in your process, you can just define it in head file.
Pthread_c_p pthread_c;
//the recall function
void *pthread_function_c(void *arg);

//init the customer thread and bind the recall function.
void init_pthread_c();

//this object is dedicated to customer, it mean a temp product
//the customer has used, notice the diffference between it and the 
//product of producer.
ProductPointer product;

//this function is dedicated to customer.
void consumption();

#endif