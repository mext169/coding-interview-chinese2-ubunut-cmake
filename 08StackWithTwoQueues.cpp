//
// Created by mext on 2021/2/24.
//

#include <cstdio>
#include "Stack.h"


void Test(int actual, int expected)
{
    if (actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* grgv[])
{
    MyStack<int> stack;

    stack.appendTail(1);
    stack.appendTail(2);
    stack.appendTail(3);

    int tail = stack.deleteTail();
    Test(tail, 3);

    tail = stack.deleteTail();
    Test(tail, 2);

    stack.appendTail(4);
    tail = stack.deleteTail();
    Test(tail, 4);

    stack.appendTail(5);
    tail = stack.deleteTail();
    Test(tail, 5);

    tail = stack.deleteTail();
    Test(tail, 1);

    // stack.deleteTail();
}