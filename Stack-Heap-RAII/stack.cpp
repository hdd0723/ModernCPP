/*
本例子演示栈展开的过程
time：2020-09-10
author：Chicharito
*/
#include<iostream>
#include<cstdlib>
using namespace std;
class obj{
    public:
        obj()
        {
            cout<<"obj()"<<endl;
        }
        ~obj()
        {
            cout<<"~obj()"<<endl;
        }
};
// 无论是否发生异常，obj的析构都会发生
void foo(int n)
{
    // 在栈空间分配的内存，在函数结束后会自动释放
    obj o;
    if(n==100)
        throw "Up to 100 now!";
}
int main(int argc, char **argv)
{
    try
    {
        foo(10);
        foo(100);
    }
    catch(const char* s)
    {
        printf("%s\n",s);
    }
    return 0;
}