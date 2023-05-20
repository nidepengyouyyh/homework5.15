#ifndef LIST
#define LIST
#include "listNode.h"
template <typename T>
class List { //�б�ģ����
	private:
		int _size;
		ListNodePosi(T) header;
		ListNodePosi(T) trailer;//��ģ��ͷ�ڱ���β�ڱ�

	protected:
		void init();
		int clear();
		void copyNodes( ListNodePosi(T), int);
		void merge( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
		void mergeSort(ListNodePosi(T)&, int);
		void selectionSort( ListNodePosi(T), int);
		void insertionSort(ListNodePosi(T), int);

	public:
//���캯��
		T dequeue2() {
			return remove ( first() ); 
			//return remove ( first() );    //���ӣ��ײ�ɾ��
		}
		List() {
			init();    //Ĭ��
		}
		List( List<T> const& L);
		List( List<T> const& L, Rank r, int n);
		List( ListNodePosi(T) p, int n);
//��������
		~List();//�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
//ֻ�����ʽӿ�
		Rank size() const {
			return _size;   //��ģ
		}
		bool empty() const {
			return _size <= 0;   //�п�
		}
		T& operator[](Rank r) const;//���أ�֧��Ѱ�ȷ���,Ч�ʽϵ�
		ListNodePosi(T) first() const {
			return header->succ;   //�׽ڵ�λ��
		}
		ListNodePosi(T) last() const {
			return trailer->pred;   //β�ڵ�λ��
		}
		bool valid (ListNodePosi(T) p) {
			return p && (trailer != p) && (header != p);   //��ͷ��β�ڵ��ͬ��NULL
		}
		int disordered() const;
		ListNodePosi(T) find (T const& e) const { //�����б����
			return find(e, _size, trailer);
		}
		ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;//�����������
		ListNodePosi(T) search (T const& e) const { //�����б����
			return search(e, _size, trailer);
		}
		ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;//�����������
		ListNodePosi(T) selectMax (ListNodePosi(T) p, int n);
		ListNodePosi(T) selectMax() {
			return selectMax(header->succ, _size);	   //���������
		}
//��д���ʽӿ�
		ListNodePosi(T) insertAsFirst(T const& e);
		ListNodePosi(T) insertAsLast(T const& e);
		ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
		ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
		T remove(ListNodePosi(T) p);
		void merge(List<T>& L) {
			merge(first(), size, L, L.first(), L._size);
		}
		void sort(ListNodePosi(T) p, int n);
		void sort() {
			sort(first(), _size);
		}
		int deduplicate();
		int uniquify();
		void reverse();
//����
		void traverse(void(* )(T&));
		template <typename VST>
		void traverse(VST&);

};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e,pred,this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T>
void List<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header -> succ = trailer;
	header -> pred = NULL;
	trailer -> pred = header;
	trailer -> succ = NULL;
	_size = 0;//��¼��ģ
}
template <typename T>
T& List<T>::operator[]( Rank r) const {
	ListNodePosi(T) p = first();
	while(0 < r--) p = p->succ;
	return p->data;
}

template <typename T> //�������б��ڽ��p ��������trailer����n�����棩ǰ���У��ҵ�����e�������
ListNodePosi(T) List<T>::find ( T const& e, int n, ListNodePosi(T) p ) const {
	while(0 < n--)
		if(e == (p = p->pred)->data) return p; //��һ�Աȣ������򷵻ظý��
	return NULL ;  // ���򷵻ؿ�
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst( T const& e) {
	_size++;
	return header->insertAsSucc(e); //e�����׽�����
}


template <typename T>
ListNodePosi(T) List<T>::insertAsLast( T const& e) {
	_size++;
	return trailer->insertAsPred(e); //e����β������
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p , T const& e) {
	_size++;
	return p->insertAsPred(e); //e����p��ǰ������
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p , T const& e) {
	_size++;
	return p->insertAsSucc(e); //e����p�ĺ�̲���
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
	//ɾ���Ϸ�λ��p���Ľ�㣬����������ֵ
	T e = p->data; //����ɾ��������ֵ
	p->pred->succ = p->succ ; // ���
	p->succ->pred = p->pred; // ǰ��
	delete p; //ɾ�����
	_size--;
	return e;
}

template <typename T>
int List<T>::deduplicate() {
	//�޳������б��е��ظ����
	if(_size < 2) return 0; //ƽ���б���Ȼ���ظ�
	int oldside = _size ;
	ListNodePosi(T) p = header ;
	Rank r = 0; //p ���׽�㿪ʼ
	while(trailer != (p = p->succ)) { //����ֱ��ĩ���
		ListNodePosi(T) q = find(p->data ,r,p); //��p��r��ǰ���в�����ͬ��
		q ? remove(q):r++; //����ȷ���ڣ�ɾ���������ȼ�һ
	}
	return oldside - _size ; //����ɾ���Ľڵ���
}

template <typename T>
void List<T>::traverse(void (*visit)(T&)) {
	//���ú���ָ����Ƶı���
	for(ListNodePosi(T) p = header->succ ; p != trailer ; p = p->succ )
		visit(p->data);
}

template <typename T> template <typename VST> // Ԫ�����ͣ�������
void List<T>::traverse(VST& visit) { //���ú����������ʵı���
	for(ListNodePosi(T) p = header->succ; p != trailer ; p = p->succ)
		visit(p->data);
}

template <typename T>
int List<T>::uniquify() {
	//�����޳��ظ�Ԫ�أ�Ч�ʸ���
	if(_size < 2) return 0; //ƽ���б���Ȼ���ظ�
	int oldside = _size;
	ListNodePosi(T) p ;
	ListNodePosi(T) q; //����ָ����ڵĸ��Խڵ�
	for(p = header ,q = p->succ ; q != trailer ; p = q ,q = q->succ) { // ��������ɨ��
		if(p->data == q->data) {
			remove(q);    //��pq��ͬ��ɾ������
			q = p ;
		}
	}
	return (oldside-_size);
}

template <typename T> //�����б��ڽ��p ��n��ǰ���У��ҵ�������e������ߣ�������ȣ�
ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) {
	while(0 <= n--)
		if(((p = p->pred)->data) <= e) break;
	return p;
}

template <typename T> //��������
void List<T>::insertionSort(ListNodePosi(T) p ,int n) {
	for(int r = 0 ; r < n ; r++) {
		insertAfter(search(p->data ,r , p) , p->data);
		p = p->succ ;
		remove(p->pred);
	}
}


template <typename T> //������ʼp��n�����������
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p ,int n) {
	ListNodePosi(T) max = p ;
	for(ListNodePosi(T) cur = p ; 1 < n  ; n--)
		if((cur = cur->succ)->data  >= max->data)
			max = cur;
	return max;
}

template <typename T> //ѡ������
void List<T>::selectionSort(ListNodePosi(T) p ,int n) {
	ListNodePosi(T) head = p->pred ;
	ListNodePosi(T) tail = p;
	for(int i = 0 ; i < n ; i++) tail = tail->succ;
	while(1 < n ) { //�����ٻ�ʣ�������֮ǰѭ��
		ListNodePosi(T) max = selectMax(head->succ ,n); //�ҳ������
		insertBefore(tail ,remove(max)); //�����ƶ���tail ��ĩβ
		tail = tail->pred;
		n--;
	}
}

template <typename T> //�鲢�㷨
void List<T>::merge(ListNodePosi(T)& p, int n , List<T>& L, ListNodePosi(T) q, int m) {
	//��p���n��Ԫ�أ���q���m��Ԫ�ع鲢
	ListNodePosi(T) pp = p->pred;
	while(0 < m) {
		if((0 < n) && (p->data <= q->data)) {
			if (q == (p = p->succ)) break ;
			n--;
		} else {
			insertBefore(p,L.remove((q = q->succ)->pred));
			m--;
		}
	}
	p = pp->succ;
}

template <typename T> //�鲢����
void List<T>::mergeSort(ListNodePosi(T)& p , int n) {
	if(n < 2) return;
	int m = n>>1;
	ListNodePosi(T) q = p ;
	for(int i = 0 ; i < m ; i++) q = q->succ;
	mergeSort(p,m);
	mergeSort(q,n-m);
	merge(p,m,*this , q , n-m);
}


template <typename T>
List<T>::~List() {
	clear();
	delete header;
	delete trailer;
}
template <typename T>
int List<T>::clear() {
	int oldSize = _size;
	while(0<_size)
		remove(header->succ);
	return oldSize;
}
#endif



