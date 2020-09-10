/*
本例子演示RAII的作用
time: 2020-09-11
author: Chicharito
*/
#include<iostream>
using namespace std;

enum class shape_type{
    circle,
    triangle,
    rectangle
};

class base_shape{
    public:
        base_shape()
        {
            cout<<"base_shape()"<<endl;
        }

        virtual void print()
        {
            cout<<"This is a base_shape."<<endl;
        }

        virtual ~base_shape() {}
};

class circle : public base_shape{
    public:
        circle()
        {
            cout<<"circle()"<<endl;
        }

        virtual void print()
        {
            cout<<"This is a circle."<<endl;
        }

};

class triangle : public base_shape{
    public:
        triangle()
        {
            cout<<"triangle()"<<endl;
        }

        virtual void print()
        {
            cout<<"This is a triangle."<<endl;
        }

};

class rectangle : public base_shape{
    public:
        rectangle()
        {
            cout<<"rectangle()"<<endl;
        }

        virtual void print()
        {
            cout<<"This is a rectangle."<<endl;
        }
};

// 如果这里的返回对象是base_shape,会存在对象切片的问题
base_shape* create_shape(shape_type type)
{
    switch(type)
    {
        case shape_type::circle:
            return new circle();
        case shape_type::rectangle:
            return new rectangle();
        case shape_type::triangle:
            return new triangle();
    }
}

// 如果在栈空间生成一个shape_wrapper对象，对象所处的作用域结束时对象会自动析构
// 所以shape_wrapper指向的动态内存也会被释放，解决了内存泄漏的问题 
class shape_wrapper{
    public:
        explicit shape_wrapper(base_shape* ptr=nullptr) : ptr_(ptr) {}
        ~shape_wrapper(){delete ptr_;}
        base_shape* get() const { return ptr_;}
    private:
        base_shape* ptr_;
};

void foo()
{
    shape_wrapper ptr(create_shape(shape_type::circle));
    ptr.get()->print();
    // 函数结束后对象 ptr 自动析构，会释放指向的动态内存
}

int main(int argc, char **argv)
{
    // 方法一：利用动态多态，防止内存泄漏
    cout<<"Method 1:"<<endl;
    base_shape* ptr = create_shape(shape_type::circle);
    ptr->print();
    delete ptr;
    cout<<"Method 2:"<<endl;

    // 方法二： 将动态内存的指针保存在本地对象中
    foo();
    return 0;
}