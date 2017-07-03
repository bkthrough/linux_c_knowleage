#include <iostream>
#include <stdio.h>
#include "utili.h"
using namespace std;

int last_flag = NOMODE;
//解决 //
void cpp::deal_with_cppxie(FILE *d_fp, int &mode)
{
    if(mode == NOMODE){
        mode = CPPMODE;
        fputc('/', d_fp);
        fputc('*', d_fp);
    }else if(mode == CPPMODE || mode == CMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == STRMODE){
        //字符串模式，那么不用管，原样输出
        fputc('/', d_fp);
        fputc('/', d_fp);
    }
}
//解决 /*
void cpp::deal_with_xing(FILE *d_fp, int &mode)
{
    if(mode == NOMODE){
        fputc('/', d_fp);
        fputc('*', d_fp);
        mode = CMODE;
    }else if(mode == CPPMODE || mode == CMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == STRMODE){
        fputc('/', d_fp);
        fputc('*', d_fp);
    }
}
//解决 */
void cpp::deal_with_cxie(FILE *d_fp, int &mode)
{
    if(mode == CPPMODE){
        fputc(' ', d_fp);
        fputc(' ', d_fp);
    }else if(mode == CMODE || mode == NOMODE){
        fputc('*', d_fp);
        fputc('/', d_fp);
        mode = NOMODE;
    }else if(mode == STRMODE){
        fputc('*', d_fp);
        fputc('/', d_fp);
    }
}
void cpp::deal_with_end(FILE *s_fp, FILE *d_fp, int &mode)
{
    char c;

    if(mode == NOMODE || mode == CMODE || mode == STRMODE){
        fputc('\n', d_fp);
        goto end;
    }
    c = fgetc(s_fp);
    if(c == EOF && mode == CPPMODE){
        fputc('*', d_fp);
        fputc('/', d_fp);
        fputc('\n', d_fp);
        mode = NOMODE;
        goto end;
    }
    if(mode == CPPMODE){
        if(c == '/'){
            c = fgetc(s_fp);
            if(c == '/'){
                deal_with_cppxie(d_fp, mode);
                fputc('\n', d_fp);
            }
            else if(c == '*'){
                fputc('*', d_fp);
                fputc('/', d_fp);
                fputc('\n', d_fp);
                mode = NOMODE;
                deal_with_xing(d_fp, mode);
            }else if(c == '"'){
                last_flag = mode;
                mode = STRMODE;
                fputc('\n', d_fp);
                fputc('/', d_fp);
                fputc(c, d_fp);
            }else{
                fputc('*', d_fp);
                fputc('/', d_fp);
                fputc('\n', d_fp);
                fputc('/', d_fp);
                mode = NOMODE;
                if(c == EOF || c == '\r')
                    goto end;
                fputc(c, d_fp);
            }
        }else if(c == '"'){
            last_flag = mode;
            mode = STRMODE;
            fputc('\n', d_fp);
            fputc(c, d_fp);
        }else{
            fputc('*', d_fp);
            fputc('/', d_fp);
            fputc('\n', d_fp);
            mode = NOMODE;
            if(c == '\n'){
                fputc('/', d_fp);
                fputc('/', d_fp);
            }
            if(c != '\r')
                fputc(c, d_fp);
        }
    }
end:
    return ;
}
void cpp::deal_with_file(const char *src, const char *dst)
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
                if(c == '/'){
                    deal_with_cxie(d_fp, mode);
                }else{
                    fputc('*', d_fp);
                    if(c != EOF || c != '\r')
                        fputc(c, d_fp);
                }
            }
            else{
                fputc('*', d_fp);
                if(c != EOF)
                    fputc(c, d_fp);
            }
        }else if(c == '"'){
            fputc(c, d_fp);
            if(mode != STRMODE){
                last_flag = mode;
                mode = STRMODE;
            }else if(mode == STRMODE){
                mode = last_flag;
            }
        }else if(c == '\n')
            deal_with_end(s_fp, d_fp, mode);
        else if(c == '\r')
            continue;
        else
            fputc(c, d_fp);
    }
}
