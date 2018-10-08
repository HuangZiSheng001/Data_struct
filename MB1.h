// MB1.h   
//     B- 树类
#define M 2
#include<iostream>
using namespace std;

template<class T>
struct mb1node{
	int num;                                                  // 记录结点中的关键字个数
	mb1node * prt;                                       // 指向父结点的指针
	T key[ 2* M];										    // 2m 个 关键字域
	mb1node * link[ 2*M + 1] ;                     // 2m+1个指向各子树的指针
}

// 定义B-树类
template<class T>
class MB1{
private:
	mb1node<T> * BTH;                                      		 //  B-树 根节点指针
public:
	MB1()   {  BTH = NULL;  return;   }                  		// B-树初始化
	mb1node<T> * MB1_search(  T, int * , int * );          // B-树 的查找
	void MB1_insert(T);														// B-树的插入
	void MB1_delete(T);												// B-树的 删除
	void MB1_prt();                                                  // 按大小输出B-树
}；


// 查找：  从根节点BTH开始，将关键字x与结点q中 各关键字  KEY（i） 进行比较：
// 若 x = key(i);   查找成功，结束
//  若x < key(i);  则沿着指针LINK（1）向下搜索
// 若 x > key(i);  则沿着指针LINK（n+1）向下搜索
// 若 key(i) < x <key(i+1)   ,  则沿着指针LINK（i+1） 向下搜索

// 在B-树中查找元素x所在结点的存储位置以及该结点中的关键字序号k
// 函数返回节结点存储空间首地址， flag= 0 表示查找失败

template<class T>
mb1node<T> * MB1<T>:: MB1_search( T x,  int *k, int * flag){
	mb1node<T> *p, *q;
	p = BTH;         *flag = 0;             q = p;         // 初始化
	
	while(  ( p  != NULL) && (  *flag == 0) ) {
		*k = 1;  q =  p;
		while( (*k < q->num)  && ( q->key[*k -1 ]  < x  ) )  *k += 1;        // 与各个关键字比较
	
		if(   q->key[*k - 1]  == x )   *flag = 1;                       // 查找成功
		
		else if (( *k ==  q->num )  && ( q->key[*k - 1] < x ) )  p = q->linl[*k];  // 向下搜索
		
		else {   p = q->link[*k-1];    *k  -= 1; }
	}
	return (q);           // 返回被查元素x应在的结点的首位置
}



// B- 树的插入
template<class T>
mb1node<T>::MB1_insert( T x){
	int flag, j,k ,t;
	T y;
	mb1node<T> *p, *q, *u, *s;
	if(BTH == NULL){                // B-树为空
		p = new mb1node<T>;			// 申请一个节点
		p->num = 1;					// 设置该节点中只有一根关键字
		p->key[0] = x;				// 设置关键字
		p->prt = NULL;				// 设置所有指针为空

		for( j = 1; j <= 2*M + 1 ; j++)  p->link[ j -1] =NULL;   // 设置所有指针为空

		BTH = p;               // B-树根节点指针
		return;       
	}
	q = (mb1node<T> *)MB1_search( x, &k, &flag);   // 寻找插入位置

	if (flag == ) {    cout<<"ERR! The data had existed !\n;"  return; }

	p = NULL;
	
	t = 0;

	while(t == 0){
		if( k == (q->num)) {          // 插入到节点q的最后
			y = x;
			u = p;
		}

		else{
			y = q->key[ q->num - 1];
			u = q->link[ q->num ];

			for( j = (q->num)-1 ;  j >= k+1; j--){
				q->key[j] = q->key[ j-1 ];
				q->link[j+1] = q->link[j];          // 向下指针均往后移一个位置
			}

			q->key[k] = x;
			q->link[ k+1] = p;

			if( p != NULL)  p->prt = q;       // 改变节点p中指向父节点的指针
		}

		if( q->num < 2*M){
			q->num = (q->num) + 1;             // 结点q中的关键字个数增加1
			q->key[ (q->num) - 1] = y;         // 将记录的关键字插入到q的最后
			q->link[ q->num ] = u;            // 将记录的向下指针插入到q的最后

			if( u != NULL)  u->prt = q;        // 改变结点u中指向父结点的指针
			t = 1; 								// 设置插入完成标志
		}
		else{
			 p = new mb1node<T>;
			 p->num = M;
			 q->num = M;
			 p->prt = q->prt;
			 x = q->key[M];

			 for( j = 1; j <= M-1; j++){
				 p->key[j-1] = q->key[M+j];
				 p->link[j-1] = q->link

			 }
		}
	}


}




// 数据的逻辑运算定义在逻辑结构， 而运算是在存储结构中













