/*
The main function
*/

#include "Multip.h"

int FLAG     = 1;   /* if parameter initialize successful,set FLAG=1 */
int symbol   = 1;   /* Number's plus-minus (global)                  */
int Mul_qlen = 0;   /* queue for result 's length                    */
int rowprint = 3, colprint = 3; /* print position                    */

/* Method */
int Multi_init(struct Multiplier *,char *,int ,int);
int Multip(struct Multiplier *, struct Multiplier *,int ,int);
void WindowInit();
void WaitForEnd();


/********************************************/
/*********   Multip main method   ***********/
/********************************************/
int main(int argc,char **argv)
{

    int ret = Mul_NG;
    /* Initialize the multiplier */
    struct Multiplier multiplier1 = {0,0}; 
    struct Multiplier multiplier2 = {0,0};
    
    WindowInit();

    /* Input the two multipliers */
    ret = Multi_init(&multiplier1,"Please input the first multiplier:",rowprint+++(Mul_qlen/ONELINEMAX),colprint);
    if(Mul_OK != ret){
        mvprintw(rowprint+2,colprint,"Parameter Init Error, Exit!\n");
        Mem_Free(multiplier1);
        WaitForEnd();
        return ret;
    }

    ret = Multi_init(&multiplier2,"            the second multiplier:",rowprint+++(Mul_qlen/ONELINEMAX)+2,colprint);
    if(Mul_OK != ret){
        //printf("Parameter Init Error !\n");
        mvprintw(rowprint+4,colprint,"Parameter Init Error, Exit!\n");
        Mem_Free(multiplier1);
        WaitForEnd();
        return ret;
    }
    
    /* Computing for result  */
    Multip((&multiplier1)->next,(&multiplier2)->next,rowprint+++(Mul_qlen/ONELINEMAX)+2,colprint);

    WaitForEnd();

    /* Resource Free */
    Mem_Free((&multiplier1)->next);
    Mem_Free((&multiplier2)->next);

}

/************************ file end *************************/
