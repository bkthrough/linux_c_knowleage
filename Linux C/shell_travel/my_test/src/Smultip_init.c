/*
parameter initialization function
*/

#include "Multip.h"

extern int FLAG;
extern int symbol;
extern int Mul_qlen;

int Mul_push(struct Multi_input *,int );
int Mul_pop(struct Multi_input *);


/********************************************/
/****** Parameter initialize method   *******/
/********************************************/
int Multi_init(struct Multiplier *param,char *outstr,int row,int col)
{
    char   c_in              = '\0'          ;
    int    c_out             = -1            ;
    int    ret               = Mul_OK        ;
    int    para_len          = 0             ;
    struct Multiplier *pNode = NULL          ;
    struct Multiplier *qHead = param         ;
    struct Multi_input para  = {NULL,NULL,0} ;
        

    if(FLAG) {

        //printf("\n********************************\n");
        //printf("\nPlease input Multiplier: ");
        init_pair(4,COLOR_YELLOW,COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(row,col,"%s\n",outstr);
        //attroff(COLOR_PAIR(4));
        mvprintw(row+1,col,"                        ");
        //refresh();

        init_pair(5,COLOR_WHITE,COLOR_BLACK);
        attron(COLOR_PAIR(5)|A_UNDERLINE);
        //attron(A_BLINK|A_UNDERLINE);
        /* Multiplier input */
        //c_in=getchar();
        c_in=getch();//refresh();
        if(('-'  == c_in)||('+' == c_in)){
            if('-' == c_in){
                symbol = 0-symbol;
            }
            c_in = '0';
        }

        /* input number saved in stack */
        while(c_in != '\n'){
            para_len++;
            if((c_in >= '0')&&(c_in <= '9')){
                ret = Mul_push(&para,(c_in - '0'));

                if(Mul_OK != ret){
                    //printf("Stack push error !\n");
                    mvprintw(row+2,col,"Stack push error !\n");
                    break;
                }

            }else{
                //mvprintw(row+2,col,"Input error !");
                ret = Mul_NG;
                break;
            }
    
            //c_in = getchar();
            c_in = getch();
        }

        attroff(A_BLINK|A_UNDERLINE);
        attron(COLOR_PAIR(4));

        /* Input error ,return */
        if((!para_len)||(Mul_OK != ret)){
            ret = Mul_NG;
            init_pair(6,COLOR_RED,COLOR_YELLOW);
            attron(COLOR_PAIR(6));
            mvprintw(row+2,col,"Input error !");
            //attroff(COLOR_PAIR(6));
            return ret;
        }


        /* Input parameter is build by chain */
        do{
            c_out = Mul_pop(&para);
            if(c_out >= 0){
                pNode=(struct Multiplier *)malloc(sizeof(struct Multiplier));
                if(NULL == pNode){
                    printf("ERROR: malloc failure [errno=%d]\n",errno);
                    ret = Mul_NG;
                    break;
                }
                pNode->elem = c_out;
                pNode->next = NULL ;
                qHead->next = pNode;
                qHead       = pNode; 
            }else{
                printf("Number < 0 ,error !\n");
                ret = Mul_NG;
                break;
            }
        
        }while(NULL != para.top);
        
        Mul_qlen += para_len;
        //printf("\n");
        /* Input dealind end */

    } else {

         printf("error,quit now!\n");
         FLAG = 0;
         ret = Mul_NG;
    }
    return ret;
}

#if 0
/********************************************/
/*********** Resource free method ***********/
/********************************************/
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

#endif

/********************************************/
/************* Window's function ************/
/********************************************/
void WindowInit()
{
    initscr();
    box(stdscr,ACS_VLINE,ACS_HLINE);
    //box(stdscr,'|','+');
    //cbreak();
    echo();
    keypad(stdscr,TRUE);
    //attron(A_NORMAL);
    start_color();
    //init_pair(1,COLOR_GREEN,COLOR_BLACK);
    //init_pair(1,COLOR_WHITE,COLOR_BLACK);
    //attron(COLOR_PAIR(1));
}

int OutWindow(WINDOW **win,int lines,int row,int col)
{
    int ret = Mul_OK;
    *win = subwin(stdscr,lines,COLS-COL_OFFSET,Mul_qlen/COLS+row,col);
    if(NULL == *win){
        ret = Mul_NG;
    }else{
        //init_pair(2,COLOR_YELLOW,COLOR_WHITE);
        //init_pair(3,COLOR_RED,COLOR_MAGENTA);
        init_pair(3,COLOR_CYAN,COLOR_BLACK);
        wattron(*win,COLOR_PAIR(3));
        //box(*win,'%','=');
        box(*win,ACS_VLINE,ACS_HLINE);
        scrollok(*win,TRUE);
        wrefresh(*win);
        //wattron(*win,COLOR_PAIR(3));
    }
    return ret;
}

void WaitForEnd()
{
  getch();
  endwin();
}

/************************ file end *************************/
