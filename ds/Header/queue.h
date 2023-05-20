#ifndef QUEUE
#define QUEUE

#include "List.h"
#include <stdlib.h>
using namespace std;


template <typename T> class Queue: public List<T> { //����ģ����
	public: //ԭ�нӿ�һ������
		void enqueue ( T const& e ) {
			this->insertAsLast ( e );    //��ӣ�β������
		}
		T dequeue() {
			return this->remove ( this->first() ); 
			//return remove ( first() );    //���ӣ��ײ�ɾ��
		}
		T& front() {
			return this->first()->data;    //����
		}
};
#endif

