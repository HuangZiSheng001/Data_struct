#include "SeqBinaryTree.h"
#include <assert.h>
#include<iostream>
using namespace std;
typedef enum PointerTag {LINK,THREAD};
template<typename ElemType>
class ThreadTree
{
public:
    class ThreadNode()
    {
        public:
            ThreadNode():ltag(LINK), lchild(NULL), rtag(LINK), rchild(NULL){};
            ~ThreadNode(){};
    public:
        ElemType data;
        class ThreadTNode *lchild, *rchild;
        PointerTag ltag, rtag;
    }
    typedef ThreadNode*  ThreadNodePointer;

public:
    //中序穿线二叉树置空
    void clear();
    //递归求中序二叉树的深度
    int depth();
    //取中序穿线二叉树的根指针
    ThreadNodePointer getRoot();
    //中序遍历中序穿线二叉树
    void inOrderTraverse_ThreadTree();
    //判断是否为空
    bool isEmpty();
    //随机生成一个中序穿线二叉树
    void randomCreate();
    //找指定结点中序的前驱
    bool searchPriorNode(ElemType key, ElemType& prior);
    //找指定结点中序的后继
    bool searchNextNode(ElemType key, ElemType& next);
    //找指定结点
    bool searchNode(ElemType key, ThreadNodePointer p);
    //中序穿线二叉树的顺序存储结构转换为二叉链表存储
    void sequetialToThreadTree(SeqBinaryTree<ElemType> T);
    //中序穿线二叉树的二叉链表存储转换为顺序存储
    void ThredTreeToSequential();
///////////    //////////////////////////////////////////////////////////////
private:
    //回收中序穿线二叉树结点存储空间的辅助函数
    void deleteNode_aux(ThreadNodePointer p);
    //递归求中序穿线二叉树深度的辅助函数
    int depth_aux(ThreadNodePoiter p);
    //中序穿线二叉树顺序存储转换为二叉链表存储的辅助函数1---初步建立二叉表（未穿线）
    void sequetialToThreadTree_aux1(int index, ThreadNodePointer p);
    //中序穿线二叉树顺序存储转换为二叉链表存储的辅助函数2---中序穿线
    void sequentialToThreadTree_aux2(ThreadNodePointer p);
    //中序穿线二叉树二叉链表存储结构转换为顺序存储结构的辅助函数
    void ThreadTreeToSequential_aux();
//////////////////////////////系统的构造函数、析构函数、输入输出函数的声明////////////////////////////////
    //构造函数（采用二叉链表存储）
    ThreadTree();
    //析构函数（采用二叉链表存储）
    virtual~ThreadTree();
    //拷贝初始化函数（采用二叉链表存储）
    ThreadTree(const ThreaTree<ElemType>& otherT);
    //输入中序穿线二叉树（采用二叉链表存储）
    void read(istream& in);
    //输出中序穿线二叉树（采用二叉链表存储）;
    void dispaly(ostream& out);
/////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    ThreadNodePointer root;
    SeqBinaryTree<ElemType> seqT;
};

///////////////////////实现///////////////////////////////////////////////////////////
//置空
template <typename ElemType>
void ThreadTree<ElemType>::clear()
{
    seqT.clear();
    deleteNode_aux(root);
    root = NULL;
}
//置空的辅助函数
template<typename ElemType>
void ThreadTree<ElemType>::deleteNode_aux(ThreadNodePointer p)
{
    //按后序遍历方式逐一回收每个结点
    if (p)
    {
        if (p->ltag == LINK)
        {
            deleteNode_aux(p->lchid);
        }
        if (p->rtag == LINK)
        {
            deleteNode_aux(p->rchild);
        }
        delete p;

    }
}

//功能：递归求中序穿线二叉树的深度
template<typename ElemType>
int ThreadTree<ElemType>::depth()
{
    return depth_aux(root);
}

//递归求中序穿线二叉树深度的辅助函数
template<typename ElemType>
int ThreadTree<ElemType>::depth_aux(ThreadNodePointer p)
{
    int lDep, rDep;
    if (!p)
    {
        return 0;
    }
    else
    {
        if (p-ltag==LINK)
        {
            lDep = depth_aux(p->lchild);
        }
        else
        {
            lDep = 0;
        }
        if (p->rtag)
        {
            rDep = depth_aux(p->rchild);
        }
        else
        {
            rDep = 0;
        }
        return (lDep > rDep ? lDep : rDep) + 1;
    }
}

//取中序穿线二叉树的根指针
template<typename ElemType>
ThreadTree<ElemType>::ThreadNodePointer ThreadTree<ElemType>::getRoot()
{
    return root;
}

//中序遍历中序穿线二叉树
template<typename ElemType>
void ThreadTree<ElemType>::inOrderTraverse_ThreadTree()
{
    ThreadNodePointer p = root;
    //从根结点开始，把每一个当前结点当做子树的根，对每颗子树进行中序遍历
    while (p)
    {//首先沿着其左子树的左指针向下滑动，直到某结点有左线索为止（即此时已经没有左子树）
        while (p -> ltag == LINK)
            p = p->lchild;
        //访问该结点
        cout << p->data;
        //如果该结点有右线索，则沿着右线索一直往上爬，访问右线索上的每一个结点，直到某结点不再有右线索，
        //而有右指针为止
        while (p->rtag==THREAD && p->rchild)
        {
            p = p->rchild;
            cout << p->data;
        }
        //进入右子树
        p = p->rchild;
    }
}

//判断是否为空
template <typename ElemType>
void ThreadTree<ElemType>::isEmpty()
{
    return root ? false : true;
}
//找指定结点中序的前驱
template <typename ElemType>
bool ThredTree<ElemType>::searchPriorNode(ElemType key, ElemType& prior)
{
    ThreadNodePointer p;//预指向待查结点的指针
    if (searchNode(key,p))//首先查找数据域为指定值的结点，如果找到，则p指向该结点
    {  
        if (p->ltag == THREAD)//如果指针p所指结点有左线索
        {
            if (!p->lchild)//如果是中序遍历的第一个结点，则无前驱
            {
                return false;//返回错误
            }
            else
            {
                //如果不是中序遍历的第一个结点，则做线索即为指定结点中序遍历的前驱
                prior = p->lchild->data;
            }
        }
        else
        {
            //如果指针p所指结点有左指针，则沿着左指针进入左子树，再沿着右指针往下滑动，直到某个结点不再有右指针，
            //而有右线索为止,则该结点即为指定结点中序遍历的前驱
            p = p->lchild;
            while (p->rtag==LINK)
            {
                p = p->rchild;
            }
            prior = p->data;
        }

    }
    else
    {
        return false;
    }
    return TRUE;
}

//找指定结点中序的后继
template<typename ELemType>
bool ThreadTree<ElemTye>::searchNextNode(ElemType key, ElemType& next)
{
    ThreadNodePointer p;
    if (searchNode(key,p))//首先查找数据域为指定值的结点，如果找到，则用指针p指向该节点。
    {
        if (p->rtag==THREAD)//如果指针p所指结点有右线索
        {
            if (!p->rchild)//如果右线索为空，则不存在后继，返回错误。
            {
                return false;
            }
            else
            {
                next = p->rchild->data;//否则返回右线索所指结点的数据域
            }
        }
        else
        {//如果指针p所指结点有右指针，则沿着右指针进入其右子树，然后，沿着左指针往下滑，直到某个结点不再有
            //左指针，而有左线索为止，则该结点即为指定结点中序遍历的后继
            p = p->rchild;
            while (p->ltag == LINK)
            {
                p = p->lchild;
            }
            next = p->data;
        }
    }
    else
    {//如果未查找到指定数据域的结点
        return false;
    }
    return true;
    
}

//找指定结点
template <typename ElemType>
bool ThreadTree<ElemType>::searchNode(ElemType key, ThreadNodePointer& p)
{
    p = root;//指向当前结点的指针，初始化为根指针
    while (p)
    {  //首先沿着其左子树指针向下滑动，直到某结点出现左线索为止
        while (p->ltag == LINK)
        {
            p = p->lchild;
        }
        //判断该结点的数据域是否等于指定的值key
        if (p->data==key)
        {
            return true;
        }
        //如果该结点有右线索，则沿着右线索一直往上爬，直到某结点出现右指针为止。
        while (p->rtag==THREAD&&p->rchild)
        {
            p = p->rchild;
            //判断右线索上每个结点的数据域是否等于指定值key
            if (p->data==key)
            {
                return true;
            }
        }
        //进入右子树
        p = p->rchild;
            
    }
    return false;
}

//中序穿线二叉树顺序存储转换为二叉链表存储
template<typename ElemType>
void ThreadTree<ElemType>::sequetialToThreadTree(SeqBinaryTree<ElemType>T)
{
    //把顺序存储中序穿线二叉树T赋值给当前中序穿线二叉树对应的顺序存储树
    seqT = T;
    //中序穿线二叉树顺序存储转换为二叉链表存储（为穿线）
    void sequetialToThreadTree_aux1(0, root);
    //将此时的二叉链表穿线
    void sequetialToThreadTree_aux2(root);
}

//中序穿线二叉树顺序存储转换为二叉链表存储的辅助函数1--初步建立二叉链表
template<typename ElemType>
void ThredTree<ElemType>::sequetialToThreadTree_aux1(int index, ThreadNodePointer p)
{
    //获得存放顺序存储中序穿线二叉树的最后一个结点的下标
    int n = seqT.getFinalIndex();
    //如果顺序存储中序穿线二叉树的最后一个结点的下标为-1，则把指针p置空，并返回
    if (n==-1)
    {
        p = NULL;
        return;
    }
    //申请二叉链表存储的中序穿线二叉树的新结点，并由指针p指向
    p = new ThreadNode;
    assert(p != 0);

    //把顺序存储中序穿线二叉树下标为index的结点的数据域赋值给新结点的数据域
    p->data = seqT.getNode(index);
    //如果顺序存储中序穿线二叉树下标为index的结点无左子树，则新结点的lchild也置空。
    //否则，用下标2*index+1和新结点的lchild自递归，以把下标为index的结点的左子树转化为二叉链表存储结构
    if ((2*index+1>n)||seqT.getNode(2*index+2)==' ')
    {
        p->lchild = NULL;
    }
    else
    {
        sequetialToThreadTree_aux1(2 * index + 1, p->lchild);
    }
    //如果顺序存储中序穿线二叉树下标为index的结点无右子树，则新结点的rchild也置空。
    //否则，用下标2*index+2和新结点的rchild自递归，以把下标为index的结点的右子树转化为二叉链表存储结构
    if ((2*index+2>n)||seqT.getNode(2*index+2)==' ')
    {
        p->rchild = NULL;
    }
    else
    {
        sequetialToThreadTree_aux1(2 * index + 2, p->rchild);
    }
}

//中序穿线二叉树顺序存储转换为二叉链表存储的辅助函数2--中序穿线
template<typename ElemType>
void ThreadTree<ElemTytpe>::sequentialToThreadTree_aux2(ThreadNodePointer p)
{
    //当前结点按中序遍历的前驱的指针，初始化为空
    static ThreadNodePointer pre = NULL;
    if (p)//如果当前结点不为空，则对以其为根的子树进行中序穿线
    {
        //用当前结点的lchild自递归，完成其左子树的线索化
        sequentialToThreadTree_aux2(p->lchild);
        if (!p->lchild)
        {//如果当前结点的lchild为空，则将其用作中序的前驱线索
            p->ltag = THREAD;
            p->lchild = pre;
        }
        if (pre&&!pre->rchild)
        {//如果当前结点按中序遍历的前驱的rchild为空，则将其用作中序的后继线索
            pre->rtag = THREAD;
            pre->rchild = p;
        }
        pre = p;//更新当前结点按中序遍历的前驱的指针
        //用当前结点的rchild自递归，完成其右子树的线索化
        sequetialToThreadTree_aux2(p->rchild);
    }
    if (p==root)
    {//如果当前结点等于根结点，则完成所有结点的中序穿线
        //最后一个结点的有标记宝珠为线索，且右线索为空
        //当前结点按中序遍历前驱的指针置空，以便再次调用此函数做线索化
        if (pre)
        {
            pre->rtag = THREAD;
            pre->rchild = NULL;
        }
        pre = NULL;
    }
}

//中序穿线二叉树的二叉链表存储转换为顺序存储
template<typename ElemType>
void ThreadTree<ElemType>::ThredTreeToSequential()
{
    int max_total;//预存放具有同样深度的满二叉树的结点数
    SeqBinaryTree<ElemType> tempT;//临时顺序存储结构的二叉树temT
    //如果当前中序穿线二叉树为空，则其对应的顺序存储树也置空
    if (!root)
    {
        seqT.clear();
        return;
    }
    //计算具有同样深度的二叉树的结点数
    max_total = 1;
    for (int i = 1; i < =depth(); i++)
    {
        max_total *= 2;
    }
    max_total -= 1;
    //根据满二叉树的结点数，设置临时顺序存储结构二叉树tempT
    tempT.initialAddress = new ThreadNode[max_total];
    tempT.finalIndex = max_total - 1;
    //借助另一个辅助递归函数,把当前中序穿线二叉树的二叉链表转换为顺序存储结构，暂存于tempT中
    ThreadTreeToSequential_aux(tempT, root, 0);

}

template<typename ElemType>
void ThreadTree<ElemType>::ThreadTreeToSequential_aux(SeqBinaryTree<ElemType>& tempT, ThreadNodePointer p, int index)
{
    if (p)
    {//用指针p所指结点的数据域设置中序穿线二叉树存储空间下标为index的值
        tempT.setNode(index, p->data);
    //如果指针p所指结点有左指针，则调用左指针和小标为2*index+1自递归
        //把其左子树的二叉链表转换为顺序存储结构
        if (p->ltag ==LINK)
        {
            ThreadTreeToSequential_aux(tempT, p->lchild, 2 * index + 1);
        }
        if (p->rtag==LINK)
        {
            ThreadTreeToSequential_aux(tempT, p->rchild, 2 * index + 2);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//构造函数
template<typename ElemType>
ThreadTree<ElemType>::ThreadTree()
{
    root = NULL:
    seqT.clear();
}

//析构函数
template<typename ElemType>
ThreadTree<ElemType>::~ThreadTree()
{
    clear();
}
//中序穿线二叉树（链式存储）的拷贝初始化函数
template<typename ElemType>
ThreadTree<ElemType>::ThreadTree(const ThreadTree<ElemType>& otherT)
{
    //如果树otherT为空，则当前中序穿线二叉树初始化为空
    if (!otherT.root)
    {
        root = NULL;
        seqT.clear();
    }
    else
    {//如果otherT不为空，则从树otherT的根结点开始，递归赋值其全部结点到当前中序穿线二叉树，只是复制结点，
        //并没有中序穿线
        ThreadTree_aux(root, otherT.root);
        //中序穿线二叉树顺序存储转换为二叉链表存储的辅助函数2--中序穿线
        sequetialToThreadTree_aux2(root);
        //生成当前中序穿线二叉树对应的顺序存储树
        ThreadTreeToSequential();

    }
}

//中序穿线二叉树（链式存储）拷贝初始化函数的辅助函数
template<typename ElemType>
void ThreadTree<ElemType>::ThreadTree_aux(ThreadNodePointer& p, ThreadNodePointer otherP)
{    //如果指针otherP为空
    if (!otherP)
    {
        p = NULL;
        return;
    }
    //如果指针otherP不为空，则复制指针otherP所指结点的数据域到新结点
    p->data = otherP->data;
    if (otherP->ltag==THREAD)
    {
        p->lchild = NULL;
    }
    else
    {
        ThreadTree_aux(p->lchild.otherP->lchild);
    }
    if (otherP->rtag==THREAD)
    {
        p->rchild = NULL;
    }
    else
    {
        ThreadTree_aux(p->rchild, otherP->rchild);
    }
}

//输入中序穿线二叉树
template<typename ElemType>
void ThreadTree<ElemType>::read(istream& in)
{
    cout << "采用顺序存储方式创建一颗中序穿线二叉树" << endl;
    in >> seqT;
    //中序穿线二叉树顺序存储转换为二叉链表存储
    sequetialToThreadTree_aux1(0, root);
    sequetialToThreadTree_aux2(root);
}

//重载输入运算符的定义
template<typename ElemType>
istream& operator >> (istream& in, ThreadTree<ElemType>& tT)
{
    tT.read(in);
    return in;
}
//输出中序穿线二叉树
template<typename ElemType>
void ThreadTree<ElemType>::dispaly(ostream& out)
{
    out << seqT;
}

//功能：重载输出运算符
template<typename ElemType>
ostream& operator << (ostream& out, ThreadTree<ElemType>tT)
{
    tT.dispaly(out);
    return out;
}