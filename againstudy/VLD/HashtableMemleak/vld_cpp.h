#pragma once

void *operator new(size_t sz, int line, const char *file);
void *operator new[](size_t sz, int line, const char *file);
void operator delete(void *ptr);
void operator delete[](void *ptr);


