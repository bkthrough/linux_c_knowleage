#include <iostream>
#include <stdio.h>
#include "utili.h"
using namespace std;

int l_flag = NOMODE;
void c::deal_with_cppxie(FILE *d_fp, int &mode)
{
    if(mode == NOMODE){
        mode = CPPMODE;
        fputc('/', d_fp);
        fputc('/', d_fp);
    }else if(mode == CMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == STRMODE || mode == CPPMODE){
        fputc('/', d_fp);
        fputc('/', d_fp);
    }
}
void c::deal_with_xing(FILE *d_fp, int &mode)
{
    if(mode == NOMODE){
        fputc('/', d_fp);
        fputc('/', d_fp);
        mode = CMODE;
    }else if(mode == CPPMODE || mode == CMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == STRMODE){
        fputc('/', d_fp);
        fputc('*', d_fp);
    }
}
void c::deal_with_cxie(FILE *d_fp, int &mode)
{
    if(mode == CPPMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == CMODE || mode == NOMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
        mode = NOMODE;
    }else if(mode == STRMODE){
        fputc('*', d_fp);
        fputc('/', d_fp);
    }
}
void c::deal_with_end(FILE *s_fp, FILE *d_fp, int &mode)
{
    char c;

    if(mode == NOMODE || mode == STRMODE || mode == CPPMODE){
        fputc('\n', d_fp);
        if(mode == CPPMODE)
            mode = NOMODE;
        goto end;
    }
    c = fgetc(s_fp);
    if(mode == CMODE){
        if(c == '"'){
            l_flag = mode;
            mode = STRMODE;
            fputc('\n', d_fp);
            fputc('/', d_fp);
            fputc('/', d_fp);
            fputc(c, d_fp);
            goto end;
        }else if(c == '*'){
            c = fgetc(s_fp);
            fputc('\n', d_fp);
            if(c == '/'){
                mode = NOMODE;
                fputc('/', d_fp);
                fputc('/', d_fp);
            }else{
                fputc('/', d_fp);
                fputc('/', d_fp);
                fputc('*', d_fp);
                if(c != '\r')
                    fputc(c, d_fp);
            }
        }else if(c != '\r' || c != EOF){
            fputc('\n', d_fp);
            fputc('/', d_fp);
            fputc('/', d_fp);
            fputc(c, d_fp);
            if(c == '\n'){
                fputc('/', d_fp);
                fputc('/', d_fp);
            }
        }
    }
end:
    return ;
}
void c::deal_with_file(const char *src, const char *dst)
{
    FILE *s_fp = NULL;
    FILE *d_fp = NULL;
    int mode = NOMODE;
    char c;

    s_fp = fopen(src, "r");
    d_fp = fopen(dst, "w");

    while(EOF != (c = fgetc(s_fp))){
        if(c == '/'){
            if(mode == STRMODE){
                fputc(c, d_fp);
                continue;
            }
            c = fgetc(s_fp);
            if(c == '/')
                deal_with_cppxie(d_fp, mode);
            else if(c == '*')
                deal_with_xing(d_fp, mode);
            else if(c == '"'){
                if(mode == STRMODE)
                    mode = l_flag;
                else
                    mode = STRMODE;
                fputc(c, d_fp);
            }
            else if(c == '\n'){
                fputc('/', d_fp);
                deal_with_end(s_fp, d_fp, mode);
            }
            else{
                putc('/', d_fp);
                if(c != EOF && c != '\r')
                    putc(c, d_fp);
            }
        }else if(c == '*'){
            if(mode == STRMODE){
                fputc(c, d_fp);
                continue;
            }
            c = fgetc(s_fp);
            if(c == '/')
                deal_with_cxie(d_fp, mode);
            else if(c == '*'){
                fputc('*', d_fp);
                while('*' == (c = fgetc(s_fp))){
                    fputc('*', d_fp);
                }
                if(c == '/')
                    deal_with_cxie(d_fp, mode);
                else{
                    fputc('*', d_fp);
                    if(c != EOF || c != '\r')
                        fputc(c, d_fp);
                }
            }
            else if(c == '"'){
                if(mode == STRMODE){
                    mode = l_flag;
                }else{
                    l_flag = mode;
                    mode = STRMODE;
                }
                fputc(c, d_fp);
            }
            else if(c == '\n'){
                fputc('*', d_fp);
                deal_with_end(s_fp, d_fp, mode);
            }
            else{
                fputc('*', d_fp);
                if(c != EOF && c != '\r')
                    fputc(c, d_fp);
            }
        }else if(c == '"'){
            fputc(c, d_fp);
            if(mode != STRMODE){
                l_flag = mode;
                mode = STRMODE;
            }else if(mode == STRMODE){
                mode = l_flag;
            }
        }else if(c == '\n')
            deal_with_end(s_fp, d_fp, mode);
        else if(c == '\r')
            continue;
        else
            fputc(c, d_fp);
    }
}
