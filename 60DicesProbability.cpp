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

// 面试题60：n个骰子的点数
// 题目：把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s
// 的所有可能的值出现的概率。

#include <cstdio>
#include <cmath>

int g_maxValue = 6;

// ====================方法一====================
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

// 用一个数组保留所有的和的可能结果，然后逐个骰子处理
// 同时对于每一个骰子的6个可能结果进行循环遍历
void PrintProbability_Solution1(int number)
{
    if(number < 1)
        return;

    // n个骰子的最大值是6n，最小值是n
    int maxSum = number * g_maxValue;
    int* pProbabilities = new int[maxSum - number + 1];
    // 概率初始化为0
    for(int i = number; i <= maxSum; ++i)
        pProbabilities[i - number] = 0;

    Probability(number, pProbabilities);

    int total = pow((double)g_maxValue, number);
    for(int i = number; i <= maxSum; ++i)
    {
        double ratio = (double)pProbabilities[i - number] / total;
        printf("%d: %e\n", i, ratio);
    }

    delete[] pProbabilities;
}

/**
 *
 * @param number 骰子数量
 * @param pProbabilities 存放每次投掷结果和的数组
 */
void Probability(int number, int* pProbabilities)
{
    for(int i = 1; i <= g_maxValue; ++i)
        Probability(number, number, i, pProbabilities);
}

/**
 *
 * @param original 最初的骰子数量
 * @param current 当前计算的骰子数量，每次递归会减一个
 * @param sum 当前的目标sum
 * @param pProbabilities
 */
void Probability(int original, int current, int sum,
                 int* pProbabilities)
{
    if(current == 1)
    {
        pProbabilities[sum - original]++;
    }
    else
    {
        for(int i = 1; i <= g_maxValue; ++i)
        {
            // 骰子数量-1
            // sum需要在原来的sum上增加
            Probability(original, current - 1, i + sum, pProbabilities);
        }
    }
}

// ====================方法二====================
void PrintProbability_Solution2(int number)
{
    if(number < 1)
        return;

    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];
    // 初始赋值
    for(int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }

    int flag = 0;
    // 对于第一个骰子，六种可能，每个可能性+1
    for (int i = 1; i <= g_maxValue; ++i)
        pProbabilities[flag][i] = 1;

    // 开始投第二个骰子
    for (int k = 2; k <= number; ++k)
    {
        // 出现了k个骰子，和<k的情况不可能发生了
        for(int i = 0; i < k; ++i)
            pProbabilities[1 - flag][i] = 0;

        for (int i = k; i <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;
            for(int j = 1; j <= i && j <= g_maxValue; ++j)
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
        }
        flag = 1 - flag;
    }

    double total = pow((double)g_maxValue, number);
    for(int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = (double)pProbabilities[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }

    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);

    printf("Test for solution1\n");
    PrintProbability_Solution1(n);

    printf("Test for solution2\n");
    PrintProbability_Solution2(n);

    printf("\n");
}

int main(int argc, char* argv[])
{
    Test(1);
    Test(2);
    Test(3);
    Test(4);

    Test(11);

    Test(0);

    return 0;
}

