#include<iostream>
#include<string>
using namespace std;

class Obj
{
    public:
        Obj()
        {
            cout<<"Obj()"<<endl;
        }

        Obj(const Obj& )
        {
            cout<<"Obj(const Obj&)"<<endl;
        }

        Obj(const Obj&&)
        {
            cout<<"Obj(const Obj&&)"<<endl;
        }
};

Obj simple()
{
    Obj obj;
    // 直接返回对象，一般会有返回值优化（NRVO）
    return obj;
}

Obj simple_with_move()
{
    Obj obj;
    // move会禁止 NRVO
    return std::move(obj);
}

Obj complicated(int n)
{
    Obj obj1;
    Obj obj2;
    if(n%2==0)
        return obj1;
    else
        return obj2;
}



int main(int argc, char **argv)
{
    cout<<"--------case 1: --------"<<endl;
    // 本来应该是一个拷贝构造，但是这里会有NRVO
    Obj obj = simple(); 
    cout<<"--------case 2: --------"<<endl;
    // 返回移动的话，就会禁止使用NRVO
    Obj obj2 = simple_with_move();
    cout<<"--------case 3: --------"<<endl;
    // 禁止使用NRVO
    Obj obj3 = complicated(10);
}