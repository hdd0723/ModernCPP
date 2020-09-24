/*
本例中实现一些配合函数对象使用的容器
time: 2020-09-24
author: Chicharito
*/
#include<queue>
#include<iostream>
#include<vector>
#include<string>
#include<functional>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
int main(int argc, char **argv)
{
    vector<int> vec{5,3,7,2,9};
    // 默认从小到大
    sort(vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), [](int num){cout<<num<<" ";});

    // 设置从大到小
    cout<<endl<<endl;
    sort(vec.begin(), vec.end(), greater<int>());
    for_each(vec.begin(), vec.end(), [](int num){cout<<num<<" ";});

    // 映射int*为其他的值
    cout<<endl<<endl;
    auto hp = hash<int*>();
    cout<<"hp(nullptr) = "<<hp(nullptr)<<endl;
    cout<<"hp(vec.data()) = "<<hp(vec.data())<<endl;
    cout<<"vec.data() = "<<static_cast<void*>(vec.data())<<endl;

    auto hs = hash<string>();
    cout<<"hs(\"hello\") = "<<hs("hello")<<endl;
    cout<<"hs(\"hellp\") = "<<hs("hellp")<<endl;

    // 优先队列配合函数对象使用
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({1,2});
    q.push({1,3});
    q.push({2,3});
    while(!q.empty())
    {
        cout<<q.top().first<<" "<<q.top().second<<endl;
        q.pop();
    }
    cout<<"-----------------------"<<endl;

    multiset<int> s = {3,4,4,2,3,5,1,2,7};
    multiset<int>::iterator lower,higher;
    std::tie(lower, higher) = s.equal_range(3);
    while(lower!=higher)
    {
        cout<<*lower<<" ";
        ++lower;
    }
}