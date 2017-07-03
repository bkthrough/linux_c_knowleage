#ifndef MEMSTORE_H_
#define MEMSTORE_H_

#include "global.h"
#include "list.h"
#include "item.h"

typedef struct _Memstore Memstore;
Memstore* init_memstore(int id);
boolean memstore_full(Memstore* memstore);
void append_memstore(Memstore *memstore, Item *item);
ResultSet* get_all_sorted_items_memstore(Memstore *memstore);
ResultSet* get_all_items_memstore(Memstore *memstore);
void sort_memstore(Memstore* memstore);
ResultSet* query_memstore_by_row_key(Memstore* memstore, char* row_key);
ResultSet* query_memstore_by_timestamp(Memstore* memstore, long long begin_timestamp, 
                                       long long end_timestamp);
List* get_left_items(Memstore *memstore, int flushed_size);
void free_memstore(Memstore* memstore);
char* get_memstore_metadata(Memstore* memstore);

#endif /* MEMSTORE_H_ */
