#include<iostream>
#include<algorithm>
using namespace std;

// 计数器
class shared_count
{
    public:
        shared_count() : count_(1) {}
        void add_count() {++count_;}
        long reduce_count() {return --count_;}
        long get_count() const {return count_;}
    private:
        long count_;
};

template<typename T>
class shared_ptr{
    public:
        template<typename U>
        friend class shared_ptr;

        explicit shared_ptr(T* ptr=nullptr) : ptr_(ptr)
        {
            if(ptr) //指向内容非空
            {
                shared_count_ = new shared_count();
            }
        }

        shared_ptr(const shared_ptr& rhs)
        {
            ptr_ = rhs.ptr_;
            // 并不是所有的拷贝都会计数器增加，
            // 还要看是否指向了具体内容
            if(ptr_) 
            {
                rhs.shared_count_->add_count();
                shared_count_ = rhs.shared_count_;
            }
        }

        ~shared_ptr()
        {
            // 计数器返回零，表明这块内存已经没有指针指向它了
            // 指向具体类型的指针清空，指向计数器的指针清空
            if(ptr_ && !shared_count_->reduce_count())
            {
                delete ptr_;
                delete shared_count_;
            }
        }

        void swap(shared_ptr& rhs)
        {
            using std::swap;
            swap(rhs.ptr_, ptr_);
            swap(rhs.shared_count_, shared_count_);
        }

        shared_ptr& operator=(shared_ptr rhs)
        {
            // rhs拷贝传参，因此rhs的计数器加一
            rhs.swap(*this);
            // 交换后，rhs指向this指针原本的内容
            // 函数结束后自动析构计数器内容减一
            return *this;
        }

        // 拷贝构造
        template<typename U>
        shared_ptr(const shared_ptr<U>& rhs)
        {
            ptr_ = rhs.ptr_;
            if(ptr_)
            {
                rhs.shared_count_->add_count();
                shared_count_ = rhs.shared_count_;
            }
        }

        // 移动构造
        template<typename U>
        shared_ptr(shared_ptr<U>&& rhs)
        {
            ptr_ = rhs.ptr_;
            if(ptr_)
            {
                // 注意这里不需要进行计数器加1
                // 因为这里是右值引用，
                shared_count_ = rhs.shared_count_;
                rhs.ptr_ = nullptr;
            }
        }

        long use_count() const 
        {
            if(ptr_)
                return shared_count_->get_count();
            else
                return 0;
        }

    private:
        // 指向具体类型的指针，指向计数器的指针
        T* ptr_;
        shared_count* shared_count_;

};


class shape {
    public: virtual ~shape() {}
};

class circle : public shape {
    public: ~circle() 
    { 
        cout<<"~circle()"<<endl; 
    }
};

int main(int argc, char **argv)
{
    shared_ptr<circle> circle_ptr(new circle());
    cout<<"use count of circle_ptr is "<<circle_ptr.use_count()<<endl;
    shared_ptr<shape> shape_ptr;
    cout<<"use count of base_shape_ptr is "<<shape_ptr.use_count()<<endl;
    shape_ptr = circle_ptr;
    cout<<"use count of circle_ptr is "<<circle_ptr.use_count()<<endl;
    cout<<"use counr of base_shape_ptr is "<<shape_ptr.use_count()<<endl;
    return 0;
}