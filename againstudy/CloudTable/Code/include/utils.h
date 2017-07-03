#ifndef UTILS_H
#define UTILS_H

#include "global.h"
#include "list.h"

/**   string normal operation part  **/
char* move_pointer(char* pointer, int div);
char* cat(char* dest, char* src);
char* m_cats(int size, ...);
char* cpy(char* dest, char* src);
char* m_cpy(char *src);
char* trim(char *str, char deli);

/** conversion methods **/
char* m_itos(int num);
long long btoll(byte *b);
int btoi(byte *b);
short btos(byte *b);
char* m_lltos(long long num);
char* m_ctos(char chr);
boolean stob(char* bool_str);
short btos(byte *b);

/** other methods **/
int max(int a, int b);
boolean cmp(char* dest, char* src, int len);
boolean match(char* dest, char *src);
int match_int(char* dest, char* src);
boolean match_for_list_find(void* dest, void *src);
boolean match_tail(char* dest, char *src);
int count(char *string, char target);

/**   string tokens operation part  **/
typedef struct _Tokens
{
    int size;
    char** tokens;
}Tokens;

Tokens* init_tokens(char *str, char deli);
void free_tokens(Tokens* tokens);
List* generate_list_by_token(char* buf, char token);
char* list_to_string_by_token(List* list, char token);

/**   I/O operation part  **/
char* m_load_txt_file_to_memory(char *file_path);
void create_or_rewrite_file(char *file_path, char* content);
boolean file_exist(char* file_path);
int get_file_size(char *file_path);
List* get_files_path_by_ext(char *folder_path, char *ext);
char* m_get_file_name_by_ext(char* folder, char* ext);
char* get_full_file_name(char* file_path);
List* get_lines_from_text_file_base_on_prefix(char* file_path, char* prefix);
List* get_lines_from_text_file(char* file_path);

/** connection string part**/
char* m_get_ip_address(char* connection_string);
int get_port(char* connection_string);
List* string_to_list(char* string);
char* list_to_string(List* list);
char* array_to_string(char** array, int begin_index, int end_index);
int generate_random_int();
long long get_current_time_stamp();
int get_local_partition_free_space();

#endif
