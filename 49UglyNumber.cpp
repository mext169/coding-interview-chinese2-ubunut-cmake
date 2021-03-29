//
// Created by lab on 2021/3/29.
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

// 面试题49：丑数
// 题目：我们把只包含因子2、3和5的数称作丑数（Ugly Number）。求按从小到
// 大的顺序的第1500个丑数。例如6、8都是丑数，但14不是，因为它包含因子7。
// 习惯上我们把1当做第一个丑数。

#include <cstdio>
#include "Timer.h"

// ====================算法1的代码====================
// 如果这个数是2/3/5的倍数，就除以2/3/5，如果最后的结果是1，那么这个数就是丑数，否则不是
bool IsUgly(int number)
{
    while(number % 2 == 0)
        number /= 2;
    while(number % 3 == 0)
        number /= 3;
    while(number % 5 == 0)
        number /= 5;

    return (number == 1) ? true : false;
}

// number从小到大循环，每次判断number是不是丑数，如果是uglyFound+1，循环直到uglyFound=index
// 这样就找到了第index个丑数
int GetUglyNumber_Solution1(int index)
{
    // 输入检测永不忘
    if(index <= 0)
        return 0;

    int number = 0;
    int uglyFound = 0;
    while(uglyFound < index)
    {
        ++number;

        if(IsUgly(number))
            ++uglyFound;
    }

    return number;
}

// ====================算法2的代码====================
int Min(int number1, int number2, int number3);

// solution1需要判断每一个数，这是很低效的；solution2跳过了一些无关的数字
// 丑数应该是另一个丑数乘以2/3/5的结果，因此可以创建一个数组，里面保存排好序的丑数
// 问题是：如何保证里面的数是排好序的？因为前一个丑数乘以3/5可能大于后一个丑数乘以2
int GetUglyNumber_Solution2(int index)
{
    // 输入检测
    if(index <= 0)
        return 0;

    // 新建一个数组，用于保存排好序的丑数
    int *pUglyNumbers = new int[index];
    pUglyNumbers[0] = 1;
    int nextUglyIndex = 1;

    int *pMultiply2 = pUglyNumbers;
    int *pMultiply3 = pUglyNumbers;
    int *pMultiply5 = pUglyNumbers;

    while(nextUglyIndex < index)
    {
        // 生成新的丑数
        int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
        pUglyNumbers[nextUglyIndex] = min;

        // pMultiply2/3/5记录了每个丑数乘以对应的数后会超过当前最大丑数的位置
        // 这些位置用于生成新的丑数
        while(*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply2;
        while(*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply3;
        while(*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply5;

        ++nextUglyIndex;
    }

    int ugly = pUglyNumbers[nextUglyIndex - 1];
    delete[] pUglyNumbers;
    return ugly;
}

int Min(int number1, int number2, int number3)
{
    int min = (number1 < number2) ? number1 : number2;
    min = (min < number3) ? min : number3;

    return min;
}

// ====================测试代码====================
void Test(int index, int expected)
{
    Timer t1;
    if(GetUglyNumber_Solution1(index) == expected)
        printf("solution1 passed\n");
    else
        printf("solution1 failed\n");
    printf("soluiton 1 use : %f ms\n", t1.toc());

    Timer t2;
    if(GetUglyNumber_Solution2(index) == expected)
        printf("solution2 passed\n");
    else
        printf("solution2 failed\n");
    printf("soluiton 2 use : %f ms\n", t2.toc());

}

int main(int argc, char* argv[])
{
    Test(1, 1);

    Test(2, 2);
    Test(3, 3);
    Test(4, 4);
    Test(5, 5);
    Test(6, 6);
    Test(7, 8);
    Test(8, 9);
    Test(9, 10);
    Test(10, 12);
    Test(11, 15);

    Test(1500, 859963392);

    Test(0, 0);

    return 0;
}

