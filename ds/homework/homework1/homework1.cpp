//���� 
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex.h"
#include "../../vector/vector.h"
using namespace std;
 
int main(){
	Complex A[10];
	cout << "�����������������" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();//����Ļ����ʾ 
    }//���ɸ��� 
    cout << endl;
    Vector<Complex>v(A, 10);
//    //______________________________________________
//    int n;
//    n = v.disordered();//��������� 
//    cout << "������Ϊ" << n << endl;
//    //getchar();
//    v.bubbleSort(0,10); 
//    n = v.disordered();
//    cout << "�����" <<endl;
//    for (int j = 0; j < 10; j++){
//	   v._elem[j].display();
//    }
//    cout<<endl;
//    cout << "������Ϊ" << n << endl;
//    //getchar();
//    //________________________________________________________���� 
	//����
	v.unsort(0,10);
	cout << "���Һ�" << endl;
	for(int i=0;i<10;i++)
		v[i].display();
	
	//����
	cout<<endl<<"����"<<endl;
	int c;
	c = v.find(A[8]);
	cout<<"A[8]��ʱ��λ��Ϊ"<<c<<endl;
	//����
	cout<<"�����"<<endl;
	v.insert(10, A[4]);
	for(int i=0;i<11;i++)
		v[i].display(); 
	cout<<endl;
 	cout<<"ɾ��8��"<<endl;
	//ɾ��
	v.remove(8);
	for(int i=0;i<10;i++)
		v[i].display();
	cout<<endl;
	cout<<"Ψһ��"<<endl;
	//Ψһ��
	c = v.deduplicate();
	cout << "�ظ������ĸ���Ϊ" << c << endl <<"Ψһ����"<< endl;
	for(int i=0;i<9;i++)
		v[i].display();
	
	 
}

 

