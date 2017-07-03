#ifndef _GENLIST_H_
#define _GENLIST_H_

typedef enum{
    INT_FLAG = 0,
    CHAR_FLAG,
    HEAD_FLAG,
    LIST_FLAG
}Node_type;
typedef struct Gen_node{
    Node_type n_type;
    //记录节点
    //记录状态
    union{
        int  int_value;
        char char_value;
        int  head_flag;        //头节点状态
        struct Gen_node *head; //存一个子表的地址
    }value;
    //指向下一个
    struct Gen_node *next;
}*Gen_list,Gen_node;

Gen_list init_genlist(char *input_str);  //创建广义表
void destroy_genlist(Gen_list *gen_list);
int get_genlist_count(Gen_list gen_list);//广义表节点数目
int get_genlist_depth(Gen_list gen_list);//广义表深度
Gen_list copy_genlist(Gen_list gen_list);//拷贝广义表
void show_genlist(Gen_list gen_list);

//解析字符串
//(1, 'a', (4, 7, 'b'), 'c')
//
//空格,单引号,括号逗号要剥离,而且要判断符号匹配情况
//存到另一个数组里


#endif
