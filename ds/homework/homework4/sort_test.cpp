//���� 
#include<windows.h> 
#include <ctime>
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../Header/Complex.h"
#include "../../Header/vector.h"
#include "../../Header/PQ_ComplHeap.h"
using namespace std;
int main()
{
	double time=0;  
    double counts=0;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;  
	int B[100];
	int A[100];
	int C[100];
	int D[100];
	int E[100];
	int F[100];
	cout << "���������������" <<endl; 
	for (int j = 0; j < 100; j++){
	   A[j]=(rand() % 2000 / 10.0);
	   B[j]=(rand() % 2000 / 10.0);
   	   C[j]=(rand() % 2000 / 10.0);
	   D[j]=(rand() % 2000 / 10.0);
	   E[j]=(rand() % 2000 / 10.0);
	   F[j]=(rand() % 2000 / 10.0);
    }//����
    cout << endl;
    Vector<int>v(A, 100);
    Vector<int>v1(B, 100);
    Vector<int>v2(C, 100);
    Vector<int>v3(D, 100);
    Vector<int>v4(E, 100);
    Vector<int>v5(F, 100);
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout << "100�����ݾ���ѡ���ź�" <<endl;
    for (int j = 0; j < 100; j++){
	   cout<<v[j]<<" ";
    }
    cout<<endl;
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"���������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
                
    cout<<"__________________________"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
//    cout << "���������" <<endl;
//    for (int j = 0; j < 100; j++){
//	   cout<<v[j]<<" ";
//    }
    cout<<endl;
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"���������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        cout<<"__________________________"<<endl;
	v.bubbleSort(-1,0,100);
    v1.bubbleSort(-1,0,100);//����
    v2.bubbleSort(-1,0,100);
    v3.bubbleSort(-1,0,100);//����
   	v4.bubbleSort(-1,0,100);
    v5.bubbleSort(-1,0,100);//����
	 
     QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
//    cout << "���������" <<endl;
//    for (int j = 0; j < 100; j++){
//	   cout<<v[j]<<" ";
//    }
    cout<<endl;
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        cout<<"���������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
	
    
}
