#include "Vector.h"
#include "PQ.h"
#include "PQ_def.h"
template <typename T>class PQ_ComplHeap:public PQ<T>, public Vector<T>{
protected:
	Rank percolateDown(Rank n, Rank i);
	Rank percolateUp(Rank i);
	void heapify(Rank n);
public:
	PQ_ComplHeap(){}
	PQ_ComplHeap(T* A,Rank n)
	{
		this->copyFrom(A,0,n);
		heapify(n);
	}
	void insert(T);
	T getMax();
	T delMax();
} ;
template <typename T>
T PQ_ComplHeap<T>::getMax(){ return this->_elem[0];}

template <typename T> void PQ_ComplHeap<T>::insert ( T e ) { //将词条插入完全二叉堆中
   Vector<T>::insert ( e ); //首先将新词条接至向量末尾
   percolateUp ( this->_size - 1 ); //再对该词条实施上滤调整
}

void swap( int &a, int &b){
   int tmp = a;
   a = b;
   b = tmp;
}
//上滤
//对向量中的第i个词条实施上滤操作，i < _size
template <typename T> Rank PQ_ComplHeap<T>::percolateUp ( Rank i ) {
   while ( ParentValid ( i ) ) { //只要i有父亲（尚未抵达堆顶），则
      Rank j = Parent ( i ); //将i之父记作j
      if (  this->_elem[i] <= this->_elem[j]  ) break; //一旦当前父子不再逆序，上滤旋即完成
      swap ( this->_elem[i], this->_elem[j] ); i = j; //否则，父子交换位置，并继续考查上一层
   } //while
   return i; //返回上滤最终抵达的位置
}

//delMax()
template <typename T> T PQ_ComplHeap<T>::delMax() { //删除非空完全二叉堆中优先级最高的词条
   T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[ --this->_size ]; //摘除堆顶（首词条），代之以末词条
   percolateDown ( this->_size, 0 ); //对新堆顶实施下滤
   return maxElem; //返回此前备份的最大词条
}

//对向量前n个词条中的第i个实施下滤，i < n
template <typename T> Rank PQ_ComplHeap<T>::percolateDown ( Rank n, Rank i ) {
   Rank j; //i及其（至多两个）孩子中，堪为父者
   while ( i != ( j = ProperParent ( this->_elem, n, i ) ) ) //只要i非j，则
      { swap ( this->_elem[i], this->_elem[j] ); i = j; } //二者换位，并继续考查下降后的i
   return i; //返回下滤抵达的位置（亦i亦j）
}

//Floyd建堆
template <typename T> void PQ_ComplHeap<T>::heapify ( Rank n ) { //Floyd建堆算法，O(n)时间
   for ( int i = LastInternal ( n ); InHeap ( n, i ); i-- ) //自底而上，依次
/*DSA*/
      percolateDown ( n, i ); //下滤各内部节点
// /*DSA*/for ( int k = 0; k < n; k++ ) {
// /*DSA*/  int kk = k; while ( i < kk ) kk = (kk - 1) / 2;
// /*DSA*/  i == kk ? print(_elem[k]) : print("    " );
// /*DSA*/}; printf("\n");
// /*DSA*/}
}

template <typename T> void Vector<T>::heapSort (  Rank lo, Rank hi ) { //0 <= lo < hi <= size
   PQ_ComplHeap<T> H ( _elem + lo, hi - lo ); //将待排序区间建成一个完全二叉堆，O(n)
   while ( ! H.empty() ) //反复地摘除最大元并归入已排序的后缀，直至堆空
      _elem[--hi] = H.delMax(); //等效于堆顶与末元素对换后下滤
}

