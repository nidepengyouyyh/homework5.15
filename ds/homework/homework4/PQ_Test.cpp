#include "../../Header/PQ_ComplHeap.h"
#include <iostream>
using namespace std;
int main(){
    int A[] = { 4, 2, 5, 1, 3};
    //���Խ��Ѻ���
	cout<<"���������:"<<endl; 
	for(int i=0;i<5;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
    PQ_ComplHeap<int> a (A, 5);
    //����getMax
    cout <<"����getMax:"<<endl;
	cout <<"�õ������ֵΪ"<< a.getMax() << endl;//5
    //����insert
    a.insert( 6 );
    //����delMax
    cout <<"����delMax:"<<endl;
	cout <<"ɾ�������ֵΪ"<< a.delMax() << endl;//6
    cout <<"��ʱ���ֵΪ"<< a.getMax() << endl;//5

    //���Զ�����
    Vector<int> vec(A, 5);
    vec.heapSort( 0, 5);
    cout<<"���Զ�����:"<<endl;
    for( int i= 0; i<5; ++i )
        cout << vec[i] << " ";//1 2 3 4 5 
    
}

