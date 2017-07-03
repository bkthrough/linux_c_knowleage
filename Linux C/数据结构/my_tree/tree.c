#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "tree.h"
#include "tools.h"
#include <string.h>
#include "queue.h"
#include "mydlist.h"
#include "stack.h"

//nice work!!!
static int get_index(char *str,char value);
static Tree_node *create_node(void);

//找到元素对应的下标
static int get_index(char *str,char value)
{
    char *result = strchr(str,value);
    return (result == NULL ? 0 : (result - str) / sizeof(char));
}
//创建节点
static Tree_node *create_node(void)
{
    Tree_node *node = (Tree_node *)Malloc(sizeof(Tree_node));

    bzero(node,sizeof(Tree_node));
    return node;
}
//注意使用二级指针，因为如果传*str这个字符串，递归回退的时候参数str指向
//没有变化。只有使用二级指针，使得指向发生变化，才能让它向后移动。
Tree create_tree(const char **str)
{
    //根据字符串创建一个二叉树
    //a#bc##d##
    //       a
    //        \
    //         b
    //        / \
    //       c   d
    //先让根为NULL，如果不是'#'那么在创建节点并且赋值
    Tree root = NULL;

    if(**str != '#' && str != NULL && *str != NULL){
        root = create_node();
        root->ele = **str;

        //指针指向字符串的下一个位置，然后创建左子树
        ++*str;
        root->left = create_tree(str);
        //如果为'#'就转到这里，创建右子树。
        ++*str;
        root->right = create_tree(str);
    }

    return root;
}
void destroy_tree(Tree *root)
{
    if(*root){
        destroy_tree(&(*root)->left);
        destroy_tree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}
//根据中序和后序确定一个树,后序的最后一个是根节点，然后通过中序把树
//划分成左子树和右子树，递归执行。
Tree create_tree_by_last_mid(char *last_str,char *mid_str,int length)
{
    Tree root = NULL;
    int index = 0;

    if(last_str == NULL || mid_str == NULL || length <= 0){
        return NULL;
    }
    root = create_node();
    //找到根节点在中序字符串中的位置。并赋值给新子树的根节点
    index = get_index(mid_str,last_str[length]);
    root->ele = last_str[length];

    //递归对右子树左子树进行相同操作
    root->left  = create_tree_by_last_mid(last_str,mid_str,index);
    root->right = create_tree_by_last_mid(last_str+index,mid_str+index+1,
                                          length-index);
    return root;
}
//根据前序和中序确定一个树
Tree create_tree_by_pre_mid(char *pre_str,char *mid_str,int length)
{
    int index = 0;
    Tree root = NULL;

    if(mid_str == NULL || pre_str == NULL || length <= 0){
        return NULL;
    }
    root = create_node();
    root->ele = pre_str[0];
    index = get_index(mid_str,pre_str[0]);
    root->left = create_tree_by_pre_mid(pre_str+1,mid_str,index);
    root->right = create_tree_by_pre_mid(pre_str+index+1,
                                         mid_str+index+1,length-index);

    return root;
}
//用层序遍历的思想，在销毁之前，先把左右子树保存，然后直接销毁
void destroy_tree_nr(Tree *root)//非递归删除
{
    Queue queue;
    Tree_node *node = NULL;

    if(root == NULL || *root == NULL){
        return ;
    }
    node = *root;
    *root = NULL;
    queue = init_queue();
    //先让根节点入队
    in(queue,node);
    while(!is_queue_empty(queue)){
        //得到队首节点，输出这个节点的元素，弹出这个节点。
        //把节点存在的左右子树入队
        get_queue_front(queue,(void **)&node);
        if(node->left){
            in(queue,node->left);
        }
        if(node->right){
            in(queue,node->right);
        }
        out(queue);
        free(node);
    }
    destroy_queue(&queue);
}
//遍历
void pre_order_print(Tree root)//先序
{
    if(root == NULL){
        return ;
    }
    if(root){
    pre_order_print(root->left);
    printf("%c ",root->ele);
    pre_order_print(root->right);
    }
}
void mid_order_print(Tree root)//中序
{
    if(root){
        mid_order_print(root->left);
        printf("%c ",root->ele);
        mid_order_print(root->right);
    }
    else{
        return ;
    }
}
void last_order_print(Tree root)//后序
{
    if(root){
        last_order_print(root->left);
        last_order_print(root->right);
        printf("%c ",root->ele);
    }
    else
        return ;
}
//非递归遍历,把右子树先存到栈里，然后存左子树。弹出栈顶元素，输出并且输入弹出的节点的右左子树
//可以达到右子树一直在最下面，父节点先输出，然后左子树输出
void pre_order_print_nr(Tree root)//前序
{
    Stack stack;
    Tree_node *node;

    if(root == NULL){
        return ;
    }
    stack = init_stack();
    //根节点入栈
    push_stack(stack,root);
    while(!stack_is_empty(stack)){
        //得到栈顶元素，输出。弹出这个节点
        //压入这个节点存在的右左节点，注意先入右节点
        //因为先入的后出。
        get_top(stack, (void **)&node);
        printf("%c ",node->ele);
        pop_stack(stack);
        if(node->left){
            push_stack(stack,node->right);
        }
        if(node->right){
            push_stack(stack,node->left);
        }
    }
}
void mid_order_print_nr(Tree root)//中序
{
    Tree_node *node;
    Stack stack;

    if(root == NULL){
        return ;
    }
    stack = init_stack();
    node = root;
    //入栈直到左节点为空，出栈并输出，让node等于右子树
    while(!stack_is_empty(stack) || node){
        while(node){
            push_stack(stack,node);
            node = node->left;
        }
        get_top(stack,(void **)&node);
        printf("%c ",node->ele);
        pop_stack(stack);

        node = node->right;
    }
}
void last_order_print_nr(Tree root)//后序
{
    Tree_node *node = NULL;
    Stack stack;
    //检查是否节点被访问过
    Tree_node *previsited = NULL;

    if(root == NULL){
        return ;
    }
    stack = init_stack();
    node = root;
    while(!stack_is_empty(stack) || node){
        //与中序类似，一直压栈直到左节点为空
        while(node){
            push_stack(stack,node);
            node = node->left;
        }

        get_top(stack,(void **)&node);
        //右边节点为空或者被访问过那么就输出这个节点，并且让这个节点置空。
        if(node->right == NULL || node->right == previsited){
            previsited = node;
            pop_stack(stack);
            printf("%c ",node->ele);
            node = NULL;
        }
        else{
            node = node->right;
        }
    }
}
//把根节点先入队列，得到队首元素并且找到它的左右子树，把它们入队
//输出队首元素，并且出队。依次循环直到队列为空
void level_print(Tree root)//层序遍历
{
    Tree_node *node = root;
    Queue queue;

    if(root == NULL){
        return ;
    }
    queue = init_queue();
    in(queue,root);
    while(!is_queue_empty(queue)){
        get_queue_front(queue,(void **)&node);
        printf("%c ",node->ele);
        out(queue);
        if(node->left){
            in(queue,node->left);
        }
        if(node->right){
            in(queue,node->right);
        }
    }

    destroy_queue(&queue);
}

Tree copy_tree(Tree root)//拷贝
{
    Tree root_copy;

    if(root == NULL){
        return NULL;
    }
    root_copy = create_node();
    //方法一：浅拷贝，只拷贝第一个结构体，后面的都指向原来的树
    memcpy(root_copy,root,sizeof(struct Tree));

    //方法二：把数据域互换
    //root_copy->ele = root->ele;
    //root_copy->left = copy_tree(root->left);
    //root_copy->right = copy_tree(root->right);

    return root_copy;
}
Boolean is_tree_equal(Tree root1,Tree root2)
{
    //都为空返回真
    if(root1 == NULL && root2 == NULL){
        return TRUE;
    }
    //判断它的左右子树是否相等，判断当前节点是否相等，并且两者都不为空
    if(root1 != NULL && root2 != NULL
       && root1->ele == root2->ele
       && is_tree_equal(root1->left,root2->left)
       && is_tree_equal(root1->right,root2->right)){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
Boolean is_full_tree(Tree root) //判断是否满树
{
    int level_count = 1;
    int node_count = 0;
    int result = 0;
    int height = 0;
    if(root == NULL){
        return FALSE;
    }

    height = Tree_height(root);
    height++;
    node_count = Tree_node_count(root);
    while(height--){
        result += level_count;
        level_count *= 2;
    }
    if(result == node_count){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
#if 1
//1.层序遍历;
//2.两个状态：（1）有左右孩子。
//            （2）只有左孩子（flag = 1）
//            （3）flag == 1后续节点不是叶子节点，就不是完全二叉树。
Boolean is_complete_tree(Tree root)//判断完全树
{
    Queue queue;
    Tree_node *node;
    int flag = 0;
    int i = 0;

    if(root == NULL){
        return FALSE;
    }
    node = root;
    queue = init_queue();
    in(queue, node);
    while(!is_queue_empty(queue)){
        get_queue_front(queue,(void **)&node);
        out(queue);
        if(node->left){
            in(queue,node->left);
        }
        if(node->right){
            in(queue,root->right);
        }

        //如果只有右子树，直接返回假
        if(node->right && NULL == node->left){
            return FALSE;
        }
        //如果标记为1，左右子树有其中一个则为假
        if((node->left || node->right) && flag == 1){
            return FALSE;
        }
        //如果只有左子树，另标记为1
        if(node->left && NULL == node->right && flag == 0){
            flag = 1;
        }
    }
    return TRUE;
}
#endif
Boolean is_balance_tree(Tree root) //判断平衡树
{
    if(root == NULL){
        return TRUE;
    }
    //左右子树高度差小于等于1,返回真，否则返回假
    if(abs(Tree_height(root->left) - Tree_height(root->right)) <= 1){
        return TRUE;
    }
    else{
        return FALSE;
    }
    //如果左右子树平衡，那么返回真，否则返回假
    return is_balance_tree(root->left) && is_balance_tree(root->right);

    //与上面的结果一样，不过个人感觉上面的写的清晰一些^_^
    //如果左右子树高度差小于等于1，那么就递归的判断左右子树是否平衡
    //if(root->left && root->right){
    //    if(abs(Tree_height(root->left) - Tree_height(root->right)) <= 1){
    //        return is_balance_tree(root->left) &&
    //               is_balance_tree(root->right);
    //    }
    //    else
    //        return FALSE;
    //}
}

int Tree_height(Tree root)//树的高度
{
    if(root == NULL){
        return 0;
    }

    return MAX(Tree_height(root->left),
               Tree_height(root->right))+1;
}
//出队的节点数等于某一层之前的所有节点数，那么高度就加一
int Tree_height_nr(Tree root)//非递归求树的高度
{
    int height = 0;
    int l_c = 1;    //这层之前的所有节点数
    int i_c = 0;    //入队的节点数
    int o_c = 0;    //出队的节点数
    Queue queue;
    Tree_node *node = root;

    if(root == NULL){
        return 0;
    }

    queue = init_queue();
    in(queue,node);
    i_c++;
    while(!is_queue_empty(queue)){
        get_queue_front(queue,(void **)&node);
        out(queue);
        //出队o_c就加一次
        o_c++;

        if(node->left){
            in(queue,node->left);
            //入队i_c加一次
            i_c++;
        }
        if(node->right){
            in(queue,node->right);
            i_c++;
        }

        //当一层的节点都从队列中弹出，那么它的下一层的所有节点正好都入队。
        //这时让l_c等于所有入队的节点和i_c。
        if(o_c == l_c){
            height++;
            l_c = i_c;
        }
    }

    return height;
}
int Tree_node_count(Tree root)//节点数
{
    if(root == NULL){
        return 0;
    }

    return Tree_node_count(root->left) + Tree_node_count(root->right) + 1;
}
int Tree_leaf_count(Tree root)//叶子节点数
{
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right == NULL){
        return 1;
    }

    return Tree_leaf_count(root->left) + Tree_leaf_count(root->right);
}
void Tree_iso(Tree root)   //树的镜像
{
    if(root == NULL){
        return ;
    }
    //因为节点有可能指向的是NULL,所以交换节点首地址，所以就需要用
    //指向节点首地址的指针。
    if(root->left || root->right){
        swap(&(root->left),&(root->right),sizeof(Tree_node *));
    }
    if(root->left){
        Tree_iso(root->left);
    }
    if(root->right){
        Tree_iso(root->right);
    }
}
Tree_node *find_node(Tree root,char value)
{
    Tree_node *node = NULL;
    if(root == NULL || root->ele == value){
        return root;
    }

    //一直向左找，如果没找到，那么就到它的右边找
    node = find_node(root->left,value);
    if(node == NULL){
        node = find_node(root->right,value);
    }

    return node;
}
int level_count(Tree root,int level)//某层的节点数目
{
    if(root == NULL){
        return 0;
    }
    if(level == 1){
        return 1;
    }

    return level_count(root->right,level) +
           level_count(root->left,level);
}
//找node的父节点
Tree_node *find_parent(Tree root,Tree_node *node)
{
    Tree_node *node1 = NULL;

    if(root == NULL || node == root){
        return NULL;
    }

    if(root->left == node || root->right == node){
        return root;
    }
    node1 = find_parent(root->left,node);
    if(node1 == NULL){
        node1 = find_parent(root->right,node);
    }

    return node1;
}
//找到离两个节点最近的节点，如果在同一个路径下
//返回上面节点的父节点。
Tree_node *find_common_node(Tree root,Tree_node *node1,Tree_node *node2)
{
    Tree_node *node1_ancestor;
    Tree_node *node = NULL;

    //如果root为空或节点就是root，那么返回空
    if(node1 == root || node2 == root || root == NULL){
        return NULL;
    }
    //找节点1的父节点
    node1_ancestor = find_parent(root,node1);
    //如果节点1的父节点的下面路径中并不包含节点2.就继续找父节点的父节点。
    //直到包含为止，返回这个节点就是公共节点
    while(node == NULL){
        node = find_node(node1_ancestor,node2->ele);
        if(node == NULL){
            node1_ancestor = find_parent(root,node1_ancestor);
        }
    }
    if(node1_ancestor == node2){
        node1_ancestor = find_parent(root,node2);
    }

    return node1_ancestor;
}
//判断root1是否包含root2
Boolean is_tree_included(Tree root1,Tree root2)
{
    //因为一个为空另一个不为空，那么它们的节点肯定不好判断
    //所以root2只要先于root1截至就先让它返回真
    //之后在通过root2中的每个节点是否与之对应来判断是否包含
    if(root2 == NULL){
        return TRUE;
    }
    if(root1 == NULL && root2 != NULL){
        return FALSE;
    }
    if(root1->ele == root2->ele){
        return TRUE;
    }

    return is_tree_included(root1->left,root2->left) &&
           is_tree_included(root1->right,root2->right);
}
int largest_dis(Tree root)
{
    int distance = 0;
    int way = 0;
    int tmp = 0;

    if(root == NULL){
        return 0;
    }

    way = Tree_height(root->left) + Tree_height(root->right) + 2;
    tmp = MAX(way, largest_dis(root->left));
    distance = MAX(tmp, largest_dis(root->right));

    return distance;
}
void tree_print(Tree root)
{
    int l_c = 1;    //这层之前的所有节点数
    int i_c = 0;    //入队的节点数
    int o_c = 0;    //出队的节点数
    Queue queue;
    Tree_node *node = root;

    if(root == NULL){
        return ;
    }

    queue = init_queue();
    in(queue,node);
    i_c++;
    while(!is_queue_empty(queue)){
        get_queue_front(queue,(void **)&node);
        out(queue);
        printf("%c ",node->ele);
        o_c++;

        if(node->left){
            in(queue,node->left);
            i_c++;
        }
        if(node->right){
            in(queue,node->right);
            i_c++;
        }

        //当一层的节点都从队列中弹出，那么它的下一层的所有节点正好都入队。
        //这时让l_c等于所有入队的节点和i_c。
        if(o_c == l_c){
            l_c = i_c;
            printf("\n");
        }
    }
}
