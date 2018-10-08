#include<iostream>
#include<cmath>
using namespace std;

#define MaxElement 100

class Element{  //“元素”类
public:
	int n;
	Element(int i=0):n(i){}
};

class MySet{						//“集合”类
	Element *element;				//指向存储元素的数组的指针
	int size;                       //数组大小
	int counter;					//数组中元素的个数
	int current;                    //用于表示扫描位置，及当前被扫描元素在数组中的下标
public:
	MySet():element(new Element[100]), size(100), counter(0), current(0){}
	~MySet(){ delete[]element; }
	void add(Element ele);			//向集合中添加一个元素，保持由小到大的顺序。
	void remove(Element ele);		//删除集合中指定的元素
	void scanFirst(){ current=0; }	//将扫描位置定位于首元素
	//**********found**********
	void scanNext(){ current++; }	//将扫描位置定位于下一个元素
	Element get()const{ return element[current]; }		//返回当前被扫描的元素
	bool isEnded()const{ return current >= counter; }	//如果已经没有更多的元素可扫描了，返回true。
	void show();										//显示集合中所有元素
};

void MySet::add(Element ele){
	int pos=counter;							//pos用于确定元素应插入的位置
	while(pos>0){								//从后往前寻找该位置
		if(ele.n > element[pos-1].n) break;		//找到应插入的位置，退出循环
		//**********found**********
		if(ele.n == element[pos-1].n) return;	//发现相同元素，终止添加过程。
		pos--;
	}
	if(counter>=size){					//如果没有足够空间，扩充空间（增加100个元素的容量）
		Element *tmp=element;			//tmp指向原来的数组
        //**********found**********
		element=new  Element[size+100];	 //申请一个新的数组，容量扩大100个元素的容量
		for(int i=0; i<size; i++) element[i]=tmp[i];
		size+=100;
		delete []tmp;
	}
	for(int i=counter; i>pos; i--) element[i]=element[i-1];	//后移相关元素，腾出存放新元素的空间
	element[pos]=ele;										//插入新元素
	counter++;
}

void MySet::show(){
	scanFirst();			//扫描位置定位于首元素
	while(!isEnded()){
		cout<<get().n<<"  ";
        //**********found**********
		scanNext();			//扫描定位于下一个元素
    }
	cout<<endl;
}

void MySet::remove(Element ele){
	int pos=counter-1;						//pos用于确定要删除的元素的位置
	while(pos>=0){							//从后往前寻找该位置
		if(ele.n > element[pos].n) return;	//集合中没有该元素，终止删除过程。
		if(ele.n == element[pos].n) break;	//找到删除的元素，退出循环。
		pos--;
	}
	if(pos<0) return;						//集合中没有该元素，终止删除过程。
	for(int i=pos; i<counter-1; i++) element[i]=element[i+1];	//删除该元素，后面的元素顺序前移。
	counter--;
	if(counter+100<=size){				//如果未使用的存储单元超过100，缩减存储空间，减少100个单元
		Element *tmp=element;
		element=new Element[size-100];
		for(int i=0; i<size; i++) element[i]=tmp[i];
		size-=100;
		delete []tmp;
	}
}

int main(){
    MySet set;
	set.add(Element(3));
	set.add(Element(8));
	set.add(Element(5));
	set.add(Element(0));
	set.show();
	set.remove(Element(5));
	set.remove(Element(4));
	set.add(Element(8));
	set.show();

	return 0;
}

