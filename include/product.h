/**********************************************************************
 * Copyright (C) 2022. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2022-10-01 21:48:19
 * @Last Modified by: weiyutao
 * @Last Modified time: 2022-10-01 21:48:19
 * @Description: in this head file, we will define the shared resources
 * between producer and customer, in this case, is producer.h and customer.h
***********************************************************************/
#ifndef product_h
#define product_h
#include "erro.h"

//define a product struct
typedef struct Product
{
    struct Product *next;
    int num;
} Product, *ProductPointer;

//head node, it is a shared resource.
//notice, if you want only one object when multiple c file include this head file,
//you can state the object in head file and use the extern keywork, 
//then you will find all c file share this object.notice not define it in head file.
ProductPointer head;

//static init the mutex and condition variable.
//public resources. but not define the shared variable in head file.
extern pthread_mutex_t lock;
extern pthread_cond_t whether_product;



#endif