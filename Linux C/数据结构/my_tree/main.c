#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>

int main(int argc,char *argv[])
{
    //Tree root = NULL;
    //Tree root1 = NULL;
    //Tree root2 = NULL;
    //Tree_node *node1 = NULL;
    //Tree_node *node2 = NULL;
    //Tree_node *node = NULL;
    //const char *str = "abc##dek###f##gh#i###";
    //const char *str2 = "bc###";
    //char *pre_str = "abcdefg";
    //char *mid_str = "cbdafeg";
    //char *last_str = "cdbfgea";
    //int l_count = 0;
    //int height = 0;
    //int distance = 0;
    Tree root = NULL;
    char *pre_str = "abc";
    char *mid_str = "bac";

    root = create_tree_by_pre_mid(pre_str,mid_str,strlen(pre_str));
    //root1 = create_tree_by_last_mid(last_str,mid_str,strlen(pre_str));
    //root = create_tree(&str);
    //root2 = create_tree(&str2);

    //printf("前序遍历root1：\n");
    //pre_order_print(root1);
    //printf("\n");

    //printf("前序遍历root1：\n");
    //pre_order_print(root1);
    //printf("\n");

    //printf("前序遍历：\n");
    //pre_order_print(root);
    //printf("\n");

    //printf("非递归后序遍历\n");
    //last_order_print_nr(root);
    //printf("\n");

    //printf("树形打印\n");
    //tree_print(root);
    //printf("\n");

    //height = Tree_height_nr(root);
    //printf("非递归方法计算树的高度为：%d\n",height);

    //l_count = level_count(root,5);
    //printf("%d\n",l_count);

    //node1 = find_node(root, 'd');
    //node2 = find_node(root, 'c');
    //node = find_common_node(root,node1,node2);
    //printf("公共节点：\n");
    //if(node){
    //    printf("%c ",node->ele);
    //}
    //else{
    //    printf("no have common ancestor");
    //}
    //printf("\n");

    //if(is_complete_tree(root)){
    //    printf("是完全二叉树\n");
    //}
    //else{
    //    printf("不是\n");
    //}

    //if(is_tree_included(root1,root2)){
    //    printf("include!");
    //}
    //else{
    //    printf("no include");
    //}
    //printf("\n");

    //distance = largest_dis(root1);
    //printf("the largest distance is %d\n",distance);

    //destroy_tree(&root);
    return 0;
}
