
/*
the function for compute multiplication
*/

#include "Multip.h"
extern int FLAG;
extern int symbol;
extern int Mul_qlen;

int OutWindow(WINDOW **,int,int,int);

/********************************************/
/*********   Computing method   *************/
/********************************************/
int Multip(struct Multiplier *param1, struct Multiplier *param2,int row,int col)
{
    if(FLAG) {
    
        int    increase            = 0             ;   /* the carry number   */
        int    bit                 = 0             ;   /* bit compute result */
        int    rstlen              = 0             ;
        int    ret                 = Mul_OK        ;
        int    mP1                 = 0             ;
        int    mP2                 = 0             ;
        struct Multiplier *Mul_p1  = param1        ;
        struct Multiplier *Mul_p2  = param2        ;
        struct Multi_output Mul_ou = {NULL,NULL,0} ;
        struct Reslt *pRst         = NULL          ;
        struct Reslt *plus         = NULL          ;
        struct Reslt *pMv1         = NULL          ;
        struct Reslt *pMv2         = NULL          ;
        WINDOW       *win          = NULL          ;

         /* result saving queue build        */
         for(rstlen=0;rstlen<=Mul_qlen+1;rstlen++){

             pRst = (struct Reslt *)malloc(sizeof(struct Reslt));
             if(NULL == pRst){
                 printf("ERROR:malloc [errno=%d]\n",errno);
                 ret = Mul_NG;
                 return ret;
             }

             if(NULL == Mul_ou.base){
                  Mul_ou.top      = Mul_ou.base = pRst;
                  pRst->next      = NULL;
             }else{
                 pRst->next       = Mul_ou.top;
                 pRst->head       = NULL;
                 Mul_ou.top->head = pRst;
                 Mul_ou.top       = pRst;
             }

             pRst->elem = 0;
         }//end for[rstlen]
         

         /* Computing ... */
         pMv1 = Mul_ou.base;
         pMv2 = Mul_ou.base;
         
         while(NULL != Mul_p2){
             mP2 = Mul_p2->elem;
             //printf("mP2:%d\n",mP2);
             if(mP2){
                 pMv1 = pMv2;
                 while(NULL != Mul_p1){
                     mP1 = Mul_p1->elem;
                     //printf("mP1:%d\n",mP1);
                     if(mP1){
                          bit        =  (mP1 * mP2) + pMv1->elem;
                          increase   = bit/10;
                          pMv1->elem = bit%10;
                          (pMv1->head)->elem += increase;
                     }
                     Mul_p1 = Mul_p1->next;
                     pMv1 = pMv1->head;
                 }//end while[Mul_p1]
             }
             /* Everytimes , the second parameter's start place is on its Beginnings */
             Mul_p1 = param1;

             /* The first parameter's point backwarding */
             Mul_p2 = Mul_p2->next;

             /* result conserving point is Forwarding for High-Bit  */
             pMv2 = pMv2->head;

         }//end while[Mul_p2]

         pRst = Mul_ou.top;
         while(NULL != pRst){
             if(0 == pRst->elem){
                 pRst = pRst->next;
             }else{
                 break;
             }
         }

         //printf("\n===============\n"); 
         //mvprintw(row,col,"===============\n"); 
         //printf("The result is : ");
         //mvprintw(row+1,col,"The result is : ");
         if(Mul_NG == OutWindow(&win,6+(Mul_qlen/COLS),row+2,2)){
             mvprintw(row+1,col,"Display Window initializing Failure ! ");
             return Mul_NG;
         }

         init_pair(7,COLOR_BLACK,COLOR_WHITE);
         wattron(win,COLOR_PAIR(7));

         mvwprintw(win,1,2,"The result is : \n");
         wattroff(win,COLOR_PAIR(7));
         init_pair(8,COLOR_WHITE,COLOR_BLACK);
         wattron(win,COLOR_PAIR(8));
         mvwprintw(win,2,2,"");
         if(symbol<0){
             //printf("-");
             wprintw(win,"-");
         }
         //standout();
         plus = pRst;
         while(NULL != pRst){
              //printf("%d",pRst->elem);
              wprintw(win,"%d",pRst->elem);
              pRst = pRst->next;
         }
         wprintw(win,"\n");
         //compute the result of every bits
         bit = 0;
         while(NULL != plus){
             bit += plus->elem ;
             plus = plus->next ;
         }
         mvwprintw(win,6,2,"plus : %d\n",bit);
         FILE * fd = fopen("rst.txt","w");
         fprintf(fd,"plus : %d\n",bit);
         
         leaveok(win,TRUE);
         wrefresh(win);
         //standend();
         //refresh();
         //printf("\n\n");
         
         pRst = Mul_ou.top;
         while(NULL != pRst){
             free(pRst);
             pRst = pRst->next;
         }
    
    }else{
       /* Error  */
       return Mul_NG ;
    }  /* end else */

}  /* end function */

/************************ file end *************************/
