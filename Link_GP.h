//Link_GP.h
// 将图邻接表和基本操作（初始化，输出，遍历，最短距离问题等） 等封装成一个类
#include<iostream>
#include<fstream>
#include"sq_Queue.h"         // 需引用   ??队列的头文件
using namespace std;

//  两个域  path    clink


// 定义图邻接表中单链表结点类型
template<class T1>
struct node{ 
	int num;        //图中结点编号
	T1 val;				// 求值函数
	node *next;   // 指向链表中下一个结点的指针域
};


//  定义图邻接表中顺序存储空间节点类型
template<class T1, class T2>
struct gpnode{
	T2 data;                      // 图中结点值
	node<T1> *link;      // 指向各单链表第一个结点的指针域
};

// 定义图邻接类
template<class T1, class T2>
class Link_GP{
private:
	int nn;
	gpnode<T1, T2> *gp;                //图邻接表中顺序存储空间首地址
public:
	Link_GP() { gp= NULL; return;}
	void creat_Link_GP(int , T2 [])    // 由键盘输入生成图邻接表
	void creat_Link_GP(int, T2[], char * );     // 由文件数据生成图邻接表
	void out_Link_GP();                     // 输出图邻接表
	void dfs_Link_GP() ;            //  纵向优先搜索法遍历图
	void bfs_Link_GP();            //  横向优先搜索法
	void short_Link_GP(int);              //  求指定结点到其余各到结点的最短距离
	void short_path_Link_GP(int);     //  求指定结点到其余各结点的最短距离与路径
}

template<class T1, class T2>
void Link_GP<T1, T2>:: creat_Link_GP(  int n, T2 d[]){
	node<T>  *p;
	int k,m;
	T1 v;
	nn = n;
	gp = new gpnode<T1, T2> [nn];        //    申请图邻接表中顺序存储空间
	for(  k=0; k<n;  k++)     {                   // 依次对图中每一个结点建立链接所有的
		(gp+k)->data = d[k];
		(gp+k)->link = NULL;
		cout<< "输入图中第"<<  k + 1<< " 个结点的后件信息:  " >> endl;
		cin >> m >> v;                                  //  输入后件信息
		while( m >= 0){                                //  输入后件信息未结束
			p = new node<T1>;                             // 申请单链表结点
			p->num =m;     p->val =v;             //  设置 后件结点编号 与 求值函数值
			
			p->next = (gp+k)->link;             //  新节点指针指向原头结点
			(gp+k)->link = p;                    //  将新节点链接到单链表链头
			cin >> m >> v;                                 // 继续输入后件信息
		}
	}
	return;
}


//  由文件生成图邻接表的成员函数
void Link_GP<T1, T2>:: creat_Link_GP(   int n, T2 d[ ], char * filename ){
	node<T1>  *p;
	int k, m;
	T1 v;
	ifstream infile(filename,  ios::in);     // 打开文件
	nn = n;
	gp = new gpnode<T1, T2>[nn]  ;         // 申请图邻接表中顺序存储空间
	for(  k=0; k<n;  k++)     {                   // 依次对图中每一个结点建立链接所有的
		(gp+k)->data = d[k];
		(gp+k)->link = NULL;
		cout<< "输入图中第"<<  k + 1<< " 个结点的后件信息:  " >> endl;
		infile >> m >> v;                                  //  输入后件信息
		while( m >= 0){                                //  输入后件信息未结束
			p = new node<T1>;                             // 申请单链表结点
			p->num =m;     p->val =v;             //  设置 后件结点编号 与 求值函数值
			
			p->next = (gp+k)->link;             //  新节点指针指向原头结点
			(gp+k)->link = p;                    //  将新节点链接到单链表链头
			infile >> m >> v;                                 // 继续输入后件信息
		}
	}
	return;
}


// 输出图邻接表
template<class T1, class T2>
void Link_GP<T1,T2>:: out_Link_GP(){
	node<T1> *q;
	int k;
	for( k = 0; k<nn;  k++){
		cout << (gp+k)->data;        //输出图结点值
		q = (gp+k)->link;
		while( q != NULL){
			cout<< "----->";
			cout<< q->num << "," << q->val;
			q = q->next;
		}
		cout<<endl;
	}
	return;
}


/*深度优先遍历（Depth First Search）：也称为深度优先搜索，DFS，深度优先搜索其实是一个递归过程，
一条路先走到底有，点像二叉树的先序遍历。我们需要一个数组 visited 来标记已经访问过的顶点 ，
visited[ i ] = false 表示未访问，true 表示已经访问过。
设x是当前被访问顶点，在对x做过访问标记后，选择一条从x出发的未检测过的边(x，y)。
若发现顶点y已访问过，则重新选择另一条从x出发的未检测过的边，否则沿边(x，y)到达未曾访问过的y，对y访问并将其标记为已访问过；
然后从y开始搜索，直到搜索完从y出发的所有路径，即访问完所有从y出发可达的顶点之后，才回溯到顶点x，并且再选择一条从x出发的未检测过的边。
上述过程直至从x出发的所有边都已检测过为止。此时，若x不是源点，则回溯到在x之前被访问过的顶点；
否则图中所有和源点有路径相通的顶点(即从源点可达的所有顶点)都已被访问过，
若图G是连通图，则遍历过程结束，否则继续选择一个尚未被访问的顶点作为新的顶点，继续遍历。*/

//  纵向优先搜索法遍历图
template<class T1, T2>
void Link_GP<T1, T2>::dfs_Link_GP(){
	int k, *mark;
	mark = new int[nn];
	for(  k =0; k< nn; k++)  mark[k] = 0;
	for(  k =0; k< nn; k++)   if(mark[k] == 0)  dfs(gp, k,  mark);       // 对每个图结点纵向优先搜索
	cout<<endl;
	delete[]  mark;
	return;
}

template<class T1, class T2>
static dfs( gpnode)<T1, T2> *q, int k, int *mark){
	node<T1>  *p;
	cout<< (q+k)->data<<"   ";            // 输出当前图结点值
	mark[k] = 1;                                   //  记录当前结点已查访标志
	p =( q+ k )->link  ;                             // 当前结点的第一个后件结点
	while(  p != NULL){
		if(   mark[p->num - 1] == 0)  dfs(q, p->num -1, mark);  // 该后件结点没访问过
		p = p->next;                  // 下一个后件结点
	}
	return 0;
}



/*
广（宽）度优先遍历（Breadth First Search）：又称为广度优先搜索，简称BFS 。
遍历的过程是先从顶点 V0 出发，遍历与 V0 直接连接而又未访问过的顶点V1 、V2 、V3 等，再访问 与 V1直接连接且未访问过的顶点。
同样用一个数组来标记一个顶点是否已经访问过，用一个队列来存储待访问的顶点。
*/
// 横向优先搜索法遍历图
template<class T1, class T2>
void Link_GP<T1, T2>::bfs_Link_GP() {
	int *mark, k;
	sq_Queue<int> q(nn);
	node<T1>  *p;
	mark = new int[nn];                               //  申请标志数组空间
	for(  k=0; k < nn; k++)  mark[k] = 0;     // 标志数组初始化
	for( k = 0; k < nn; k++) {                      //  对每个图结点横向优先搜索
		if(mark[k] == 0 ) {                               // 当前结点没查访过
			mark[k] = 1;                                   // 记录当前结点已查访标志
			cout<<  gp->data   <<"    ";              // 输出当前结点值
			q.in_sq_Queue(k);                                    // 当前结点编号入队
			while( q,flag_sq_Queue() ){                     // 队列不空
				k = q.del_sq_Queue() ;                         // 从队列中退出一个结点作为当前结点
				p = (gp+k)->link;                              // 所有后件结点链表指针
				while( p != NULL){                            // 还有后件时
					k = p->num-1;                
					if ( mark[k] == 0){                                // 该结点没被查访过
						cout << (gp+k) ->data << "    ";            // 输出该结点值
						mark[k] = 1;                                          // 记录该结点 已查访标志
						q.in_sq_Queue(k);                                      //   该结点编号入队列
					}
					p = p->next;                                            // 下一个后件
				}
			}
		}
	}
	cout << endl;
	delete[] mark;
	return;
}

//  求指定结点到其余各到结点的最短距离
template<class T1, class T2>
void Link_GP<T1, T2>::short_Link_GP(int m)     {
	int *mark,    k  ,  j  , h ;
	T1 *e;
	node<T1>  *p;
	sq_Queue<int>q(nn);                                       // 建立循环队列并初始化
	e = new T1{nn];                                                 // 申请距离数组空间
	mark = new int[nn];											  // 申请标志数组空间
	for(  k=0; k < nn; k++)   mark[k] = 0;             // 标志数组初始化
	
	for(  k=0; k < nn; k++)  e[k] = 1;                  //  距离数组初始化
	
	q.in_sq_Queue(m);                                //  起始节点入队
	mark[m-1] = 1;                                             // 设置起始结点入队标志
	e[ m-1] = 0;                                                         //  到起始节点的距离为0
	
	while(  q.flag_sq_Queue() ) {                          //  当队列非空
		k = q.del_sq_Queue();                             // 从队列中取出一个结点 编号k
		p = (gp+ k -1)->link;                                    //  结点后件的单链表头指针
		while  (  p != NULL)  {                                //  还有后件   
			j = p->num; 											// 该后件结点编号
			h = e[ k-1]  + p->val ;                                      // 计算该后件结点 到起始结点的距离 
			
			if(     (e[j-1] == -1)  || (e[j-1] > h) ){                  //  如果距离更小
				e[ j -1 ] = h;                                                     //  记录该更小的距离
				if(          mark[j-1] == 0  ) {                         //  如果该后件结点没有入过队， 则入队
					mark[ j-1 ] = 1;                                        //  设置其入队标志
					q.in_sq_Queue(j)                                         //  入队
				} 
			}
			p = p->next;                                           // 单链表中下一个后件结点
		}                                                                     // 
	}
	cout << "K    " << "      PATH" << endl;
	
	for(  k=0; k <nn; k+)  cout  << k+1  << "    " << e[k]  << endl;	// 输出指定结点到其余各个结点的最短距离
	delete [] mark;
	delete [] e;
	return;	
}


// 求指定结点到其余各结点的最短距离和路径

// 定义最短距离与路径顺序存储空间结点类型
template< class T1>
struct pathnode{
	T1 path;                                              // path 用来存放指定结点到各结点的最短距离 
	node<T1>   *elink;                         //  elink 用来链接最短路径上各结点的信息        
}

template<class T1, class T2>
void Link_GP<T1, T2>::short_path_Link_GP(int m)   {
	int *mark, k , j ,h;       
	pathnode<T1>  *e;                                                         
	node<T1>  *p, *pp;                                        
	
	sq_Queue<int> q(nn);                           // 建立循环队列并初始化
	e = new pathnode<T1>[nn];            //  申请最短距离与路径顺序存储空间
	mark = new int[nn];                              // 申请标志数组空间
	for(  k = 0 ;  k< nn; k++)      mark[k] = 0;                  // 标志数组初始化
	
	for(  k = 0 ;  k< nn; k++) {
		(e+k)->path = -1;
		(e+k)->link = NULL;
	}
	(e + m - 1)->path = 0;
	q.in_sq_Queue(m);
	mark[m-1] = 1;
	while(  q.flag_sq_Queue()  )  {                // 当队列非空
		k = q.del_sq_Queue();                    // 从队列中取出一个结点
		p = (gp +k-1)->link;                  // 该结点后件单链表头指针
		
		while(  p != NULL)    {                     //  还有后件结点
			j = p->num;                             // 当前后件结点编号
			h =  (   ( e + k -1)->path  )    +   p->val    ;               // 当前后件结点到起始节点新距离
			if(  (    ( e+j -1)->path == -1 )      ||   ( e+j -1)->path > h )    ) {                // 若距离更小 
				( e+j -1)->path = h;                                                  //  设置更小的距离
				pp = ( e+j -1)->elink;                                               // 最短距离的最后一个路径
				if(   pp  == NULL)   pp =new node<T1>;                    // 路径为空则申请一个最短距离路径结点
				pp->num = j ;             pp->val = p->val;                              // 设置新路径
				pp->next = ( e + k -1)->elink;    (e + j -1)->elink = pp ;                    // 连接新路径
				
				if(   mark[j-1] == 0)  {                                      //  若当前结点没入队过
					mark[ j-1] = 1;                                       // 设置当前后件结点入队标志
					q.in_sq_Queue(j);                                        //  当前后件结点入队
				} 
			}
			
		p = p->next;         // 遍历 + 访问
		}
	}
	
	cout << "K /t" << "PATH \t"<< "ELINK \t" << endl;
	for( k =0; k< nn; k++){                                                         // 依次输出各结点到起始结点的最短距离与路径
		cout << k+1 << "\t" << (e+k)->path << "\t";             // 输出结点编号和最短距离
		p = (e+k)->elink;
		
		while ( p != NULL)  {
			cout<< "--->";  cout << p->num<< "," << p->val;              // 输出路径
			p = p->next;
		}
		cout << endl;
	}
	delete[] mark;  delete[] e;
	return;
}




//  实例：
#include"Link_GP.h"
int main(){
	char d[8] = { 'A', 'B',  'C', 'D', 'E', 'F', 'G', 'H'};
	Link_GP<int, char> g;
	g.creat_Link_GP(8, d,  "f1.txt")     ;          // 由数据文件生成图g邻接表
	
	cout << "输出图g邻接表:"<<endl;
	
	g.out_Link_GP();                                  
	
	cout<< "纵向优先搜索法遍历图g:"<<endl;
	g.dfs_Link_GP();
	
	
	cout<< "横向优先搜索法遍历图g:"<<endl;
	g.bfs_Link_GP();
	
	
	cout<< "第三个结点到其余各结点的最短距离: \n"<< endl;
	
	g.short_Link_GP(3);
	
	cout<< "第三个结点到其余各结点的最短距离和路径: \n"<< endl;
	
	g.short_path_Link_GP(3);
	return 0;
}





















