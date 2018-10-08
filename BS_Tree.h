//BS_Tree.h

#include<iostream>
using namespace std;


//  定义二叉链表结点类型
template<class T>
struct BSnode{
	T d;
	BSnode * lchild;
	BSnode * rchild;
}