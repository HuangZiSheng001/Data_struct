//qck.h
// 快速排序法

// 关键在于对线性表的分割
/* 步骤：
首先在表的第一，中间与最后一个元素中选取中项，  设为P（k）， 并 T = P(k) ， 再将表第一个元素移动到P（k）位置上
*/

#include"bub.h"

template<class T>
void qck( T p[],  int n){
	int m. i;
	T *s;
	
	if( n>10){                     // 子表长度大于10， 用快速排序
		i = split(p, n);            // 对表进行分割
		qck(p,i);                     //  对前面的子表进行快速排序
		s = p + (i+1);      
		m = n- ( i+1);
		qck( s, m)
	}                    
}