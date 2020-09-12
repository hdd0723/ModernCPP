#include "shape.h"
#include<algorithm>
template<typename T>
class unique_ptr
{
    public:
        unique_ptr(T* ptr=nullptr) : ptr_(ptr) {}
        ~unique_ptr() {delete ptr_;}
        T* get() const {return ptr_;}

        // 添加类似指针的用法
        T& operator*() {return *ptr_;}
        T* operator->() {return ptr_;}
        // 转为bool型数据
        operator bool() {return ptr_;}

        // 释放资源的管理权
        T* release()
        {
            T* temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }

        // 定义移动构造函数
        unique_ptr(unique_ptr&& rhs)
        {
            cout<<"Move Constructor: "<<endl;
            ptr_ = rhs.release();
        }

        void swap(unique_ptr& rhs)
        {
            using std::swap;
            swap(this->ptr_, rhs.ptr_);
        }

        unique_ptr& operator=(unique_ptr rhs)
        {
            rhs.swap(*this);
            return *this;
        }

        // circle*可以转为shape*，但是指向circle的unique_ptr不能转为
        // base_shape的unique_ptr, 加入下面的构造函数就可以
        template<typename U>
        unique_ptr(unique_ptr<U>&& rhs)
        {
            cout<<"Move Constructor from subclass to baseclass.";
            ptr_ = rhs.release();
        }
    private:
        T* ptr_;
};

int main(int argc, char **argv)
{
    unique_ptr<base_shape> ptr1(create_shape(shape_type::circle));
    // unique_ptr<base_shape> ptr2{ptr1}; // 没有手动定义拷贝构造讲报错
    // unique_ptr<base_shape> ptr3 = ptr1; // 调用拷贝构造函数，报错原因同上
    unique_ptr<base_shape> ptr4;
    // ptr4 = ptr1;    // 赋值的时候会调用拷贝拷贝构造函数，报错原因同上
    ptr4 = std::move(ptr1);
    if(ptr1.get()==nullptr && ptr4.get()!=nullptr)
        ptr4.get()->print();
    unique_ptr<base_shape> ptr5(std::move(ptr4));
    if(ptr5.get()!=nullptr && ptr4.get()==nullptr)
        ptr5.get()->print();
    // create返回的是一个基类指针，不能用来初始化unique_ptr<circle>类对象
    // unique_ptr<circle> circle_ptr(create_shape(shape_type::circle));
    unique_ptr<circle> circle_ptr{new circle()};
    unique_ptr<base_shape> base_ptr(std::move(circle_ptr));
    return 0;
}
