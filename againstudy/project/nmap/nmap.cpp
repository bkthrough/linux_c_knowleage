#include "syn.h"
#include "fin.h"
#include "all.h"
#include "muti.h"
int main()
{
    int num;
    int min, max;
    const char *ip = "127.0.0.1";

    for(;;){
        cout << "******************************" << endl;
        cout << "*  [0]all      [1]muti       *" << endl;
        cout << "*  [2]syn      [3]fin        *" << endl;
        cout << "*  [4]help     [5]quit       *" << endl;
        cout << "******************************" << endl;
        cout << "请输入序号：";
        cin >> num;
        switch(num){
            case 0:
                cout << "请输入端口区间：";
                cin >> min >> max;
                deal_with_all((char *)ip, min, max);
                break;
            case 1:
                cout << "请输入端口区间：";
                cin >> min >> max;
                deal_with_muti((char *)ip, min, max);
                break;
            case 2:
                cout << "请输入端口区间：";
                cin >> min >> max;
                synscan((char *)ip, min, max);
                break;
            case 3:
                cout << "请输入端口区间：";
                cin >> min >> max;
                deal_with_fin((char *)ip, min, max);
                break;
            case 4:
                //deal_with_help();
                break;
            case 5:
                cout << "quit";
                return 0;
        }
    }
}
