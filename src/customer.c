#include "../include/customer.h"


void *pthread_function_c(void *arg) 
{
    //the customer thread will run first.
    uint64_t i = (uint64_t)arg;
    printf("I am %luth thread, my pid is %d, my tid is %lu\n", i, getpid(), (long unsigned int)pthread_self());

    for (;;)
    {
        //recycle consumption
        //consumption means access to public resources.
        //1 access public resources and lock
        if (pthread_mutex_lock(&lock) != 0)
            error.error_die("pthread_mutex_lock error\n");
        
        //2 use the condition variable second.
        //if it is not meet the condition variable, the thread will block and 
        //wait to be wake up by producer thread.
        if (pthread_cond_wait(&whether_product, &lock) != 0)
            error.error_die("pthread_cond_wait error\n");
        
        //3 pthread_cond_wait function involved unlock, perform other and
        //lock when the condition variable meet. while perform other, the 
        //producer thread will have the opportunity to get the cpu resouces,
        //so during the pthread_cond_wait function, process will give the resouces
        //to producer thread. this is why the third step in customer thread to the 
        //fourth step of the producer thread. when the variable meet, the function 
        //if this thread is wake up by producer thread, pthread_cond_wait will lock
        //and end. process will go ahead and execute. so the next step is 8.
        
        //8 consumption
        consumption();

        //9 unlock
        if (pthread_mutex_unlock(&lock) != 0)
            error.error_die("pthread_mutex_unlock error\n");
        
        printf("-----consumer %lu consumption %d-----\n", pthread_self(), product->num);

        //10 last, we need to free the memory in heap what malloced in heap by producer.
        //why can, because the product pointer point to it, we have make it in function consumption.
        free(product);
        
        //when process run here, customer thread should release the cpu resources,
        //in order to the producer thread can access the resouces to produce product.
        sleep(rand() % 5);
    }
    return NULL;
}

void init_pthread_c()
{
    pthread_c = (Pthread_c_p)malloc(sizeof(Pthread_c));
    pthread_c->pthread_function_c = pthread_function_c;
}

void consumption() 
{
    product = head;
    head = product->next;
}
