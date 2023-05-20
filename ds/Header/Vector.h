#ifndef VECTOR
#define VECTOR
typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
#include<stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace std;

template <typename T> 
class Vector { //����ģ����
	protected:
		Rank _size;
		int _capacity, clock;
		T* _elem; //��ģ��������������
		int *_elem2;
		void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
		void expand(); //�ռ䲻��ʱ����
		void shrink(); //װ�����ӹ�Сʱ����
		Rank partition ( Rank lo, Rank hi );
		Rank _partition ( Rank lo, Rank hi );

	public:
// ���캯��
//   T* check2(Rank lo, Rank hi, double m1, double m2);
		void quickSort ( Rank lo, Rank hi );
		void heapSort ( Rank lo, Rank hi );
		void shellSort ( Rank lo, Rank hi );
		void display(T* A,int n);
		void selectSort(Rank lo,Rank hi);
		void merge ( Rank lo, Rank mi, Rank hi ); //�鲢�㷨
		void mergeSort ( Rank lo, Rank hi ); //�鲢�����㷨
		bool bubble ( Rank lo, Rank hi ); //ɨ�轻��
		bool bubble ( Rank n, Rank lo, Rank hi);
		void bubbleSort ( Rank n, Rank lo, Rank hi);//���غ���
		void bubbleSort ( Rank lo, Rank hi ); //���������㷨
		Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) {
			//����Ϊc����ģΪs������Ԫ�س�ʼΪv
			_elem = new T[_capacity = c];
			for( _size = 0; _size < s; _elem[_size++] = v );
		} //s<=c
		Vector ( T const* A, Rank n ) {
			copyFrom ( A, 0, n );    //�������帴��
		}
		Vector ( T const* A, Rank lo, Rank hi ) {
			copyFrom ( A, lo, hi );    //����
		}
		
		Vector ( Vector<T> const& V ) {
			copyFrom ( V._elem, 0, V._size );    //�������帴��
		}

		Vector ( Vector<T> const& V, Rank lo, Rank hi ) {
			copyFrom ( V._elem, lo, hi );    //����
		}
// ��������
		~Vector() {
			delete [] _elem;    //�ͷ��ڲ��ռ�
		}
// ֻ�����ʽӿ�
		Rank size() const {
			return _size;    //��ģ
		}
		bool empty() const {
			return !_size;    //�п�
		}
		int disordered() const; //�ж������Ƿ�������
		Rank find ( T const& e ) const {
			return find ( e, 0, _size );    //���������������
		}
		Rank find ( T const& e, Rank lo, Rank hi ) const; //���������������
		Rank search ( T const& e ) const { //���������������
			return ( 0 >= _size ) ? -1 : search ( e, 0, _size );
		}
		Rank search ( T const& e, Rank lo, Rank hi ) const; //���������������
// ��д���ʽӿ�
		T& operator [] ( Rank r ) const; //�����±������������������������ʽ���ø�Ԫ��
		Vector<T>& operator = ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
		T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
		int remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
		Rank insert ( Rank r, T const& e ); //����Ԫ��
		Rank insert ( T const& e ) {
			return insert ( _size, e );    //Ĭ����ΪĩԪ�ز���
		}
		void unsort ( Rank lo, Rank hi ); //��[lo, hi)����
		void unsort() {
			unsort ( 0, _size );    //��������
		}
		int deduplicate(); //����ȥ��
		int uniquify(); //����ȥ��
		T* check(Rank lo, Rank hi, double m1, double m2);
// ����


		void traverse ( void (* ) ( T& ) ); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
		template <typename VST> void traverse ( VST& ); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector
//������������������������������������������������������������������������������������������������������������//
//copyfrom



template <typename T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[_size++] = A[lo++];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
	if (_elem) 
		delete []_elem;
	copyFrom (V._elem, 0, V._size);
	return *this;
}//=������,��������Ҫ��

template <typename T>
T& Vector<T>::operator [] ( Rank  r) const {  //�����±������
	return _elem[r];   //assert: 0 <= r < _size
}

template <typename T>
T* Vector<T>::check(Rank lo, Rank hi, double m1, double m2) {
	int count = 0;
	T* temp = new T[hi-lo];
	for(int i=lo; i<hi; i++) {
		if(_elem[i]>=m1&&_elem[i]<m2) {
			count++;
			temp[count++]=_elem[i];
		}
	}
	for(int i=count; i<hi; i++)
		temp[i]='\0';
	return temp;
}

//����expand
template <typename T>
void Vector<T>::expand() {
	if(_size < _capacity) return;//δ�� ������
	if(_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY; //��֤������ԭ��������
	T *oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete []oldElem;//�ͷ�ԭ�ռ�
}

//����shrink
template <typename T>
void Vector<T>::shrink() {
	if(_capacity < DEFAULT_CAPACITY << 1)return;
	if(_size << 2 > _capacity)return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete []oldElem;
}
//����
template <typename T>
Rank Vector<T>::insert ( Rank r, T const& e ) {
	expand();//����Ҫ��������
	for(int i=_size; i>r; i--)
		_elem[i] = _elem[i-1];
	_elem[r] = e;
	_size++;
	return r;
}
//����
template <typename T>
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const {
	while ((lo < hi--)&&(e != _elem[hi] ) );
	return hi;
}
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo,Rank hi) { //���ֲ���
	while(1<hi - lo) {
		Rank mi = (lo < hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return (e == A[lo]) ? lo : -1;
}

//����
template <typename T>
void Vector<T>::unsort ( Rank lo, Rank hi ) {
	T* V = _elem + lo;
	for(Rank i = hi - lo; i > 0; i--)
		swap(V[i-1],V[rand() % i]);
} //��[lo, hi)����

//����ɾ��
template <typename T>
int Vector<T>::remove ( Rank lo, Rank hi ) {
	if( lo == hi)return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();//����Ҫ ����
	return hi - lo;
}
//��Ԫ��ɾ��
template <typename T>
T Vector<T>::remove ( Rank r ) {
	T e = _elem[r];//���ݱ�ɾ����Ԫ��
	remove(r, r+1);
	return e;
}
//Ψһ��
template <typename T>
int Vector<T>::deduplicate() { //����ȥ��
	int oldSize = _size;
	Rank i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0)?i++:remove( i );
	return oldSize - _size;
}
template <typename T>
int Vector<T>::uniquify() {
	Rank i = 0,j = 0;
	while ( ++j < _size)
		if( _elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - i;
}
//���������
template <typename T>
int Vector<T>::disordered() const {
	int n = 0;
	for(int i = 1; i < _size; i++)
		if( _elem[i-1] > _elem[i] ) n++;
	return n;//���ҽ���n=0ʱ��������
}
//����


template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) { //һ��ɨ�轻��
	bool sorted = true;
	while (++lo < hi)
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted; //���������־
}
template<typename T>
bool Vector<T>::bubble(Rank n, Rank lo, Rank hi) { //����bubble
	bool sorted = true;
	while (++lo < hi) {
		if (_elem[lo - 1]<_elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);	//��������ֵ
		}
	}
	return sorted;
}
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {	//ð������
	while (!bubble(lo, hi--));
}
template<typename T>
void Vector<T>::bubbleSort(Rank n, Rank lo, Rank hi) {	//ð������
	while (!bubble(n, lo, hi--));
}


template <typename T> //���������Ĺ鲢
void Vector<T>::merge(Rank lo ,Rank mi, Rank hi) {
	//��mi Ϊ�磬���������������[lo,mi) [mi, hi)
	T*  A = _elem + lo; //�ϲ��������A[0,hi-lo) = _elem[lo,hi)
	int lb = mi - lo ;
	T* B = new T[lb] ;//ǰ������B[0,lb) = _elem[lo,mi)
	for(Rank i = 0 ; i < lb ; B[i] = A[i++]); //����ǰ������,ֻ��ǰ����б�Ҫ���ƣ��б����ǵķ���
	int lc = hi-mi ;
	T* C = _elem + mi;//ǰ������C[0,lc) = _elem[mi,hi)
	for(Rank i = 0 , j = 0,k = 0 ; (j < lb)||(k < lc);) {
		// ��B[j]��C[k]�е�С������A��ĩβ
		if((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if((k < lc) && (!(j < lb) || C[k] <= B[j])) A[i++] = C[k++];
	}
	delete []B; //�ͷ���ʱ�ռ�B
} // �鲢��õ��������������� lo,hi



//���β���
template <typename T> //���������Ĺ鲢����
void Vector<T>::mergeSort(Rank lo , Rank hi) {
	if (hi - lo < 2) return; //һֱ���ε���Ԫ�����䣬��ʱ��Ȼ˳��
	int mi = (lo + hi) >>1; // �ҵ������
	mergeSort(lo,mi);
	mergeSort(mi,hi);
	merge(lo,mi,hi); //���Σ�Ȼ��鲢
}

template <typename T> //������������
void Vector<T>::quickSort( Rank lo, Rank hi ) { //0 <= lo < hi <= size
	if(hi - lo < 2)
		return;
	Rank mi = partition(lo,hi-1);
	quickSort(lo,mi);
	quickSort(mi+1,hi);
}
template <typename T> //��㹹���㷨�汾A
Rank Vector<T>::_partition ( Rank lo, Rank hi ) { //DUP1�棺��DUP��ȼۣ���������LUG��ȼ۵�LUG1��
	swap ( _elem[lo], _elem[ lo + rand() % ( hi - lo +1) ] ); //��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ
	while ( lo < hi ) { //�����������˽�������м�ɨ��
		while ( ( lo < hi ) && ( pivot < _elem[hi] ) ) //�ڴ���pivot��ǰ����
			hi--;
		_elem[lo] = _elem[hi];
		//������pivot�߹������������
		while ( ( lo < hi ) && ( _elem[lo] <= pivot ) ) //��С��pivot��ǰ����
			lo++; //������չ���������
		_elem[hi] = _elem[lo]; //��С��pivot�߹����Ҷ�������
	} //assert: lo == hi
	_elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
	return lo; //����������
}

template <typename T> //��㹹���㷨�汾B
Rank Vector<T>::partition ( Rank lo, Rank hi ) { //DUP�棺���Ż��������ؼ�����ͬ���˻����
	swap ( _elem[lo], _elem[ lo + rand() % ( hi - lo + 1 ) ] ); //��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ
	while ( lo < hi ) { //�����������˽�������м�ɨ��
		while ( lo < hi )
			if ( pivot < _elem[hi] ) //�ڴ���pivot��ǰ����
				hi--; //������չ�Ҷ�������
			else { //ֱ������������pivot��
				_elem[lo++] = _elem[hi];    //����������������
				break;
			}
		while ( lo < hi )
			if ( _elem[lo] < pivot ) //��С��pivot��ǰ����
				lo++; //������չ���������
			else { //ֱ��������С��pivot��
				_elem[hi--] = _elem[lo];    //��������Ҷ�������
				break;
			}
	} //assert: lo == hi
	_elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
	return lo; //����������
}
template <typename T> //����ϣ������/��������
void Vector<T>::shellSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size <= 2^30
	//printf ( "\tshellSort [%3d, %3d)\n", lo, hi );
	for ( Rank d = 0x3FFFFFFF; 0 < d; d >>= 1 ) //PS Sequence: { 1, 3, 7, 15, ..., 1073741823 }
		for ( Rank j = lo + d; j < hi; j++ ) { //for each j in [lo+d, hi)
			T x = _elem[j];
			Rank i = j - d;
			while ( lo <= i && _elem[i] > x ) {
				_elem[i + d] = _elem[i];
				i -= d;
			}
			_elem[i + d] = x; //insert [j] into its subsequence
		}
}
template <typename T>
void Vector<T>::selectSort(Rank lo,Rank hi) { //ѡ������
	for(int i=lo; i<hi; i++) {
		int index = i;
		for(int j = i+1; j < hi ; j++) {
			if(_elem[index]>_elem[j])
				index = j;
		}
		swap(_elem[i],_elem[index]);
	}
}

template <typename T>
void Vector<T>::display(T* A,int n)
{ 
	for(int i = 0;i<n;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
}
#endif





