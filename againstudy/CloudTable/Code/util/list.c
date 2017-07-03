#include "malloc2.h"
#include "list.h"

typedef struct _ListNode
{
    struct _ListNode *next;
    struct _ListNode *prev;
    void* data;
}ListNode;

struct _List
{
    ListNode* cursor;
    ListNode* first;
};

ListNode* list_next_node(List* thiz)
{
    /*if the list is empty or reach the end*/
    if(thiz->cursor==NULL) return NULL;
    ListNode *node = thiz->cursor;
    thiz->cursor = thiz->cursor->next;
    return node;
}

void free_node(ListNode* node)
{
    if(node->prev != NULL) node->prev = NULL;
    if(node->next != NULL) node->next = NULL;
    free2(node);
}

List* list_create(void)
{
    List *list = malloc2(sizeof(List));
    /*safe action*/
    list->first = NULL;
    list->cursor = NULL;
    return list;
}

ListNode* create_list_node(void* data)
{
    ListNode *next = malloc2(sizeof(ListNode));
    next->data = data;
    next->next = NULL;
    next->prev = NULL;
    return next;
}

/** Not Performance Wise Choice, but no need to rewind the list after finishing using it **/
void list_append(List* thiz, void* data)
{
    list_rewind(thiz);
    list_add(thiz, data);
    list_rewind(thiz);
}

/** Performance Wise Choice, pls rewind the list after finishing using it **/
void list_add(List* thiz, void* data)
{
    ListNode *next = create_list_node(data);
    /*if the list is empty*/
    if(thiz->cursor == NULL)
    {
        next->prev = NULL;
        thiz->first = next;
        list_rewind(thiz);
    }
    else
    {
        while(thiz->cursor->next!=NULL)
        {
            thiz->cursor = thiz->cursor->next;
        }
        next->prev = thiz->cursor;
        thiz->cursor->next = next;
    }
}

/** the method for better coding, and thread safe, but not performance wise for large list iterating **/
void* list_get(List* thiz, int index)
{
    void* result = NULL;
    list_rewind(thiz);
    int i=0;
    void* temp = NULL;
    while((temp = list_next(thiz)) != NULL)
    {
        if(i == index)
        {
            result = temp;
            break;
        }
        else
        {
            i++;
        }
    }
    list_rewind(thiz);
    return result;
}

/** this method won't rewind the list, pls rewind the list after iterating it, and it is performance wise**/
void* list_next(List* thiz)
{
    /*if the list is empty or reach the end*/
    ListNode *node = list_next_node(thiz);
    if(node==NULL)
    {
        return NULL;
    }
    else
    {
        return node->data;
    }
}

void* list_find(List* thiz, void* target, boolean(*match)(void *object, void *target))
{
    list_rewind(thiz);
    void *object = NULL;
    while((object = list_next(thiz)) != NULL)
    {
        if(match(object, target)) 
            break;
    }
    list_rewind(thiz);
    return object;
}
void list_replace(List* thiz, void* old_data, void* new_data)
{
    list_rewind(thiz);
    ListNode *node = list_next_node(thiz);
    if(node!=NULL && node->data == old_data)
        node->data = new_data;
    list_rewind(thiz);
}

List* list_find_all(List* thiz, void* target, boolean(*match)(void *object, void *target))
{
    List* newList = list_create();
    list_rewind(thiz);
    void *object = NULL;
    while((object = list_next(thiz)) != NULL)
    {
        if(match(object, target)) list_append(newList, object);
    }
    list_rewind(thiz);
    return newList;
}

/** will use default strcmp method to sort**/
List* list_sort(List* thiz)
{
    List *newList = list_create();
    /*convert list to array*/
    int size = list_size(thiz);
    char** arrays = (char**)list_to_array(thiz);
    int i=0, j=0, k=0;
    for(i=0; i<size; i++)
    {
        for(j=i+1; j<size; j++)
        {
            if(strcmp(arrays[i], arrays[j])>0)
            {
                swap_pointer(arrays[i], arrays[j]);
            }
        }
    }
    for(k=0; k<size; k++)
    {
        list_append(newList, arrays[k]);
    }
    return newList;
}

boolean list_remove(List* thiz, void* data, void (*free_object)(void *object))
{
    free_object(data);
    list_rewind(thiz);
    ListNode *node = NULL;
    while((node = list_next_node(thiz))!=NULL)
    {
        if(node->data == data)
        {
            /*if the first node catchs*/
            if(node == thiz->first)
            {
                thiz->first = node -> next;
            }
            else
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            free_node(node);
            return true;
        }
    }
    return false;
}

void list_destory(List* thiz, void (*free_object)(void *object))
{
    if(thiz != NULL)
    {
        list_rewind(thiz);
        void *data = NULL;
        while((data = list_next(thiz))!=NULL) 
        {
            list_remove(thiz, data, free_object);
        }
        free2(thiz);
    }
}

void list_rewind(List* thiz)
{
    thiz->cursor = thiz->first;
}

int list_size(List* thiz)
{
    list_rewind(thiz);
    int i=0;
    void *data = NULL;
    while((data = list_next(thiz))!=NULL) 
        i++;
    list_rewind(thiz);
    return i;
}

/** the method is a fake method, for freeing object has not been malloced **/
void only_free_struct(void *p){};

/** this free method for character list **/
void just_free(void *p)
{
    if(p != NULL) free2(p);
}

List* array_to_list(void** array, int size)
{
    List* list = list_create();
    int i=0;
    for(i=0; i<size; i++)
    {
        list_append(list, array[i]);
    }
    return list;
}

void** list_to_array(List* thiz)
{
    int size = list_size(thiz);
    void **array = malloc2(sizeof(void *) * size);
    int i=0;
    list_rewind(thiz);
    for(i=0; i<size; i++)
    {
        array[i] = list_next(thiz);
    }
    list_rewind(thiz);
    return array;
}

