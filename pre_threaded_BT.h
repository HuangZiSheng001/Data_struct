// pre_threaded_BT.h

# include<iostream>
using namespace std;
template TTnode{
	T d;
	int lflag;
	int rflag;
	TTnode * lchild;
	TTnode * rchild;
};

// 前序线索二叉链表类
template<class T>
class pre_threaded_BT{
private:
	TTnode<T> * BT;
public:
	pre_threaded_BT() { BT = NULL; return;}
	void creat_Binary_Tree(T);
	void creat_threaded_BT();
	void intrav_threaded_BT();                       // 遍历前序线索二叉链表类
}

// 生成二叉链表类
template<class T>
void pre_threaded_BT<T>::creat_Binary_Tree(T end){
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
	cin >>x;             // 输入结点值
	if(x!=end){   
		q = new TTnode<T>;        申请一个二叉链表节点
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


// 生成前序线索二叉链表
template<class T>
void pre_threaded_BT<T>::creat_threaded_BT() { 
	TTnode<T> *p, *q =NULL;
	p = BT;
	pre_threaded(p , &q);
	return;
}

template<class T>
static pre_threaded(TTnode<T> *bt, TTnode<T> **h){       // 左右根   **h 为一个索引
	TTnode<T> *p, *q ;
	if(  bt!= NULL ){
		p = bt->lchild; 
		q = bt->rchild;
		//  若上次访问的结点的左指针为空 ， 则将当前访问到的节点序号填入 ，并设置左标志域为1
		if( (*h != NULL) && ( p==NULL )){
			bt->lchild = *h;
			bt->lflag = 1;
		}		

		//  若上次访问的结点的右指针为空 ， 则将当前访问到的节点序号填入 ，并设置右标志域为1
		if( (*h != NULL) && ( (*h)->rchild==NULL )){
			(*h)->rchild = *h;
			(*h)->rflag = 1;
		}		
		
		*h = bt;    // 记住访问到的节点
		pre_threaded(p, h);
		pre_threaded(q, h);
	}
	return 0;
}

// 前序遍历线索二叉链表
template<class T>
void pre_threaded_BT<T>::intrav_threaded_BT(){
	TTnode<T> *p;
	if(  BT == NULL ) return;
	cout<<  BT->d << "    ";              // 输出根节点值
	p = BT->lchild;                        //  沿左子树
	if( p ==NULL )  p = BT->rchild;   // 左子树空则沿右子树
	
	while( p != NULL) {            // 子树不空
		cout<< p->d << "   ";    //  输出当前结点值
		while(p->lflag ==0)  {    // 沿着左链访问直到lflag 为1
			p = p->lchild;
			cout<< p-d<< "   ";     // 输出当前结点值
		}
		p = p->rchild;          // 取右指针	
	}
	cout<<endl;
	return;
}



















