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

// 面试题50（一）：字符串中第一个只出现一次的字符
// 题目：在字符串中找出第一个只出现一次的字符。如输入"abaccdeff"，则输出
// 'b'。

#include <cstdio>
#include <string>

char FirstNotRepeatingChar(const char* pString)
{
    // 输入检测
    if(pString == nullptr)
        return '\0';

    const int tableSize = 256;
    // 实现了一个简单的哈希表，下标对应的是字符的ASCII码，即哈希表的Key；每一位置对应的值是字符出现的次数，即哈希表的值
    unsigned int hashTable[tableSize];
    for(unsigned int i = 0; i < tableSize; ++i)
        hashTable[i] = 0;

    // 第一次遍历，统计每个字符出现的次数
    const char* pHashKey = pString;
    while(*(pHashKey) != '\0')
        hashTable[*(pHashKey++)] ++;

    // 第二次遍历，如果字符出现的次数是1，直接返回
    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;

        pHashKey++;
    }

    return '\0';
}

// ====================测试代码====================
void Test(const char* pString, char expected)
{
    if(FirstNotRepeatingChar(pString) == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
    // 常规输入测试，存在只出现一次的字符
    Test("google", 'l');

    // 常规输入测试，不存在只出现一次的字符
    Test("aabccdbd", '\0');

    // 常规输入测试，所有字符都只出现一次
    Test("abcdefg", 'a');

    // 鲁棒性测试，输入nullptr
    Test(nullptr, '\0');

    return 0;
}

