#include <iostream>

struct __true_type{}; //定义错误和正确两个结构体
struct __false_type{};
template <typename T>
struct type_traits//定义类型萃取结构体
{
    typedef __true_type this_dummy_member_must_be_first;
    typedef __false_type is_POD_type;
};
template <>//特化模板
struct type_traits<char>
{
    typedef __true_type is_POD_type; //类型重定义
};
template <>
struct type_traits<char *>
{
    typedef __false_type is_POD_type;
};
//重载
void fun(__true_type) //针对某种类型定义函数
{
    std::cout << "__true_type\n";
}
void fun(__false_type)
{
    std::cout << "__false_type\n";
}
template <class T>
void test_fun(T)
{
    typedef typename type_traits<T>::is_POD_type is_POD;
    fun(is_POD()); //必须加括号，根据对应的T给出对应的函数
}
int main()
{
    char a;
    char *b;
    test_fun(b);
    return 0;
}
