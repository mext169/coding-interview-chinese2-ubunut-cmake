//
// Created by lab on 2021/4/2.
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

// 面试题57（二）：为s的连续正数序列
// 题目：输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、
// 4～6和7～8。

#include <cstdio>

void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
    if(sum < 3)
        return;

    int small = 1;
    int big = 2;
    // 因为至少有2个数，因此较小的那个数不会超过(1 + sum) / 2
    int middle = (1 + sum) / 2;
    int curSum = small + big;

    // 一直循环知道small==middle，这样就能找到所有可能的组合了
    while(small < middle)
    {
        // 如果当前Sum和目标sum相等，说明找到了一组数字，打印
        if(curSum == sum)
            PrintContinuousSequence(small, big);

        // 如果curSum超过了sum，那么就把small减去试试能不能相等
        while(curSum > sum && small < middle)
        {
            curSum -= small;
            // 减去一个small后，small++
            small ++;

            // 判断一下相等了不，如果仍然curSum > sum，那么就继续减
            // 如果curSum < sum了，那么就得加big++了
            if(curSum == sum)
                PrintContinuousSequence(small, big);
        }

        big ++;
        curSum += big;
    }
}

void PrintContinuousSequence(int small, int big)
{
    for(int i = small; i <= big; ++ i)
        printf("%d ", i);

    printf("\n");
}

// ====================测试代码====================
void Test(const char* testName, int sum)
{
    if(testName != nullptr)
        printf("%s for %d begins: \n", testName, sum);

    FindContinuousSequence(sum);
}

int main(int argc, char* argv[])
{
    Test("test1", 1);
    Test("test2", 3);
    Test("test3", 4);
    Test("test4", 9);
    Test("test5", 15);
    Test("test6", 100);

    return 0;
}

