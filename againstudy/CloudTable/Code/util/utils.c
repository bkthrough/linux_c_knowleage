#include "list.h"
#include "utils.h"
#include "malloc2.h"
#include "log.h"
#include "buf.h"

/**   string normal operation part  **/
/** the safe implmenetaion of strcat **/
char* move_pointer(char* pointer, int div)
{
    char* temp = pointer;
    int i=0;
    for(i=0; i<div; i++) temp++;
    return temp;
}

char* cat(char* dest, char* src)
{
    return strncat(dest, src, strlen(src));
}

/**allocate a memory chunk and concat multiple strings**/
char* m_cats(int size, ...)
{
    char *dest = mallocs(10);
    va_list ap;
    int i=0;
    
    va_start(ap, size);
    for(i=0; i<size; i++)
    {
        char *str = va_arg(ap, char *);
        int len = strlen(dest) + strlen(str);
        dest = realloc2(dest, len + 1);
        cat(dest, str);
        dest[len] = '\0';
    }
    return dest;
}
/** the safe implmenetaion of strcpy, need to make sure
 *
 *  * the size of dest is bigger than the size of src + 1 **/
char* cpy(char* dest, char* src)
{
    memset(dest, 0, strlen(src)+1);
    return strncpy(dest, src, strlen(src));
}

/** will create a memory chunk, before cpy, and needs to be freed**/
char* m_cpy(char *src)
{
    char *s = mallocs(strlen(src));
    return cpy(s, src);
}

char* trim(char *str, char deli)
{
    /*remove left side*/
    while(*str == deli)
    {
        str++;
    }
    /*remove right side*/
    char* tmp = str;
    while(*tmp != '\0')tmp++;
    tmp--;
    
    while(*tmp == deli)
    {
        *tmp = '\0';
        tmp--;
    }
    return str;
}



/** other methods **/
int max(int a, int b)
{
    int max = a > b? a : b;
    return max;
}

/** the simple implmenetaion for strncmp, and ignore case **/
boolean cmp(char* dest, char* src, int len)
{
    boolean result = false;
    if(strncasecmp(dest, src, len)==0) result = true;
    return result;
}

/** the safe version of cmp,  will used max len between the two strings and ignore case **/
boolean match(char* dest, char *src)
{
    int max_len = max(strlen(dest), strlen(src));
    /** Base on previous experience, strcmp may not fit for this situation **/
    return cmp(dest, src, max_len);
}

/**The match method for returning int compare result**/
int match_int(char* dest, char* src)
{
    int max_len = max(strlen(dest), strlen(src));
    return strncasecmp(dest, src, max_len);
}

/** the match method for list find **/
boolean match_for_list_find(void* dest, void *src)
{
    char* tmp_dest = (char*)dest;
    char* tmp_src = (char*)src;
    return match(tmp_dest, tmp_src);
}

/** if the tail of dest is as same as src **/
boolean match_tail(char* dest, char *src)
{
    char* tmp_dest = dest;
    char* ptr = NULL;
    /*find the rightmost match string*/
    while(1)
    {
        tmp_dest = strstr(tmp_dest, src);
        if(tmp_dest != NULL)
        {
            ptr = tmp_dest;
            tmp_dest++;
        }
        else
        {
            break;
        }
    }
    if(ptr == NULL) return false;
    /*check if the tmp_dest is at the tail*/
    ptr = move_pointer(ptr, strlen(src));
    if( *ptr == '\0') return true;
    else return false;
}

/** count the occurrence of target char inside the string **/
int count(char *string, char target)
{
    int occurrence = 0;
    while(*string != '\0')
    {
        if(*string == target) occurrence++;
        string++;
    }
    return occurrence;
}

/** conversion methods **/
/** byte and char are very different, need to make sure to use the right to handle it **/
/** integer to string **/

char* m_itos(int num)
{
    char *str = mallocs(20);
    sprintf(str, "%d", num);
    return str;
}

/** long long to string **/
char* m_lltos(long long num)
{
    char *str = mallocs(50);
    sprintf(str, "%lld", num);
    return str;
}

/** char to string **/
char* m_ctos(char chr)
{
    char *str = mallocs(1);
    sprintf(str, "%c", chr);
    return str;
}

/** string to boolean **/
boolean stob(char* bool_str)
{
    if(match(bool_str, true_str))
    {
        return true;
    }
    else 
        return false;
}

/** byte to integer, is necessary when loading integer from bytes **/
int btoi(byte *b)
{
    return *((int *)b);
}

/** byte to long long **/
long long btoll(byte *b)
{
    return *((long long *)b);
}

/** byte to short **/
short btos(byte *b)
{
    return *((short *)b);
}

/**   string tokens operation part  **/
/** this method will remove  the token which is empty or just have a lot of space **/
Tokens* clean_tokens(Tokens* tokens)
{
    int i=0;
    for(i=0; i<tokens->size; i++)
    {
        trim(tokens->tokens[i], ' ');
        if(strlen(tokens->tokens[i]) == 0)
        {
            tokens->size--;
            free2(tokens->tokens[i]);
            if(i<tokens->size - 1)
                tokens->tokens[i] = tokens->tokens[i+1];
        }
    }
    return tokens;
}

/*
 *
 *  * sample str: name, sex,  home_address, work_address
 *
 *   * sample deli: , may have some issue on deli
 *
 *    */

Tokens* init_tokens(char *str, char deli)
{
    Tokens *tokens = malloc2(sizeof(Tokens));
    tokens->size = 0;
    if(str == NULL || strlen(str) == 0) return tokens;
    char *tmp = str;
    int i = 0, len = strlen(str);
    int max_times = count(tmp, deli) + 1;
    tokens->tokens = malloc2(max_times * sizeof(char*));
    tokens->tokens[0] = mallocs(len);
    boolean prev_matched = false;
    while(*tmp != '\0')
    {
        if(*tmp == deli)
        {
            if(!prev_matched)
            {
                i++;
                tokens->tokens[i] = mallocs(len);
            }
            prev_matched = true;
        }
        else
        {
            prev_matched = false;
            strncat(tokens->tokens[i],tmp,1);
        }
        tmp++;
    }
    tokens->size = i + 1 ;
    return clean_tokens(tokens);
}
/*
 *
 *  * since the tokens has a nested array, it needs a method to free
 *
 *   */
void free_tokens(Tokens* tokens)
{
    int i=0;
    for(i=0; i<tokens->size; i++)
    {
        free2(tokens->tokens[i]);
    }
    free2(tokens);
}
List* generate_list_by_token(char* bytes, char token)
{
    List* list = list_create();
    Tokens* tokens = init_tokens(bytes, token);
    int i=0;
    for(i=0; i<tokens->size; i++)
    {
        if(strlen(tokens->tokens[i]) == 0) continue;
        char* item = m_cpy(tokens->tokens[i]);
        list_append(list, item);
    }
    free_tokens(tokens);
    return list;
}

char* list_to_string_by_token(List* list, char token)
{
    Buf* buf = init_buf();
    char *token_string = m_ctos(token);
    int size = list_size(list);
    int i=0;
    for(i=0; i<size; i++)
    {
        char *value = list_next(list);
        buf_cat(buf, value, strlen(value));
        buf_cat(buf, token_string, strlen(token_string));
    }
    char* result = m_get_buf_string(buf);
    trim(result, token);
    free2(token_string);
    list_rewind(list);
    destory_buf(buf);
    return result;
}

/**   I/O operation part  **/
/** if returns 0, that means the file not exist**/
char* m_load_txt_file_to_memory(char *file_path)
{
    int file_size = get_file_size(file_path);
    if(file_size == 0) return NULL;
    char *buffer = mallocs(file_size);
    FILE *fp = fopen(file_path, "r");
    fread(buffer, file_size,1, fp);
    fclose(fp);
    return buffer;
}

/** If the file can not be created, the system will be aborted!!!
 *
 *  *  Besides the content can be NULL, if just want to created the file.
 *
 *   * **/

void create_or_rewrite_file(char *file_name, char* content)
{
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) 
    {
        logg(EMERG, "can not create this file %s.", file_name);
        exit(-1);
    }
    if(content != NULL)
    {
        fwrite(content, strlen(content), 1, fp);
    }
    fclose(fp);
}

boolean file_exist(char* file_path)
{
    boolean result = false;
    FILE *fp = fopen(file_path, "r");
    if(fp != NULL)
    {
        result = true;
        fclose(fp);
    }
    return result;
}

/** If the file can not be handle, the system will be aborted!!! **/
int get_file_size(char *file_path)
{
    FILE *fp = fopen(file_path, "r");
    if(fp == NULL)
    {
        logg(EMERG, "Can not open the file %s.", file_path);
        exit(-1);
    }
    fseek(fp,0,SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

/** will get file name before  first '.' with first file with this ext **/

List* get_files_path_by_ext(char *folder_path, char *ext)
{
    List *fileList = list_create();
    DIR *dir = opendir(folder_path);
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL) 
    {
        if(match_tail(dp->d_name, ext))
        {
            char *file_path = m_cats(3, folder_path, FOLDER_SEPARATOR_STRING, dp->d_name);
            list_append(fileList, file_path);
        }
    }
    closedir(dir);
    return fileList;
}

char* m_get_file_name_by_ext(char* folder, char* ext)
{
    List *files = get_files_path_by_ext(folder, ext);
    Tokens* tokens = init_tokens(get_full_file_name(list_get(files, 0)), MID_SEPARATOR);
    char* file_name = m_cpy(tokens->tokens[0]);
    free_tokens(tokens);
    return file_name;
}

/** will the file name with ext **/
char* get_full_file_name(char* file_path)
{
    char* file_name = file_path;
    char* tmp = file_name;
    while( *tmp++ != '\0')
    {
        if(*tmp ==  FOLDER_SEPARATOR)
        {
            file_name = tmp + 1;
        }
    }
    return file_name;
}

List* get_lines_from_text_file(char* file_path)
{
    char* file_content = m_load_txt_file_to_memory(file_path);
    List* lines = generate_list_by_token(file_content, LINE_SEPARATOR);
    free2(file_content);
    return lines;
}

List* get_lines_from_text_file_base_on_prefix(char* file_path, char* prefix)
{
    List* lines = get_lines_from_text_file(file_path);
    List* newLines = list_create();
    char* line = NULL;
    while((line = list_next(lines)) != NULL)
    {
        if(cmp(line, prefix, strlen(prefix)))
            list_append(newLines, m_cpy(line));
    }
    list_destory(lines, just_free);
    return newLines;
}

/** conn string part **/
char* m_get_ip_address(char* connection_string)
{
    char* ip_address = NULL;
    Tokens* tokens = init_tokens(connection_string, ':');
    ip_address = m_cpy(tokens->tokens[0]);
    free_tokens(tokens);
    return ip_address;
}

int get_port(char* connection_string)
{
    Tokens* tokens = init_tokens(connection_string, ':');
    int port = atoi(tokens->tokens[1]);
    free_tokens(tokens);
    return port;
}

/** only allows character list **/
List* string_to_list(char* list_string)
{
    return generate_list_by_token(list_string, STRING_SEPARATOR);
}

/** only allows character list **/
char* list_to_string(List* list)
{
    return list_to_string_by_token(list, STRING_SEPARATOR);
}
/** The begin index is starts at zero **/
char* array_to_string(char** array, int begin_index, int end_index)
{
    char* string = NULL;
    Buf* buf = init_buf();
    buf_cat(buf, array[begin_index], strlen(array[begin_index]));
    int i = 0;
    for(i = begin_index+1; i<=end_index; i++)
    {
        buf_cat(buf, " ", strlen(" "));
        char* part = array[i];
        buf_cat(buf, part, strlen(part));
    }
    string = m_get_buf_string(buf);
    free_buf(buf);
    return string;
}

/** return should be between 0 to 100**/
int generate_random_int()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday (&tv , &tz);
    srand(tv.tv_usec);
    int percent = rand() % 100;
    return percent;
}
/* should get timestamp base on micro seconds */
long long get_current_time_stamp()
{
    struct timeval t;
    gettimeofday (&t, NULL);
    long long time_mills = (long long)t.tv_sec * 1000;
    time_mills +=(long long) t.tv_usec/1000;
    return time_mills;
}

/** The Unit is MB **/
int get_local_partition_free_space()
{
    char* local_dir = ".";
    struct statfs diskInfo;
    statfs(local_dir, &diskInfo);
    unsigned long long totalBlocks = diskInfo.f_bsize;
    unsigned long long freeDisk = diskInfo.f_bavail*totalBlocks;
    return freeDisk / MB;
}
