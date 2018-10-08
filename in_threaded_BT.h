// in_threaded_BT.h      中序穿线二叉树   只有中序遍历

/*要在二叉链表中生成中序遍历顺序的线索，只需在中序遍历过程中将访问根结点用下列操作代替：
　　　（1）若上次访问到的结点的右指针为空，则将当前访问到的结点序号填入，并置右标志为1。
　　　（2）若当前访问到的结点的左指针为空，则将上次访问到的结点序号填入，并置左标志为1。*/

#include<iostream>
using namespace std;

template<class T>
struct TTnode{
	T d;
	int lflag;
	int rflag;
	TTnode * lchild;
	TTnode * rchild;
};

template<class T>
class in_threaded_BT{
private:
	TTnode<T> *BT;
public:
	in_threaded_BT() { BT = NULL; return; }
	void creat_Binary_Tree(T);
	void creat_threaded_BT();
	void intrav_threaded_BT();
};

template<class T>
void in_threaded_BT<T>::creat_Binary_Tree(T end){
	TTnode<T> *p;
	T x;
	cin>>x;
	if(x == end)  return;
	
	p = new TTnode<T>;
	p->d = x;
	p->lchild = NULL;
	p->rchild = NULL;
	BT = p;
	creat(p, 1 ,end);
	creat(p, 2, end);
	return ;
}

template<class T>
static creat( TTnode<T> *p, int k, T end){
	TTnode<T> *q;
	T x;
	cin >>x;
	if(x!=end){
		q = new TTnode<T>;
		q->d =x;
		q-> lchild = NULL;
		q-> rchild = NULL;
		q->lflag = 0;
		q->rflag = 0;
		if(k==1) p->lchild =q;
		if(k ==2) p->rchild =q;
		creat(q, 1, end);
		creat(q, 2, end);
	}
	return 0;
}


// 
template<class T>
void in_threaded_BT<T>::creat_Binary_Tree(){
	TTnode<T> *p, *q =NULL;
	p = BT;
	in_threaded(p , &q);
	return;
}

template<class T>
static in_threaded(TTnode<T> *p, TTnode<T> **h){
	if(p!= NULL){
		in_threaded(p->lchild, h);    
		//  若上次访问的结点的右指针为空 ， 则将当前访问到的节点序号填入 ，并设置右标志域为1
		if( (*h != NULL) && ( (*h)->rchild==NULL )){
			(*h)->rchild = p;
			(*h)->rflag = 1;
		}		
		
		//  若上次访问的结点的左指针为空 ， 则将当前访问到的节点序号填入 ，并设置左标志域为1
		if( (*h != NULL) && ( (*h)->lchild==NULL )){
			(*h)->lchild = p;
			(*h)->lflag = 1;
		}		
		
		*h = p;    // 记住访问到的节点
		in_threaded(p->rchild, h);
	}
	return 0;
}

// 遍历中序线索二叉树链表
template<class T>
void in_threaded_BT<T>::intrav_threaded_BT() {
	TTnode<T> *p;
	
	if(BT == NULL)  return;         // 二叉链表为空
	p = BT;
	
	while( p->lflag == 0) p = p->lchild;   // 沿着左链找到叶子节点
	
	cout << p->d << "  ";                    // 输出中序序列中的第一个节点值
	
	while( p->rchild!= NULL )  {                 // 沿着右链扫描后件
		if( p-> rflag == 1)  p = p->rchild;
		else{                                                      //  沿着右子树的左链扫描
			p = p->rchild;
			while( (p->lflag==0) && (p->lchild != NULL))  p = p->lchild;
		}
		cout << p->d<< "   ";          // 输出中序序列中的结点值
	}
	cout<<endl;
	return;
}

















