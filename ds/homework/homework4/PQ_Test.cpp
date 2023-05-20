#include "../../Header/PQ_ComplHeap.h"
#include <iostream>
using namespace std;
int main(){
    int A[] = { 4, 2, 5, 1, 3};
    //测试建堆函数
	cout<<"构造堆如下:"<<endl; 
	for(int i=0;i<5;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
    PQ_ComplHeap<int> a (A, 5);
    //测试getMax
    cout <<"测试getMax:"<<endl;
	cout <<"得到的最大值为"<< a.getMax() << endl;//5
    //测试insert
    a.insert( 6 );
    //测试delMax
    cout <<"测试delMax:"<<endl;
	cout <<"删除的最大值为"<< a.delMax() << endl;//6
    cout <<"此时最大值为"<< a.getMax() << endl;//5

    //测试堆排序
    Vector<int> vec(A, 5);
    vec.heapSort( 0, 5);
    cout<<"测试堆排序:"<<endl;
    for( int i= 0; i<5; ++i )
        cout << vec[i] << " ";//1 2 3 4 5 
    
}

