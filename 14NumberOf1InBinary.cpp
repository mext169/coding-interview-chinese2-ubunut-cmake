//
// Created by mext on 2021/2/27.
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

// 面试题15：二进制中1的个数
// 题目：请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。例如
// 把9表示成二进制是1001，有2位是1。因此如果输入9，该函数输出2。

#include <cstdio>

/**
 * 输入负数会死循环
 * @param n
 * @return
 */
int NumberOf1_MayDeadLoop(int n)
{
    int count = 0;
    while (n)
    {
        if (n & 1)
            count ++;
        // 对于负数，移位后仍要保持是一个负数，因此移位后的最高位会被设为1，如果一直做右移运算，那么最终数字会变成0xFFFFFFFF而陷入死循环
        n = n >> 1;
    }
    return count;
}


int NumberOf1_Solution1(int n)
{
    int count = 0;
    unsigned int flag = 1;
    while (flag)
    {
        // 首先将n和1做与运算，判断n的最低位是不是1
        // 接着把n左移一位得到2，然后再做与运算，这样反复左移下去
        // 循环的次数等于整数二进制的位数
        if (n & flag)
            count++;

        flag = flag << 1;
    }

    return count;
}

/**
 * 把一个整数减去1，再和原整数做与运算，会把该整数最右边的1变成0，那么二进制表示中有多少个1，就需要进行多少次计算
 * @param n
 * @return
 */
int NumberOf1_Solution2(int n)
{
    int count = 0;

    while (n)
    {
        ++count;
        // 把一个整数减去1之后再和原来的整数做位与运算，得到的结果相当于把整数的二进制表示中最右边的1变成0
        n = (n - 1) & n;
    }

    return count;
}

// ====================测试代码====================
void Test(int number, unsigned int expected)
{
    int actual = NumberOf1_Solution1(number);
    if (actual == expected)
        printf("Solution1: Test for %p passed.\n", number);
    else
        printf("Solution1: Test for %p failed.\n", number);

    actual = NumberOf1_Solution2(number);
    if (actual == expected)
        printf("Solution2: Test for %p passed.\n", number);
    else
        printf("Solution2: Test for %p failed.\n", number);

    printf("\n");
}

int main(int argc, char* argv[])
{
    // 输入0，期待的输出是0
    Test(0, 0);

    // 输入1，期待的输出是1
    Test(1, 1);

    // 输入10，期待的输出是2
    Test(10, 2);

    // 输入0x7FFFFFFF，期待的输出是31
    Test(0x7FFFFFFF, 31);

    // 输入0xFFFFFFFF（负数），期待的输出是32
    Test(0xFFFFFFFF, 32);

    // 输入0x80000000（负数），期待的输出是1
    Test(0x80000000, 1);

    // 下面输入负数会引起死循环
    printf("my dead loop...");
    int count = NumberOf1_MayDeadLoop(10);
    printf("count: %d", count);


    return 0;
}


