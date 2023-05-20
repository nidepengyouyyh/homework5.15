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

template <typename T> void PQ_ComplHeap<T>::insert ( T e ) { //������������ȫ�������
   Vector<T>::insert ( e ); //���Ƚ��´�����������ĩβ
   percolateUp ( this->_size - 1 ); //�ٶԸô���ʵʩ���˵���
}

void swap( int &a, int &b){
   int tmp = a;
   a = b;
   b = tmp;
}
//����
//�������еĵ�i������ʵʩ���˲�����i < _size
template <typename T> Rank PQ_ComplHeap<T>::percolateUp ( Rank i ) {
   while ( ParentValid ( i ) ) { //ֻҪi�и��ף���δ�ִ�Ѷ�������
      Rank j = Parent ( i ); //��i֮������j
      if (  this->_elem[i] <= this->_elem[j]  ) break; //һ����ǰ���Ӳ������������������
      swap ( this->_elem[i], this->_elem[j] ); i = j; //���򣬸��ӽ���λ�ã�������������һ��
   } //while
   return i; //�����������յִ��λ��
}

//delMax()
template <typename T> T PQ_ComplHeap<T>::delMax() { //ɾ���ǿ���ȫ����������ȼ���ߵĴ���
   T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[ --this->_size ]; //ժ���Ѷ����״���������֮��ĩ����
   percolateDown ( this->_size, 0 ); //���¶Ѷ�ʵʩ����
   return maxElem; //���ش�ǰ���ݵ�������
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> Rank PQ_ComplHeap<T>::percolateDown ( Rank n, Rank i ) {
   Rank j; //i���䣨���������������У���Ϊ����
   while ( i != ( j = ProperParent ( this->_elem, n, i ) ) ) //ֻҪi��j����
      { swap ( this->_elem[i], this->_elem[j] ); i = j; } //���߻�λ�������������½����i
   return i; //�������˵ִ��λ�ã���i��j��
}

//Floyd����
template <typename T> void PQ_ComplHeap<T>::heapify ( Rank n ) { //Floyd�����㷨��O(n)ʱ��
   for ( int i = LastInternal ( n ); InHeap ( n, i ); i-- ) //�Ե׶��ϣ�����
/*DSA*/
      percolateDown ( n, i ); //���˸��ڲ��ڵ�
// /*DSA*/for ( int k = 0; k < n; k++ ) {
// /*DSA*/  int kk = k; while ( i < kk ) kk = (kk - 1) / 2;
// /*DSA*/  i == kk ? print(_elem[k]) : print("    " );
// /*DSA*/}; printf("\n");
// /*DSA*/}
}

template <typename T> void Vector<T>::heapSort (  Rank lo, Rank hi ) { //0 <= lo < hi <= size
   PQ_ComplHeap<T> H ( _elem + lo, hi - lo ); //�����������佨��һ����ȫ����ѣ�O(n)
   while ( ! H.empty() ) //������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
      _elem[--hi] = H.delMax(); //��Ч�ڶѶ���ĩԪ�ضԻ�������
}

