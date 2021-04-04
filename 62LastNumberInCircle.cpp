//
// Created by lab on 2021/4/4.
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

// 面试题62：圆圈中最后剩下的数字
// 题目：0, 1, …, n-1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里
// 删除第m个数字。求出这个圆圈里剩下的最后一个数字。

#include <cstdio>
#include <list>

using namespace std;

// ====================方法1====================
/**
 * 删掉之后，从下一个数开始计数,删掉第m个
 * @param n 一个圈有几个数
 * @param m 每次删掉第几个数字
 * @return 剩下的最后一个数字
 */
int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;

    unsigned int i = 0;

    list<int> numbers;
    for(i = 0; i < n; ++ i)
        numbers.push_back(i);

    // list<int>::iterator end111 = numbers.end();
    // --end111;
    // printf("%d", *end111);
    // list<int>::iterator begin111 = numbers.begin();
    // --end111;
    // printf("%d", *begin111);

    list<int>::iterator current = numbers.begin();
    while(numbers.size() > 1)
    {
        // 循环结束后，current就是需要被删的那个
        for(int i = 1; i < m; ++ i)
        {
            current ++;
            if(current == numbers.end())
                current = numbers.begin();
        }


        list<int>::iterator next = ++ current;
        // TODO
        // 这里next表示下一个数，如果下一个数在链表尾端，为什么直接就跳到链表的开头了了
        // 通过46-51行注释代码的测试，.begin是第一个元素，.end并不是最后一个元素，最后一个元素的后面，类似于EOF
        if(next == numbers.end())
            next = numbers.begin();

        -- current;
        numbers.erase(current);
        current = next;
    }

    return *(current);
}

// ====================方法2====================
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;

    int last = 0;
    for (int i = 2; i <= n; i ++)
        last = (last + m) % i;

    return last;
}

// ====================测试代码====================
void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    if(LastRemaining_Solution1(n, m) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");

    if(LastRemaining_Solution2(n, m) == expected)
        printf("Solution2 passed.\n");
    else
        printf("Solution2 failed.\n");

    printf("\n");
}

void Test1()
{
    Test("Test1", 5, 3, 3);
}

void Test2()
{
    Test("Test2", 5, 2, 2);
}

void Test3()
{
    Test("Test3", 6, 7, 4);
}

void Test4()
{
    Test("Test4", 6, 6, 3);
}

void Test5()
{
    Test("Test5", 0, 0, -1);
}

void Test6()
{
    Test("Test6", 4000, 997, 1027);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}

