#ifndef LIST_H_
#define LIST_H_

#include "global.h"

struct _List;
typedef struct _List List;

List* list_create(void);
void list_append(List* thiz, void* data);
void list_add(List* thiz, void* data);
void* list_get(List* thiz, int index);
void* list_next(List* thiz);
void* list_find(List* thiz, void* target, boolean(*matchs)(void *object, void *target));
List* list_find_all(List* thiz, void* target, boolean(*match)(void *object, void *target));
void list_replace(List* thiz, void* old_data, void* new_data);
boolean list_remove(List* thiz, void* data, void (*free_object)(void *object));
void list_rewind(List* thiz);
List* list_sort(List* thiz);
int list_size(List* thiz);
void list_destory(List* thiz, void (*free_object)(void *object));
void only_free_struct(void *p);
void just_free(void *p);
List* array_to_list(void** array, int size);
void** list_to_array(List* thiz);

#endif /* LIST_H_ */
