//
// Created by mext on 2021/2/22.
//
/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/


#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * 创建ListNode
 * @param value
 * @return
 */
ListNode* CreateListNode(int value)
{
    ListNode* pNode = new ListNode();
    pNode->m_nValue = value;
    pNode->m_pNext = nullptr;

    return pNode;
}

/**
 * 将ListNode连成链表
 * @param pCurrent
 * @param pNext
 */
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)
{
    if(pCurrent == nullptr)
    {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->m_pNext = pNext;
}

/**
 * 打印ListNode
 * @param pNode
 */
void PrintListNode(ListNode* pNode)
{
    if(pNode == nullptr)
    {
        printf("The node is nullptr\n");
    }
    else
    {
        printf("The key in node is %d.\n", pNode->m_nValue);
    }
}

/**
 * 从头到尾打印列表的值
 * @param pHead 指向链表头的指针
 */
void PrintList(ListNode* pHead)
{
    printf("PrintList starts.\n");

    ListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        printf("%d\t", pNode->m_nValue);
        pNode = pNode->m_pNext;
    }

    printf("\nPrintList ends.\n");
}

/**
 * 从头到尾删除
 * @param pHead 指向列表头的指针
 */
void DestroyList(ListNode* pHead)
{
    ListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        pHead = pHead->m_pNext;
        delete pNode;
        pNode = pHead;
    }
}

/**
 *
 * @param pHead 指向 指向链表头的指针
 * @param value
 */
void AddToTail(ListNode** pHead, int value)
{
    // 创建一个ListNode
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;

    // 如果传入的是空链表，就把新创建的节点作为第一个
    // 因此*pHead作为一个指针，应该指向新创建的节点
    if(*pHead == nullptr)
    {
        *pHead = pNew;
    }
    else
    {
        // 创建一个指针保存 链表头指针
        ListNode* pNode = *pHead;

        // 不知道链表的长度，一直找到链表的末尾
        while(pNode->m_pNext != nullptr)
            pNode = pNode->m_pNext;

        // *pHead->m_pNext = pNew
        pNode->m_pNext = pNew;
    }
}

/**
 *
 * @param pHead
 * @param value
 */
void RemoveNode(ListNode** pHead, int value)
{
    // 输入检查
    if(pHead == nullptr || *pHead == nullptr)
        return;

    ListNode* pToBeDeleted = nullptr;
    // 如果被删的是第一个节点
    if((*pHead)->m_nValue == value)
    {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    }
    else
    {
        ListNode* pNode = *pHead;
        // 找到指向被删除的那个节点的指针
        while(pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue != value)
            pNode = pNode->m_pNext;

        if(pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue == value)
        {
            pToBeDeleted = pNode->m_pNext;
            // 跳过这个节点，让前一个指向下一个
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }

    // 别忘了delete
    if(pToBeDeleted != nullptr)
    {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}
