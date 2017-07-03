#ifndef BUF_H_
#define BUF_H_

#include "global.h"

/**  serializing and deserializing methods **/
typedef struct _Buf Buf;
byte* get_buf_data(Buf *buf);
int get_buf_index(Buf *buf);
char* m_get_buf_string(Buf *buf);
Buf* init_buf();
Buf* create_buf(int size, byte* data);
void buf_cat(Buf *buf, void* src, int size);
void buf_combine(Buf* dest_buf, Buf* src_buf);
void* buf_load(Buf* buf, int size);
int buf_load_int(Buf* buf);
long long buf_load_long_long(Buf* buf);
short buf_load_short(Buf* buf);
void destory_buf(Buf* buf);
void free_buf(Buf* buf);

#endif /* BUF_H_ */
