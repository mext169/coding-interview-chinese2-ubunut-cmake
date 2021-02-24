//
// Created by mext on 2021/2/24.
//

//===============================================
//    用两个queue实现一个stack
//===============================================

#ifndef CODING_INTERVIEW_CHINESE2_CMAKE_STACK_H
#define CODING_INTERVIEW_CHINESE2_CMAKE_STACK_H

#include <queue>
#include <stdexcept>

template <typename T>
class MyStack{
public:
    MyStack();
    ~MyStack();

    // 在栈末尾添加一个节点
    void appendTail(const T& node);

    // 删除栈的末尾节点
    T deleteTail();

private:
    std::queue<T> queue1;
    std::queue<T> queue2;
};

template <typename T>
MyStack<T>::MyStack() {

}

template <typename T>
MyStack<T>::~MyStack() {

}

template <typename T>
void MyStack<T>::appendTail(const T &node) {
    if (queue1.empty() && queue2.empty())
    {
        queue1.push(node);
    }
    else
    {
        queue1.size() > queue2.size() ? queue1.push(node) : queue2.push(node);
    }
}

template <typename T>
T MyStack<T>::deleteTail() {
    T tail;
    if (queue1.size() > queue2.size() && queue2.empty())
    {
        while (queue1.size() > 1)
        {
            T& data = queue1.front();
            queue1.pop();
            queue2.push(data);
        }
        tail = queue1.front();
        queue1.pop();
    }
    else if (queue2.size() > queue1.size() && queue1.empty())
    {
        while (queue2.size() > 1)
        {
            T& data = queue2.front();
            queue2.pop();
            queue1.push(data);
        }
        tail = queue2.front();
        queue2.pop();
    }
    else
    {
        std::logic_error e("stack is empty");
        throw e;
    }
    return tail;
}




#endif //CODING_INTERVIEW_CHINESE2_CMAKE_STACK_H
