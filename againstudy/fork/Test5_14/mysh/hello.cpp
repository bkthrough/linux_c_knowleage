#include <iostream>
using namespace std;

class test
{
public:
    test(int value, int s = 0): v(value), sa(s)
    {}
private:
    int v;
    int sa;
};
int main()
{
    test t(2);
    return 0;
}
