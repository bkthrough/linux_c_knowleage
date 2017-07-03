#include <iostream>
using namespace std;

class apple
{};
class orange
{};
class watermalon
{};

template <typename A>
class traits
{};
//////////////////////////////////////////////////////////////////////////
//重要的：
//模板的特化，就是把一个或者几个template的参数指定为某种类型
//比如下面指定为apple类型，这就是特化
/////////////////////////////////////////////////////////////////////////
//对于偏特化，就是说template的几个参数没有全部都特化
//如：
//template <class A, class B>
//class test{};
//之后的偏特化：
//template <class A>
//class test<int>{};
//只把class B特化了，这就是偏特化
template <>
class traits<apple>
{
public:
    void eat(){cout << "直接吃" << endl;}
};
template <>
class traits<orange>
{
public:
    void eat(){cout << "剥了皮吃" << endl;}
};
template <> class traits<watermalon>
{
public:
    void eat(){cout << "切开吃" << endl;}
};


//这个是总领的类
template <typename T>
class fruit
{
public:
    void eat()
    {
        //根据T的类型执行对应的eat函数
        traits<T>().eat();
    }
};
int main()
{
    fruit<apple> A;
    fruit<orange> B;
    fruit<watermalon> C;

    A.eat();
    B.eat();
    C.eat();

    return 0;
}
