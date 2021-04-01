//
// Created by lab on 2021/4/1.
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

// 面试题56（一）：数组中只出现一次的两个数字
// 题目：一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序
// 找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

#include <cstdio>

unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num, unsigned int indexBit);

void FindNumsAppearOnce(int data[], int length, int* num1, int* num2)
{
    if(data == nullptr || length < 2)
        return;

    // 这里用了异或运算取得了什么效果呢
    // 举个例子：4的二进制表示为0100，要想把这个数通过异或运算变成0，那么只有另外来一个0100才可以完全消除
    // 否则，其他数字通过异或运算消除了一些位的同时，又引入了一些其他位，那么只有再次遇到这个数才可以消除，以此类推
    // 这样就达到了找重复数字的效果，如果一个数字出现两次，那么重复异或运算是可以消除这个数字出现过的痕迹的
    // 但是，如果只出现一次，就无法消除痕迹，最后的异或运算结果就是这个只出现一次的数字
    int resultExclusiveOR = 0;
    for(int i = 0; i < length; ++i)
        resultExclusiveOR ^= data[i];

    // 因为数组中有2个只出现一次的不同数字，那么异或运算的结果一定不是0；我们需要找到这一位
    unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);

    // 上述两个数字在 异或结果的第一位1所在的位置 这一位是不同的，我们可以根据这个特点将原数组划分为两个子数组
    // 如果原数组中任意一个数字的这一位是1，就分为一组；不是1的话，就分为另一组
    // 重复的数字任意位都是相同的，因此可以保证相同的数字分到同一组
    // 通过上述划分后，每一组就只有一个数字只出现一次，于是就可以再次通过异或运算的方式找到各个小组中只出现一次的数字
    *num1 = *num2 = 0;
    for(int j = 0; j < length; ++j)
    {
        if(IsBit1(data[j], indexOf1))
            *num1 ^= data[j];
        else
            *num2 ^= data[j];
    }
}

// 找到num从右边数起第一个是1的位
unsigned int FindFirstBitIs1(int num)
{
    int indexBit = 0;
    // 找到1的位置索引
    while(((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
    {
        num = num >> 1;
        ++indexBit;
    }

    return indexBit;
}

// 判断数字num的第indexBit位是不是1
bool IsBit1(int num, unsigned int indexBit)
{
    // 右移之后和1做与运算，结果为1分为一组，不为1分为另一组
    num = num >> indexBit;
    return (num & 1);
}

// ====================测试代码====================
void Test(const char* testName, int data[], int length, int expected1, int expected2)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    int result1, result2;
    FindNumsAppearOnce(data, length, &result1, &result2);

    if((expected1 == result1 && expected2 == result2) ||
       (expected2 == result1 && expected1 == result2))
        printf("Passed.\n\n");
    else
        printf("Failed.\n\n");
}

void Test1()
{
    int data[] = { 2, 4, 3, 6, 3, 2, 5, 5 };
    Test("Test1", data, sizeof(data) / sizeof(int), 4, 6);
}

void Test2()
{
    int data[] = { 4, 6 };
    Test("Test2", data, sizeof(data) / sizeof(int), 4, 6);
}

void Test3()
{
    int data[] = { 4, 6, 1, 1, 1, 1 };
    Test("Test3", data, sizeof(data) / sizeof(int), 4, 6);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}

