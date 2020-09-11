/*
本例子实现一个简单的auto_ptr
time: 2020-9-11
author: Chicharito
*/
#include "shape.h"
#include<algorithm>

template<typename T>
class auto_ptr
{
public:
    explicit auto_ptr(T* ptr=nullptr) : ptr_(ptr) {}
    ~auto_ptr() {delete ptr_;}
    T* get() const {return ptr_;}
    // 添加一些指针特有的行为，是这个类用起来像指针
    T& operator*() const {return *ptr_;}
    T* operator->() const {return ptr_;}
    operator bool() const {return ptr_;}

    // 释放auto_ptr对资源的控制权
    T* release()
    {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    // 交换两个auto_ptr的资源
    void swap(auto_ptr& rhs)
    {
        using std::swap;
        swap(this->ptr_, rhs.ptr_);
    }

    // 拷贝构造函数
    auto_ptr(auto_ptr& rhs)
    {
        ptr_ = rhs.release();
    }

    // 拷贝赋值运算符
    auto_ptr& operator=(auto_ptr& rhs)
    {
        // 参数是引用，可以拷贝这个引用对象来进行交换
        auto_ptr(rhs).swap(*this);
        // 下面的用法和上面的等价，都可以实现对rhs的拷贝
        // auto_ptr(rhs.release()).swap(*this);
        return *this;
    }

private:
    T* ptr_;
};

int main(int argc, char **argv)
{
    auto_ptr<base_shape> ptr_1{create_shape(shape_type::circle)};
    // auto_ptr之间的拷贝，原有指针会释放资源的控制权
    auto_ptr<base_shape> ptr_2(ptr_1);
    if(ptr_1.get()==nullptr && ptr_2.get())
        cout<<"In copy construct: p1 --> p2."<<endl;
    
    auto_ptr<base_shape> ptr_3{create_shape(shape_type::rectangle)};
    // auto_ptr之间的赋值，原有的指针也会交出对资源的控制权
    ptr_1 = ptr_3;
    if(ptr_3.get()==nullptr && ptr_1.get())
        cout<<"In assignment construct: p3 --> p1"<<endl;
}