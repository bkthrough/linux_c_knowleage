#include <iostream>
#include <map>
using namespace std;

int main()
{
    int array[] = {1,92,13,15,23,16,7,8,9};
    int array1[] = {1,38,92,13,16};

    map<int, int> m;
    for(int i = 0; i < 10; ++i){
        m[array[i]] = i;
    }
    map<int, int> :: iterator it;
    for(int i = 0; i < sizeof(array1)/sizeof(int); ++i){
        it = m.find(array1[i]);
        if(it == m.end()){
        }else{
            cout << it->second << endl;
        }
    }
}
