//
// Created by mext on 2021/3/26.
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

// 面试题44：数字序列中某一位的数字
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这
// 个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。请写一
// 个函数求任意位对应的数字。

// 数字比较小的时候，如0-9，每个数字只有一位
// 10-99，每个数字有两位
// 100-999，每个数字有三位

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int countOfIntegers(int digits);
int digitAtIndex(int index, int digits);
int beginNumber(int digits);

int digitAtIndex(int index)
{
    if(index < 0)
        return -1;

    int digits = 1;
    while(true)
    {
        // 计算digits位数共包含了多少个数字
        int numbers = countOfIntegers(digits);
        // numbers * digits 表示digits位包含的所有数字共占了多少位
        // 如果当前的个数已经超了
        if(index < numbers * digits)
            return digitAtIndex(index, digits);

        index -= digits * numbers;
        digits++;
    }

    return -1;
}

// 计算n位数共有多少个数字
// 比如1位数，共有10个数字，0-9
int countOfIntegers(int digits)
{
    if(digits == 1)
        return 10;

    int count = (int) std::pow(10, digits - 1);
    return 9 * count;
}


int digitAtIndex(int index, int digits)
{
    // number是index所指位置的数字
    int number = beginNumber(digits) + index / digits;
    // digits位数从右数第几位数
    int indexFromRight = digits - index % digits;
    for(int i = 1; i < indexFromRight; ++i)
        number /= 10;
    return number % 10;
}

// digits位数字的开始的那个数
int beginNumber(int digits)
{
    if(digits == 1)
        return 0;

    return (int) std::pow(10, digits - 1);
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
    if(digitAtIndex(inputIndex) == expectedOutput)
        cout << testName << " passed." << endl;
    else
        cout << testName << " FAILED." << endl;
}


int main()
{
    test("Test1", 0, 0);
    test("Test2", 1, 1);
    test("Test3", 9, 9);
    test("Test4", 10, 1);
    test("Test5", 189, 9);  // 数字99的最后一位，9
    test("Test6", 190, 1);  // 数字100的第一位，1
    test("Test7", 1000, 3); // 数字370的第一位，3，1000=10+90*2+270*3,
    test("Test8", 1001, 7); // 数字370的第二位，7，1000=10+90*2+270*3+1
    test("Test9", 1002, 0); // 数字370的第三位，0，1000=10+90*2+270*3+2
    return 0;
}