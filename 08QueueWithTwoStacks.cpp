//
// Created by mext on 2021/2/24.
//
/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题9：用两个栈实现队列
// 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
// 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。

// CQueue中包含了两个栈
// stack1 向CQueue中添加元素时，实际上push到了stack1中
// stack2 删除元素时用。由于CQueue要求"先入先出",而栈是先入后出的，因此需要先将stack中的元素pop,push到stack2中再弹出
//        这样达到了“先入先出”的效果

// 删除与添加元素的逻辑
// 1. 添加元素都push到stack1中
// 2. 删除元素借助stack2完成，需要完成下面的判断：
//    2.1 stack2是不是空的，如果不是空的，说明元素都存在stack1中，直接在stack1中pop不符合队列的逻辑，因此先将stack1中的元素pop并push到
//        stack2中，这样再从stack2中pop，就满足“先入先出”的要求
//    2.2 此时在判断stack的size是不是0，如果是，那就说明2.1中并没有把元素弄过来，说明两个stack组成的队列中没有元素；如果不是0，直接到2.3
//    2.3 经过2.2后，如果没有报错，说明stack2中是有内容的，因此直接pop即可。

#include <cstdio>
#include "Queue.h"

// ====================测试代码====================
void Test(char actual, char expected)
{
    if(actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
    CQueue<char> queue;

    queue.appendTail('a');
    queue.appendTail('b');
    queue.appendTail('c');

    char head = queue.deleteHead();
    Test(head, 'a');

    head = queue.deleteHead();
    Test(head, 'b');

    queue.appendTail('d');
    head = queue.deleteHead();
    Test(head, 'c');

    queue.appendTail('e');
    head = queue.deleteHead();
    Test(head, 'd');

    head = queue.deleteHead();
    Test(head, 'e');

    return 0;
}


