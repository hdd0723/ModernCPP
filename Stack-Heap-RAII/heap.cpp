/*
本例子演示动态分配内存的用法
time: 2020-9-11
author: Chicharito
*/
#include<iostream>
using namespace std;
class bar{

};

// 在同一个函数中动态分配和释放并不符合现代c++惯用法
void foo()
{
    cout<<"Method 1: "<<endl;
    bar* ptr = new bar();
    delete ptr;
}

// c++习惯动态分配和释放空间在不同的函数中
bar* make_bar()
{
    bar* ptr = nullptr;
    try
    {
        ptr = new bar();
    }
    catch(...) // 三个点在c++中表示可变的函数参数
    {
        delete ptr;
        throw;
    }
    return ptr;
}

void foo2()
{
    cout<<"Method 2: "<<endl;
    bar* ptr = make_bar();
    delete ptr;
}

int main(int argc, char **argv)
{
    foo();
    foo2();
    return 0;
}