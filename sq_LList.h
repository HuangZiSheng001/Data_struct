//sq_LList.h
#include<iostream>
// using namespace std;    是否用namespace  :  参考  C 11标准
template<class T>
class sq_LList{
private:
    int mm;
    int nn;
    T *v;
public:
    sq_LList()  { mm = 0 ; nn = 0; return ;}
    sq_LList(int);
    void prt_sq_LList();
    int flag_sq_LList();
    void ins_sq_LList(int, T);
    void del_sq_LList(int);
};

// 建立空顺序表
template<class T>
sq_LList<T>::sq_LList(int m){
    mm = m;
    v = new T[mm];
    nn = 0;
    return;
}

// 顺序输出顺序表中的元素与顺序表长度
template<class T>
void sq_LList<T>::prt_sq_LList(){
    int ins_sq_LList;
    std::cout<<" nn = "<< nn << std::endl;
    for( i =0; i < nn; i++) std::cout << v[i] << std::endl;
    return;
}

// 检测表的状态
template<class T>
int sq_LList<T>::flag_sq_LList(){
    if( nn == mm)  return (-1);
    if( nn == 0) return (0);
    return (1);;
}

// 在指定元素前插入新元素
template<class T>
void sq_LList<T>::ins_sq_LList(){
    int k ;
    if (nn == mm) {  std::cout << "overflow" << std::endl;   return ;}

    if( i > nn)  i = nn+1;

    if(i < 1) i =1;

    for( k = nn; k >= i ; k--)  v[k] = v[k-1];

    v[i-1] = b;

    nn++;

    return;

}

// 
template<class T>
void sq_LList<T>::del_sq_LList(int i){
    int k;
    if(nn == 0)  {  std::cout << "underflow" << std::endl;   return ;}

    if( (i<1) || (i>nn)) { std::cout << "Not this element in the list" << std::endl;   return ;}

    for( k = i;  k<nn; k++) v[k-1] = v[k];
    nn--;
    return;
}


#include"sq_LList.h"
int main()
{
    sq_LList<double>s1(100);
    std::cout<< " first print: "<< std::endl;
    s1.prt_sq_LList();

    s1.ins_sq_LList(0, 1.5);
    s1.ins_sq_LList(1, 2.5);
    s1.ins_sq_LList(4, 3.5);

    std::cout<<" secondly print:" << std::endl;
    s1.prt_sq_LList();

    s1.del_sq_LList(0);
    s1.del_sq_LList(2);

    std::cout<<"thirdly  print:" << std::endl;
    s1.prt_sq_LList();

    return 0;
}











