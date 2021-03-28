//
// Created by lab on 2021/3/28.
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

// 面试题48：最长不含重复字符的子字符串
// 题目：请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子
// 字符串的长度。假设字符串中只包含从'a'到'z'的字符。

#include <string>
#include <iostream>

// 方法一：蛮力法
bool hasDuplication(const std::string& str, int position[]);



int longestSubstringWithoutDuplication_1(const std::string& str)
{
    int longest = 0;
    // 用于记录每个字母是否重复
    int* position = new int[26];
    for(int start = 0; start < str.length(); ++start)
    {
        for(int end = start; end < str.length(); ++end)
        {
            int count = end - start + 1;  // count记录了当前子数组的长度
            const std::string& substring = str.substr(start, count);
            if(!hasDuplication(substring, position))
            {
                if(count > longest)
                    longest = count;
            }
            // 如果到当前位置已经有重复字母了，那么再往后继续也没有意义了，因此直接break
            else
                break;

        }
    }

    delete[] position;
    return longest;
}

bool hasDuplication(const std::string& str, int position[])
{
    for(int i = 0; i < 26; ++i)
        position[i] = -1;

    for(int i = 0; i < str.length(); ++i)
    {
        int indexInPosition = str[i] - 'a';
        if(position[indexInPosition] >= 0)
            return true;

        position[indexInPosition] = indexInPosition;
    }

    return false;
}

// 方法2：动态规划
int longestSubstringWithoutDuplication_2(const std::string& str)
{
    int curLength = 0;
    int maxLength = 0;

    // 用于记录每个字母是否重复
    int* position = new int[26];
    for(int i = 0; i < 26; ++i)
        position[i] = -1;

    for(int i = 0; i < str.length(); ++i)
    {
        // 当前字母对应position中的值，如果这个字母没有出现过，那么prevIndex=-1
        // 如果曾经出现过，那么prevIndex为这个字母上次出现在str中的索引
        int prevIndex = position[str[i] - 'a'];
        // prevIndex < 0 表示当前字母没有出现过
        // i - prevIndex > curLength 表示这个字母以前出现过，但是距离上次出现位置的距离大于当前子数组的长度，
        // 表示重复字母在当前子数组之外，不影响
        if(prevIndex < 0 || i - prevIndex > curLength)
            ++curLength;
        // 进入else表示遇到了曾经出现过的字母 且 距离上一次出现位置的距离<=当前子数组的长度
        // 这样就表示这个重复字母在当前子数组之内，子数组长度要记录一下，不能再增加了
        else
        {
            if(curLength > maxLength)
                maxLength = curLength;
            // 出现重复字母了，子数组长度要记录一下
            curLength = i - prevIndex;
        }
        // 把当前字母在position中对应的位置赋值为i,表示这个字母出现过，以及在str中哪个位置
        position[str[i] - 'a'] = i;
    }

    if(curLength > maxLength)
        maxLength = curLength;

    delete[] position;
    return maxLength;
}

// ====================测试代码====================
void testSolution1(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_1(input);
    if(output == expected)
        std::cout << "Solution 1 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

void testSolution2(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_2(input);
    if(output == expected)
        std::cout << "Solution 2 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

void test(const std::string& input, int expected)
{
    testSolution1(input, expected);
    testSolution2(input, expected);
}

void test1()
{
    const std::string input = "abcacfrar";
    int expected = 4;
    test(input, expected);
}

void test2()
{
    const std::string input = "acfrarabc";
    int expected = 4;
    test(input, expected);
}

void test3()
{
    const std::string input = "arabcacfr";
    int expected = 4;
    test(input, expected);
}

void test4()
{
    const std::string input = "aaaa";
    int expected = 1;
    test(input, expected);
}

void test5()
{
    const std::string input = "abcdefg";
    int expected = 7;
    test(input, expected);
}

void test6()
{
    const std::string input = "aaabbbccc";
    int expected = 2;
    test(input, expected);
}

void test7()
{
    const std::string input = "abcdcba";
    int expected = 4;
    test(input, expected);
}

void test8()
{
    const std::string input = "abcdaef";
    int expected = 6;
    test(input, expected);
}

void test9()
{
    const std::string input = "a";
    int expected = 1;
    test(input, expected);
}

void test10()
{
    const std::string input = "";
    int expected = 0;
    test(input, expected);
}

int main(int argc, char* argv[])
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
