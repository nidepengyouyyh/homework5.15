#ifndef QUEUE
#define QUEUE

#include "List.h"
#include <stdlib.h>
using namespace std;


template <typename T> class Queue: public List<T> { //队列模板类
	public: //原有接口一概沿用
		void enqueue ( T const& e ) {
			this->insertAsLast ( e );    //入队：尾部插入
		}
		T dequeue() {
			return this->remove ( this->first() ); 
			//return remove ( first() );    //出队：首部删除
		}
		T& front() {
			return this->first()->data;    //队首
		}
};
#endif

