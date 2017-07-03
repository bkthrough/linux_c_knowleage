/* Static libriary source for Multip-Pro    */
/* Made by 2014-07-30 09:36AM(CST)          */
/********************************************/
/*********** Resource free method ***********/
/********************************************/

#include <stdlib.h>
#include "Multip.h"

void Mem_Free(struct Multiplier *param)
{
    struct Multiplier *p,*q ;
    p = q = param ;
    while(NULL != p){
        if(q){
            p = q->next;
            free(q);
            q = p;
        }
    }
}

/********************************************/
/************** Stack push method ***********/
/********************************************/
int Mul_push(struct Multi_input *para,int c_in)
{
    struct Multiplier *Mul_in = NULL;
    
    Mul_in = (struct Multiplier *)malloc(sizeof(struct Multiplier));
    if(NULL == Mul_in){
        printf("ERROR: malloc failure [errno=%d]\n",errno);
        return Mul_NG;
    }
    
    Mul_in->elem = c_in;
    if(NULL == para->base){
        Mul_in->next = NULL;
        para->top    = para->base = Mul_in;
    }else{
        Mul_in->next = para->top;
        para->top    = Mul_in;
    }
    return Mul_OK;
}

/********************************************/
/************* Stack pop method *************/
/********************************************/
int Mul_pop(struct Multi_input *para)
{
    int num = Mul_NG;
    struct Multiplier *Mul_ou = NULL;
    if(NULL != para->top){
        num       = (para->top)->elem;
        Mul_ou    = para->top;
        para->top = (para->top)->next;
        free(Mul_ou);
    }
    return num ;
}

/************************ file end *************************/
