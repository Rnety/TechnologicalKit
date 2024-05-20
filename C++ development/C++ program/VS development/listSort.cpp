#include <bits/stdc++.h>
using namespace std;

// 定义链表结点
struct Node
{
    int data;
    struct Node *next;
};

void sort(Node *head, Node *lastptr)
{
    if (head->next == nullptr)
    {
        return;
    }
    Node *p = nullptr;    // 当前遍历指针的前置结点
    Node *q = nullptr;    // 当前遍历结点
    Node *last = nullptr; // 当前需要遍历的最后一个结点

    while (head->next != last)
    {
        p = head->next; // 初始化
        q = p->next;
        while (q != last && q != nullptr)
        {
            if (p->data < p->next->data)
            {
                swap(p->data, q->data);
            }
            q = q->next;
            p = p->next;
        }
        last = p;
    }
}

int main()
{
    int n;
    Node *head = new Node; // 定义头结点
    head->data = -1;
    head->next = nullptr;
    Node *p = nullptr;
    p = head;
    while (cin >> n) // 逐步输入元素
    {
        Node *node = new Node; // 定义新结点
        node->data = n;
        node->next = nullptr;
        p->next = node;
        p = node;
    }
    sort(head, p);
    p = head;
    while (p)
    {
        cout << p->data << endl;
        p = p->next;
    }
    // 释放内存
    while (p)
    {
        delete p;
        p = p->next;
    }
    return 0;
}
