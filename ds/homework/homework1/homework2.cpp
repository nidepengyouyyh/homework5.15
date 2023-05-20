//���� 
#include<windows.h> 
#include <ctime>
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../Header/Complex.h"
#include "../../Header/vector.h"
using namespace std;
int main()
{
	double time=0;  
    double counts=0;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;  
	Complex B[10];
	Complex A[10];
	cout << "�����������������" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();//����Ļ����ʾ 
    }//���ɸ��� 
    cout << endl;
    for(int i=0;i<10;i++)
    {
    	B[i].m_real=A[i].m_real;
    	B[i].m_imag=A[i].m_imag;
    	B[i].m_modulus=A[i].m_modulus;
	}
    Vector<Complex>v(A, 10);
    Vector<Complex>v1(B, 10);
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.quickSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout << "_____�����" <<endl;
    for (int j = 0; j < 10; j++){
	   v[j].display();
    }
    cout<<endl;
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;

    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
	v.bubbleSort(-1,0,10);
    v1.bubbleSort(-1,0,10);//����
	 
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
	
    
}
