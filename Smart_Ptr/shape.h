#ifndef SHAPE_H
#define SHAPE_H
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
    return nullptr;
}
#endif