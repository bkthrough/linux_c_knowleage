#pragma once

enum{CPPMODE, CMODE, NOMODE, STRMODE};
enum{CPP, C};

class base
{
public:
    base(){}
    ~base(){}
public:
    virtual void deal_with_cppxie(FILE *d_fp, int &mode)=0;
    virtual void deal_with_cxie(FILE *d_fp, int &mode)=0;
    virtual void deal_with_xing(FILE *d_fp, int &mode)=0;
    virtual void deal_with_end(FILE *s_fp, FILE *d_fp, int &mode)=0;
    virtual void deal_with_file(const char *src, const char *dst)=0;
};
class cpp:public base
{
public:
    void deal_with_cppxie(FILE *d_fp, int &mode);
    void deal_with_cxie(FILE *d_fp, int &mode);
    void deal_with_xing(FILE *d_fp, int &mode);
    void deal_with_end(FILE *s_fp, FILE *d_fp, int &mode);
    void deal_with_file(const char *src, const char *dst);
};
class c:public base
{
public:
    void deal_with_cppxie(FILE *d_fp, int &mode);
    void deal_with_cxie(FILE *d_fp, int &mode);
    void deal_with_xing(FILE *d_fp, int &mode);
    void deal_with_end(FILE *s_fp, FILE *d_fp, int &mode);
    void deal_with_file(const char *src, const char *dst);
};
