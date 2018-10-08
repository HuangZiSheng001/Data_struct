//Binary_Tree.h
#include<iostream>
using namespace std;

template<class T>
struct Btnode{
	T d;
	Btnode * lchild;
	Btnode * rchild;
};

template<class T>
class Binary_Tree{
private:
	Btnode<T> *BT;
public:
	Binary_Tree() { BT = NULL; return; }
	void create_Binary_Tree(T);
	void pretrav_Binary_Tree();
	void intrav_Binary_Tree();
	void postrav_Binary_Tree();
};

template<class T>
void Binary_Tree<T>::create_Binary_Tree(T end){
	Btnode<T> *p;
	T x;
	cin>>x;
	if(x == end)  return;
	p = new Btnode<T>;
	p->d = x;
	p->lchild = NULL;
	p->rchild = NULL;
	BT = p;
	creat(p, 1 ,end);
	creat(p, 2, end);
	return ;
}

template<class T>
static creat( Btnode<T> *p, int k, T end){
	Btnode<T> *q;
	T x;
	cin >>x;
	if(x!=end){
		q = new Btnode<T>;
		q->d =x;
		q-> lchild = NULL;
		q-> rchild = NULL;
		if(k==1) p->lchild =q;
		if(l ==2) p->rchild =q;
		creat(q, 1, end);
		creat(q, 2, end);
	}
	return 0;
}

// 前序遍历二叉链表
template<class T>
void Binary_Tree<T>::pretrav_Binary_Tree() {
	Btnode<T> *p;
	p = BT;
	pretrav(p);
	cout<< endl;
	return;
}

template<class T>
static pretrav(Btnode<T> *p){
	if( p != NULL){
		cout<< p>d << "    ";
		pretrav(p->lchild) ;    // 
		pretrav(p->rchild);   //
	}
	return 0;
}


//
template<class T>
void Binary_Tree<T>::intrav_Binary_Tree() {
	Btnode<T> *p;
	p = BT;
	intrav(p);
	cout<<endl;
	return;
}

template<class T>
static intrav(Btnode<T> *p){
	if(p != NULL){
		intrav(p->lchild);
		cout<<p->d<<"   ";
		intrav(p->rchild);
		}
	return 0;
}


// hou xu 
template<class T>
void Binary_Tree<T>::postrav_Binary_Tree() {
	Btnode<T> *p;
	p = BT;
	postrav(p);
	cout<<endl;
	return;
}

template<class T>
static postrav(Btnode<T> *p){
	if( p != NULL){
		postrav(p->lchild);    //
		postrav(p->rchild);     //
		cout<< p->d <<"   ";   // 
	}
	return 0;
}













