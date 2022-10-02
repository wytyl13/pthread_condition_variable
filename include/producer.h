#ifndef pthread_p_h
#define pthread_p_h

#include <pthread.h>
#include "product.h"
#include "erro.h"

//define a struct for producer pthread, involved pid and product
//and the recall function, because of the features of c language
//you can just define the pointer function in struct and bind the function
//to the pointer function out of the struct.
typedef struct Pthread_p
{
    pthread_t pid;
    void *(*pthread_function_p)(void *arg);
    ProductPointer product;
} Pthread_p, *Pthread_p_p;


Pthread_p_p pthread_p;
void *pthread_function_p(void *arg);
//init the producer thread and bind the recall function.
void init_pthread_p();

//notice : this product is dedicated to producer.
//but c language has not the measures to prevent customer to use it
//so only when we will share an object in one process, can we define the
//object in producer head file. in this case, we just use it in here, separately
//defined product by itself in it's head file.
ProductPointer product;

//this function is dedicated to producer. the product id is a random number
void produce();

//this function is dedicated to producer, loading, it is essentially using
//the header method of a linked list.
void loading(ProductPointer product);

#endif