/*
本例子演示vector中的empalce_back和push_back的用法的不同
time: 2020-9-23
author: Chicharito
*/

#include<iostream>
#include<vector>
#include<list>
using namespace std;

class Obj1{
    public:
        Obj1()
        {
            cout<<"Obj()"<<endl;
        }

        Obj1(const Obj1&)
        {
            cout<<"Obj1(const Obj1&)"<<endl;
        }

        Obj1(Obj1&&)
        {
            cout<<"Obj1(Obj&&)"<<endl;
        }
};

class Obj2{
    public:
        Obj2()
        {
            cout<<"Obj2()"<<endl;
        }

        Obj2(const Obj2&)
        {
            cout<<"Obj2(const Obj1&)"<<endl;
        }

        Obj2(Obj2&&) noexcept
        {
            cout<<"Obj2(Obj2&&)"<<endl;
        }
};

class Obj3{
    public:
        Obj3() {cout<<"Obj3()"<<endl;}
        Obj3(int n){cout<<"Obj3(int n) "<<n<<endl;}
        Obj3(const Obj3&) {cout<<"const Obj3&"<<endl;}
        Obj3(Obj3&&) noexcept {cout<<"Obj3&&"<<endl;}
};
int main(int argc, char **argv)
{
    vector<Obj1> vec1;
    vec1.reserve(2);
    vec1.emplace_back();
    vec1.emplace_back();
    // 插入第三个对象需要另外重新分配内存，
    // 因此前两个对象会重新复制到容器中
    // 不过使用的是拷贝构造函数
    vec1.emplace_back();

    vector<Obj2> vec2;
    vec2.reserve(2);
    vec2.emplace_back();
    vec2.emplace_back();
    // 由于Obj2中定义了一个不抛异常的移动构造函数
    // 因此重新分配内存时候，原来的对象是移动到新
    // 的内存中
    vec2.emplace_back();
    cout<<"------------------"<<endl;
    vector<Obj3> vec3;
    vec3.reserve(2);
    // push_back先构造，然后再移动
    vec3.push_back(Obj3(1));
    // emplace_back直接在原地进行构造
    vec3.emplace_back(12);
    
}