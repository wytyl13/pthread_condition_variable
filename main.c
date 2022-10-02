/**********************************************************************
 * Copyright (C) 2022. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2022-10-01 14:50:44
 * @Last Modified by: weiyutao
 * @Last Modified time: 2022-10-01 14:50:44
 * @Description: this is a process about thread applycation in linux, what involved thread synchronization,
 * the mutex, the condition variabes and so on, some system programming konwledge.
***********************************************************************/
#include "./include/erro.h"
#include "./include/producer.h"
#include "./include/customer.h"

//if you want to use this two variable as shared variable, you should
//use the extern statemen it in the file.
//so the shared variable has two method to create.
//one is state in head file, and define in C file.
//the other one is not state in head file, you can just use the extern keywork
//in another file to state this shared variable. this define in main file, the
//variable will be shared between producer thread and customer thread.
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t whether_product = PTHREAD_COND_INITIALIZER;
ProductPointer head = NULL;
int main(int argc, char const *argv[])
{
    init_pthread_p();
    init_pthread_c();
    printf("I am main process, my pid is %d, my tid is %lu\n", getpid(), (long unsigned int)pthread_self());
    // first, you should create two thread to simulate producer and consumer separately.therefore, this case
    //simply involves three thread. why not use the main thread? 
    //but before we create the thread, we should set some things to share for two thread first.

    //pthread_t, it is a type about number what is unsigned long int, it means a thread id.
    pthread_t tid_p, tid_c;

    //because of we will use some random number, and we want to unified it between two thread.
    //so we should set the share things rand seed before create them.
    srand(time(NULL));

    //tid_p is a outgoing param, the third param is thread recall function what is a function will
    //be run after one thread created.

    //here, we will create two thread separately represent the produceer and customer.
    if (pthread_create(&tid_p, NULL, pthread_p->pthread_function_p, (void *)1) != 0)
        error.error_die("pthread_create error\n");
    if (pthread_create(&tid_c, NULL, pthread_c->pthread_function_c, (void *)2) != 0)
        error.error_die("pthread_create error\n");

    

    //recycle the thread
    if (pthread_join(tid_p, NULL))
        error.error_die("pthread_join error\n");

    if (pthread_join(tid_c, NULL))
        error.error_die("pthread_join error\n");
    sleep(2);
    return 0;
}
