// pos_threaded_BT.h

//  后序遍历：  左右根
/*
后序穿线二叉树的遍历：
首先从根节点开始，后序遍历找到第一个结点（它也是后序序列的第一个结点）， 设置为h， 按以下原则找到其后件：
	①若当前结点h是二叉树的根节点，则其没有后件，遍历结束
	②若当前结点h是其双亲的右孩子，或是其双亲的左孩子且其双亲没有右孩子， 则其后件即为双亲结点
	③若当前结点h是其双亲的左孩子，且其双亲有右孩子， 则其后件即为双亲的右子树上按后序遍历列出的第一个结点    

*/
// 在后序穿线二叉树中进行遍历时， 需要知道结点的双亲， 要在结点的存储结构中增加一个指向双亲的指针域

# include<iostream>
using namespace std;
template TTTnode{
	T d;
	int lflag;
	int rflag;
	TTTnode * pre;          // 父指针域  ，  三叉链表
	TTTnode * lchild;
	TTTnode * rchild;
};


// 后序线索三叉链表类
template<class T>   
class pos_threaded_BT{
private:
	TTTnode<T> *BT;
public:
	pos_threaded_BT() {BT = NULL; return;}
	void creat_Binary_Tree(T);
	void creat_threaded_BT();
	void intrav_threaded_BT();
}

// 生成三叉链表
template<class T>
void pos_threaded_BT<T>::creat_Binary_Tree( T end){
	TTTnode<T>  *p;
	T x;
	cin>>x;
	if(x==end)  return;
	p = new TTTnode<T>;
	p->d = x;   p->lchild =NULL;  p-> rchild =NULL;
	p->lflag = 0;  p->rflag = 0;  p->pre = NULL;
	
	BT =p;
	creat(p, 1, end);
	creat(p, 2 , end);
	return;
}

template<class T>
static creat( TTTnode<T> *p, int k, T end){
	TTTnode<T> *q;
	T x;
	cin >>x;             // 输入结点值
	if(x!=end){   
		q = new TTTnode<T>;        申请一个二叉链表节点
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

// 生成后序线索三叉链表
template<class T>
void pos_threaded_BT<T>::creat_threaded_BT(){
	TTTnode<T> *p, *q =NULL;
	p = BT;
	pos_threaded(p, &q);
	return;
}
template
static pos_threaded(TTTnode<T> *p, TTTnode<T> **h){
	if( p!= NULL){
		pos_threaded( p->lchild, h);
		pos_threaded(p->rchild, h );
		
		//  若上次访问的结点的右指针为空 ， 则将当前访问到的节点序号填入 ，并设置右标志域为1
		if( (*h != NULL) && ( (*h)->rchild==NULL )){
			(*h)->rchild = p;
			(*h)->rflag = 1;
		}		
		
		//  若上次访问的结点的左指针为空 ， 则将当前访问到的节点序号填入 ，并设置左标志域为1
		if( (*h != NULL) && ( p->lchild==NULL )){
			p->lchild = *h;
			p->lflag = 1;
		}		
		*h = p;
	}
	return 0;
} 


//  遍历后序线索三叉表
template<class T>
void pos_threaded_BT<T>::intrav_threaded_BT(){
	TTTnode<T> *p, *h;
	if(BT == NULL)  return;            // 为空的时候
	h =BT;                           //  头节点?
	while(  (h->lchild != NULL)  || (h->rflag == 0)  && (h->rchild != NULL)){
		if( h->lchild != NULL)   h = h->lchild;
		else h = h->rchild;
	}                                         // 按后序遍历找第一个结点
	cout<< h->d<< "   ";
	while( h->pre != NULL)  {        // 当前结点不是根节点
		if( h->rflag != 0)  h = h->rchild;        // 按标志找到后件
		else{
			p = h->pre;
			if(  (p->rchild == h)  ||  (p->lchild ==h)  && ( ( p->rflag != 0) || (p->rchild == NULL) ) )   h = p;  // 父节点作为后件
			else{
				h = p->rchild;
				
				//  当       h的 lflag为0并且 h的 左指针不为空     或者是   h的rflag 为0  并且 h  的右指针不空      即后继结点不为根节点
				while(  (  (  h->lflag ==0)  &&  (h->lchild != NULL) )  ||  (  ( h->rflag == 0) && h->rchild != NULL）   )  ){
					if(    (   h->lflag == 0) && (   h->lchild) != NULL   ))   h = h->lchild;      // 往左找
					else h = h->rchild;
				}
			}
		}
	}
	cout<<endl;
	return;
}














