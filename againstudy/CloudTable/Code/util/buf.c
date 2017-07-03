#include "buf.h"
#include "utils.h"
#include "malloc2.h"

/**
 *
 *  * Buf is in-memory struct for handling multiple data concatntion.
 *
 *   **/
#define INITIAL_BUF_SIZE 1000

/** The Factor Number is for incrementing the buffer size **/
#define BUF_GROWTH_FACTOR 2

struct _Buf
{
    byte* data;
    int index; /** the pointer of data, not the size of data, its usage will be varied base on the method **/
    int allocated_size; /* the size has been allocated */
};/** Buf is a auto-enlarge buffer for holding temporary data **/

byte* get_buf_data(Buf *buf)
{
    return buf->data;
}

int get_buf_index(Buf *buf)
{
    return buf->index;
}

/** will return a copy of data, but as string format **/
char* m_get_buf_string(Buf *buf)
{
    char* string = mallocs(buf->index);
    return strncpy(string, buf->data, buf->index);
}

Buf* init_buf()
{
    Buf *buf = malloc2(sizeof(Buf));
    buf->index = 0;
    buf->allocated_size = INITIAL_BUF_SIZE;
    buf->data = mallocs(buf->allocated_size);
    return buf;
}

void enlarge_buf(Buf *buf, int size)
{
    int required_len = buf->index + size;
    if(buf->allocated_size < required_len)
    {
        int target_len = buf->allocated_size * BUF_GROWTH_FACTOR;
        if(target_len < required_len) target_len = required_len * BUF_GROWTH_FACTOR;
        buf->allocated_size = target_len;
        buf->data = realloc2(buf->data, buf->allocated_size);
    }
}
/* the container for importing the current data sets  */
Buf* create_buf(int index, byte* data)
{
    Buf *buf = malloc2(sizeof(Buf));
    buf->index = index;
    buf->allocated_size = 0;
    buf->data = data;
    return buf;
}

void buf_cat(Buf *buf, void* src, int size)
{
    enlarge_buf(buf, size);
    void* tmp_dest = buf->data;
    /*locate the dest begin index*/
    tmp_dest+=buf->index;
    memcpy(tmp_dest, src, size);
    buf->index += size;
}

void buf_combine(Buf* dest_buf, Buf* src_buf)
{
    enlarge_buf(dest_buf, src_buf->index);
    void* tmp_dest = dest_buf->data;
    int dest_begin_index = dest_buf->index;
    /*locate the dest begin index*/
    while(dest_begin_index--!=0) tmp_dest++;
    memcpy(tmp_dest, src_buf->data, src_buf->index);
    dest_buf->index += src_buf->index;
}

void* buf_load(Buf* buf, int size)
{
    if(size==0) return NULL;
    /*add 1 for string*/
    void *dest = mallocs(size);
    void *tmp_src = buf->data;
    tmp_src = move_pointer(tmp_src, buf->index);
    memcpy(dest, tmp_src, size);
    buf->index += size;
    return dest;
}

int buf_load_int(Buf* buf)
{
    void* string = buf_load(buf, sizeof(int));
    int integer = btoi(string);
    free2(string);
    return integer;
}

long long buf_load_long_long(Buf* buf)
{
    void* string = buf_load(buf, sizeof(long long));
    long long longlong = btoll(string);
    free2(string);
    return longlong;
}

short buf_load_short(Buf* buf)
{
    void* string = buf_load(buf, sizeof(short));
    short short_int = btos(string);
    free2(string);
    return short_int;
}

void destory_buf(Buf* buf)
{
    if(buf != NULL)
    {
        frees(2, buf, buf->data);
    }
}

/** Won't free it data **/
void free_buf(Buf* buf)
{
    if(buf != NULL)
    {
        free2(buf);
    }
}


