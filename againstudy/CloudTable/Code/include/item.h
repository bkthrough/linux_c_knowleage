#ifndef ITEM_H_
#define ITEM_H_

#include "global.h"
#include "list.h"
#include "utils.h"
#include "buf.h"

typedef struct _Key Key;
typedef struct _Item Item;
typedef struct _ResultSet
{
    byte magic[8];
    int size;
    Item **items;
}ResultSet;

Key* get_key(Item *item);
Key* m_clone_key(Key* key);
Key* m_load_key(FILE *fp);
Item* m_create_item(char *row_key, char*column_name, char* value);
Item* m_load_item(FILE *fp);
Item* m_clone_item(Item* item);
char* get_column_name(Item *item);
long long get_timestamp(Item *item);
char* get_value(Item *item);
char* get_row_key(Key *key);
boolean match_by_timestamps(long long src_begin_timestamp, long long src_end_timestamp,
                            long long dest_begin_timestamp, long long dest_end_timestamp);
boolean between_timestamps(long long timestamp, long long begin_timestamp, long long end_timestamp);
void flush_key(Key* key, FILE *fp);
void flush_item(Item *item, FILE *fp);
Buf* result_set_to_byte(ResultSet* resultSet);
ResultSet* byte_to_result_set(byte* buf);
void free_key(Key *key);
void free_item(Item *item);
void free_item_array(int item_size, Item** items);
void free_result_set(ResultSet *resultSet);
void destory_result_set(ResultSet *resultSet);
Key* get_last_key(ResultSet* resultSet);
Key* get_first_key(ResultSet* resultSet);
boolean validate_item(Item* item);
int cmp_item_void(const void* item1_void, const void* item2_void);
int cmp_item(Item* item1, Item* item2);
int cmp_key_with_row_key(const Key *key, const char* row_key);
int cmp_item_with_row_key(const Item *item, const char* row_key);
boolean between_keys(Key *firstKey, Key *lastKey, char *row_key);
ResultSet* found_items_by_row_key(int size, Item** items, char* row_key);
ResultSet* found_items_by_timestamp(int size, Item** items, long long begin_timestamp, long long end_timestamp);
ResultSet *m_item_list_to_result_set(List* itemList);
ResultSet* m_create_result_set(int item_size, Item **items);
void print_result_set_in_nice_format(ResultSet* resultSet);
ResultSet* m_combine_result_set(ResultSet* set0, ResultSet* set1);
ResultSet* cleansing(ResultSet* set);

#endif /* ITEM_H_ */
