#ifndef _TREE_H_
#define _TREE_H_

#include "mydlist.h"
#define MAX(a,b)  (a > b ? a : b)
typedef struct Tree
{
    char   ele;
    int   flag;
    struct Tree *left;
    struct Tree *right;
}*Tree,Tree_node;

Tree create_tree_by_last_mid(char *last_str,char *mid_str,int length);
Tree create_tree_by_pre_mid(char *pre_str,char *mid_str,int length);
Tree create_tree(const char **str);
void init_tree(Tree *root);
void destroy_tree(Tree *root);
void destroy_tree_nr(Tree *root);//非递归删除
Boolean insert_node(Tree root,char value);
//遍历
void pre_order_print(Tree root);//前序
void mid_order_print(Tree root);//中序
void last_order_print(Tree root);//后序

//非递归遍历
void pre_order_print_nr(Tree root);//前序
void mid_order_print_nr(Tree root);//中序
void last_order_print_nr(Tree root);//后序

void level_print(Tree root);//层序遍历
void tree_print(Tree root);//以树型打印

Tree copy_tree(Tree root);//拷贝
Boolean is_tree_equal(Tree root1,Tree root2);
Boolean is_full_tree(Tree root); //判断是否满树
Boolean is_complete_tree(Tree root);//判断完全树
Boolean is_balance_tree(Tree root); //判断平衡树

int Tree_height(Tree root);//树的高度
int Tree_height_nr(Tree root);//非递归求树高度
int Tree_node_count(Tree root);//节点数
int Tree_leaf_count(Tree root);//叶子节点数
void Tree_iso(Tree root);   //树的镜像
int level_count(Tree root,int level);//某层的节点数目
//找到离两个节点最近的节点
Tree_node *find_common_node(Tree root,
                            Tree_node *tree_node1,
                            Tree_node *tree_ndoe2);
Tree_node *find_parent(Tree root,Tree_node *node);
Tree_node *find_node(Tree root,char value);

Boolean is_tree_included(Tree root1,Tree root2);//二叉树是否被包含
int largest_dis(Tree root);

#endif
