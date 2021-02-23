//
// Created by mext on 2021/2/20.
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

// 面试题3（二）：不修改数组找出重复的数字
// 题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至
// 少有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改输入的
// 数组。例如，如果输入长度为8的数组{2, 3, 5, 4, 3, 2, 6, 7}，那么对应的
// 输出是重复的数字2或者3。

// 解法一：创建一个长度为n+1的辅助数组。逐一把原数组的每一个数字复制到辅助数组。如果原数组中被复制的数字是m，则把它复制到辅助数组中下标为m的位置。
//        这个方法需要O(n)的辅助空间
// 解法二：长度为n+1的数组包含了n个数，那么至少有一个重复数字，即至少有一个数字出来的次数大于1。
//       如题，将区间[1,n]分为两部分，分别统计这两部分中的数字在给定数组里出现的次数的和，如果出现的次数大于小区间数字的个数，那么这个小区间中一定
//       包含着重复数字，那么就再一次将这个小区间划分。这样一致操作下去，直到小区间中只包含一个数字，这样就可以统计粗来一个重复出现多次的数字。
//       具体实现看下面的代码
//       注：这个算法不能保证找出所有重复的数字，因为对于例如[1,2]这样的小区间，对数组{1,2}和{2,2}的统计效果是相同的，如果不对这个小区间进行
//       细分是找不出来的，但是可能这个小区间没有再细分的机会了，因此不能找出来了

#include <iostream>

int countRange(const int* numbers, int length, int start, int end);

// 参数:
//        numbers:     一个整数数组
//        length:      数组的长度
// 返回值:
//        正数  - 输入有效，并且数组中存在重复的数字，返回值为重复的数字
//        负数  - 输入无效，或者数组中没有重复的数字
int getDuplication(const int* numbers, int length)
{
    // 防止输入为空
    if(numbers == nullptr || length <= 0)
        return -1;

    // 设置二分法的起点和终点
    int start = 1;
    int end = length - 1;
    while(end >= start)
    {
        int middle = ((end - start) >> 1) + start;
        // 统计原数组中在start到middle范围内的元素的个数
        int count = countRange(numbers, length, start, middle);

        // 是不是已经划分到只有一个元素的小区间了
        // 如果小区间对应的数在原数组中出现了大于1次，那么这个小区间对应的数就是重复的这个数了
        if(end == start)
        {
            if(count > 1)
                return start;
            else
                break;
        }

        // 如果count大于当前区间长度，那么这个区间里有重复数组，下次循环划分这个区间
        // 否则下次循环划分另一个区间
        if(count > (middle - start + 1))
            end = middle;
        else
            start = middle + 1;
    }
    return -1;
}

/**
 * 如果数组的元素在区间范围内，就统计一个
 * @param numbers
 * @param length
 * @param start
 * @param end
 * @return
 */
int countRange(const int* numbers, int length, int start, int end)
{
    // 防止输入为空指针
    if(numbers == nullptr)
        return 0;

    int count = 0;
    for(int i = 0; i < length; i++)
        if(numbers[i] >= start && numbers[i] <= end)
            ++count;
    return count;
}

// ====================测试代码====================

/**
 *
 * @param testName 测试名
 * @param numbers 测试的数组
 * @param length 测试数组的长度
 * @param duplications 测试数组中的重复数组组成的数组
 * @param dupLength 测试数组中重复数字的个数
 */
void test(const char* testName, int* numbers, int length, int* duplications, int dupLength)
{
    int result = getDuplication(numbers, length);
    for(int i = 0; i < dupLength; ++i)
    {
        if(result == duplications[i])
        {
            std::cout << testName << " passed." << std::endl;
            return;
        }
    }
    std::cout << testName << " FAILED." << std::endl;
}

// 多个重复的数字
void test1()
{
    int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
    int duplications[] = { 2, 3 };
    test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个重复的数字
void test2()
{
    int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7 };
    int duplications[] = { 4 };
    test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最小的数字
void test3()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8 };
    int duplications[] = { 1 };
    test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最大的数字
void test4()
{
    int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8 };
    int duplications[] = { 8 };
    test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 数组中只有两个数字
void test5()
{
    int numbers[] = { 1, 1 };
    int duplications[] = { 1 };
    test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字位于数组当中
void test6()
{
    int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7 };
    int duplications[] = { 3 };
    test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 多个重复的数字
void test7()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 6 };
    int duplications[] = { 2, 6 };
    test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个数字重复三次
void test8()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 2 };
    int duplications[] = { 2 };
    test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 没有重复的数字
void test9()
{
    int numbers[] = { 1, 2, 6, 4, 5, 3 };
    int duplications[] = { -1 };
    test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 无效的输入
void test10()
{
    int* numbers = nullptr;
    int duplications[] = { -1 };
    test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}
