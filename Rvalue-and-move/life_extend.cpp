#include<iostream>
using namespace std;

class shape 
{   
    public: 
        virtual ~shape() {}
};

class circle : public shape 
{
    public: circle() 
    { 
        cout<<"circle()"<<endl;
    } 
    ~circle() 
    { 
        cout<<"~circle()"<<endl;
    }
};

class triangle : public shape 
{   
    public: 
        triangle() 
        { 
            cout<<"triangle()"<<endl;
        } 
        ~triangle() 
        { 
            cout<<"~triangle()"<<endl;
        }
};

class result 
{
    public: result() 
    { 
        cout<<"result()"<<endl;
    } 
    ~result() 
    { 
        cout<<"~result()"<<endl;
    }
};

// 返回一个临时对象，是一个纯右值
result process_shape(const shape& s1, const shape& s2)
{
    cout<<"In process_shape()"<<endl;
    return result();
}


int main(int argc, char **argv)
{
    cout<<"In main()"<<endl;
    // circle(),triangle()会先创建，返回的result最后创建
    // 但是最先被析构
    process_shape(circle(), triangle());
    cout<<"---------------------------"<<endl;
    // 如果让一个右值引用绑定到纯右值上，就会延长这个右值的生命周期到整个
    // main的最后，result()不仅会在circle()和triangle()之后析构
    // 这个纯右值的生命周期将和这个右值引用的生命周期一样长
    result&& r = process_shape(circle(), triangle());
    cout<<"----------------------------"<<endl;
    // 右值引用绑定纯右值会延长这个纯右值的生命周期，但如果不是纯右值，就会失效
    // 将和第一种情况一样
    result&& r2 = std::move(process_shape(circle(), triangle()));
    cout<<"End"<<endl;
}