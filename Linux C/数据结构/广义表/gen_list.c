#include "gen_list.h"
#include "tools.h"
#include <strings.h>
#include <ctype.h>
static void get_item(char *sub_str, char *item_str)
{
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);
 
    while(i < sub_len){
        if(sub_str[i] == '('){
            flag++;    
        }
        if(sub_str[i] == ')'){
            flag--;
        }
        //当前没有在子表里，逗号可以进行元素分割
        if(flag == 0 && sub_str[i] == ','){
            break ;
        }
        i++;     
    }   

    //获取广义表元素
    if(i == sub_len){    //只有一个元素
        strcpy(item_str, sub_str);
        sub_str[0] = '\0';
    }else{    //把当前的元素复制给item_str,并且在原列表删除复制的元素
        strncpy(item_str, sub_str, i);
        item_str[i] = '\0';
        strcpy(sub_str, sub_str + i + 1);
    }
}

static Gen_list create_genlist(char *str);
static Boolean string_is_empty(const char *str);
static Gen_node *create_head_node(int head_flag);
static Gen_node *create_int_node(int int_value);
static Gen_node *create_char_node(char char_value);
static char *blank_delete(char *string);
static void delete_braket(const char *src_str,char *des_str,int src_len);
static void get_item1(char *sub_str,char *item);
static Gen_node *create_node(void);
static void get_item(char *sub_str, char *item_str)
{
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);
 
    while(i < sub_len){
        if(sub_str[i] == '('){
            flag++;    
        }
        if(sub_str[i] == ')'){
            flag--;
        }
        //当前没有在子表里，逗号可以进行元素分割
        if(flag == 0 && sub_str[i] == ','){
            break ;
        }
        i++;     
    }   

    //获取广义表元素
    if(i == sub_len){    //只有一个元素
        strcpy(item_str, sub_str);
        sub_str[0] = '\0';
    }else{    //把当前的元素复制给item_str,并且在原列表删除复制的元素
        strncpy(item_str, sub_str, i);
        item_str[i] = '\0';
        strcpy(sub_str, sub_str + i + 1);
    }
}

static void get_item1(char *sub_str,char *item)
{
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);
    while(i < sub_len){
        if(sub_str[i] == '('){
            flag++;
        }
        else if(sub_str[i] == ')'){
            flag--;
        }
        if(flag == 0 && sub_str[i] == ',')
            break;
        i++;
    }
    if(i == sub_len){
        strcpy(item,sub_str);
        sub_str[0] = '\0';
    }
    else{
        strncpy(item,sub_str,i);
        item[i] = '\0';
        strcpy(sub_str,sub_str+i+1);
    }
}
static void delete_braket(const char *src_str,char *des_str,int src_len)
{
    strncpy(des_str,src_str+1,src_len-2);
}
static char *blank_delete(char *string)
{
    int i = 0;
    int j = 0;
    int length = strlen(string);

    if(string == NULL){
        return NULL;
    }
    while(i < length){
        if(isblank(string[i])){
            i++;
            continue;
        }
        string[j++] = string[i++];
    }
    return string;
}


static Gen_node *create_int_node(int int_value)
{
    Gen_node *node = create_node();
    node->n_type = INT_FLAG;
    node->value.int_value = int_value;
    return node;
}
static Gen_node *create_char_node(char char_value)
{
    Gen_node *node = create_node();
    node->n_type = CHAR_FLAG;
    node->value.char_value = char_value;
    return node;
}
static Gen_node *create_head_node(int head_flag){
    }

    flag++;    //说明第一个是左括号成立
    while(string[i] != '\0'){
        if(string[i] == '('){
            flag++;
        }else if(string[i] == ')'){
            flag--;
        }
        if(flag == MATCH && string[i+1] != '\0'){
            return NOT_MATCH;
        }
        i++;
    }
    return flag == MATCH ? MATCH : NOT_MATCH;
   
}

static Boolean is_braket_match1(const char *string)
{
    int flag = MATCH;
    int length = strlen(string);
    int i = 1;
     
    if(string[0] != '(' || string[length - 1] != ')'){
        return NOT_MATCH;
    }

    while(i < length - 1){
        if(string[i] == '('){
            flag++;
        }else if(string[i] == ')'){
            flag--;
        }
        if(flag < MATCH){
            return NOT_MATCH;
        }
        i++;
    }
    return flag == MATCH ? MATCH : NOT_MATCH;
}

Gen_list init_genlist1(char *input_str)          //广义表的创建   
{
    //判断输入字符串是否符合条件
    if(input_str == NULL || is_input_empty(input_str) == TRUE 
    || is_braket_match(input_str) == NOT_MATCH){
        return NULL;
    }
   
    delete_blank(input_str);
    //使用字符串构建广义表，遇到子表结构递归调用
    return create_genlist(input_str);  
}


void     destroy_genlist1(Gen_list *gen_list)    //广义表的销毁
{
    Gen_node *p_node = NULL;

    if(gen_list == NULL || *gen_list == NULL){ 
        return ;
    }
 
    p_node = *gen_list;
    while(p_node != NULL){
        *gen_list = p_node->next;
        if(p_node->n_type == LIST){
            //如果是子表，则递归调用销毁函数
            destroy_genlist(&(p_node->value.head));
        }
        free(p_node);
        p_node = *gen_list;
    }  
}

int      get_genlist_count(Gen_list gen_list)    //得到广义表的元素个数
{
    return 1;
}

int      get_genlist_depth(Gen_list gen_list)    //得到广义表的深度
{
    return 1;

}

Gen_list copy_genlist(Gen_list gen_list)         //广义表的拷贝
{

    return NULL;
}

static void show_genlist_value1(Gen_list gen_list)            //显示广义表信息
{
    Gen_node *p_node = NULL;

    if(gen_list == NULL){
        return ;
    }
    printf("(");
    p_node = gen_list->next;
    while(p_node != NULL){
        if(p_node->n_type == INT){ 
            printf("%d", p_node->value.int_value);
        }else if(p_node->n_type == CHARACTER){ 
            printf("'%c'", p_node->value.char_value);
        }else{
            show_genlist_value(p_node->value.head);
        }
        if(p_node->next != NULL){ 
            printf(", ");
        }
        p_node = p_node->next;
    }
    printf(")");
}


void show_genlist1(Gen_list gen_list)            //显示广义表信息
{
    show_genlist_value(gen_list);
    printf("\n");
}
static void get_item(char *sub_str, char *item_str)
{
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);
 
    while(i < sub_len){
        if(sub_str[i] == '('){
            flag++;    
        }
        if(sub_str[i] == ')'){
            flag--;
        }
        //当前没有在子表里，逗号可以进行元素分割
        if(flag == 0 && sub_str[i] == ','){
        *gen_list = node->next;
        if(node->n_type == LIST_FLAG){
            destroy_genlist(&(node->value.head));
        }
        free(node);
        node = *gen_list;
    }
    *gen_list = NULL;
}
