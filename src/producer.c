#include <../include/producer.h>

/**
 * @Author: weiyutao
 * @Date: 2022-10-01 20:54:21
 * @Parameters: 
 * @Return: 
 * @Description: producer thread recall function
 */


void *pthread_function_p(void *arg) 
{
    uint64_t i = (uint64_t)arg;
    printf("I am %luth producer thread, my pid is %d, my tid is %lu\n", i, getpid(), (long unsigned int)pthread_self());


    for (;;)
    {
        //notice: the process will start with the customer thread. so we should
        //keep the producer thread to be sleep first.

        //in producer process, we need not to define the product
        //we can use the product in head file product.h
        //so here we need not define it and can run the funtion produce directly.
        produce();
        //run here, producer has produced one product.
        //then he should put this product on the shelf what is public area.
        //in order to thread synchronization and execution efficiency,
        //just when you access the public areas, you should lock, and unlock when you leave it.

        //4 lock, the static init mutex in head file product.c.
        if (pthread_mutex_lock(&lock) != 0)
            error.error_die("pthread_mutex_lock error\n");
        
        //5 loading
        loading(product);

        //6 leave the public area, in order to efficient, you should unlock now.
        if (pthread_mutex_unlock(&lock) != 0)
            error.error_die("pthread_mutex_unlock error\n");
        
        //7 release the signal, that is wake up the customer thread who block
        //wait at this condition variable if the product number loaded is zero.
        //you can choose to wake up one or all of them.
        if (pthread_cond_signal(&whether_product) != 0)
            error.error_die("pthread_cond_signal error\n");
        
        //release the cpu resources, beacause the producer is in cycle production
        //if you don't release the cpu, the customer thread will not run.
        sleep(rand() % 5);
    }

    return NULL;
}

void init_pthread_p()
{
    pthread_p = (Pthread_p_p)malloc(sizeof(Pthread_p));
    pthread_p->pthread_function_p = pthread_function_p;
}

void produce() 
{
    //init the pointer product
    product = (ProductPointer)malloc(sizeof(product));
    //in this case, random numbers are used as products produces by producers.
    product->num = rand() % 1000 + 1;//(0 - 999) + 1 = 1 - 1000
    printf("-----producer %lu produce %d-----\n", pthread_self(), product->num);
}

void loading(ProductPointer product) 
{
    //the head method.
    product->next = head;
    head = product;
}
