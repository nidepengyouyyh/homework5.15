//排序 
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
	cout << "随机生成无序向量" <<endl; 
	for (int j = 0; j < 100; j++){
	   A[j]=(rand() % 2000 / 10.0);
	   B[j]=(rand() % 2000 / 10.0);
   	   C[j]=(rand() % 2000 / 10.0);
	   D[j]=(rand() % 2000 / 10.0);
	   E[j]=(rand() % 2000 / 10.0);
	   F[j]=(rand() % 2000 / 10.0);
    }//生成
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
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout << "100个数据经过选择排后" <<endl;
    for (int j = 0; j < 100; j++){
	   cout<<v[j]<<" ";
    }
    cout<<endl;
    cout<<"乱序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序归并执行时间："<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序插入执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序选择执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序快排执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序堆排序执行时间："<<time*1000<<"ms"<<endl;
                
    cout<<"__________________________"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
//    cout << "起泡排序后" <<endl;
//    for (int j = 0; j < 100; j++){
//	   cout<<v[j]<<" ";
//    }
    cout<<endl;
    cout<<"有序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"有序归并执行时间："<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"有序插入执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"有序选择执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"有序快排执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"有序堆排序执行时间："<<time*1000<<"ms"<<endl;
        cout<<"__________________________"<<endl;
	v.bubbleSort(-1,0,100);
    v1.bubbleSort(-1,0,100);//倒序
    v2.bubbleSort(-1,0,100);
    v3.bubbleSort(-1,0,100);//倒序
   	v4.bubbleSort(-1,0,100);
    v5.bubbleSort(-1,0,100);//倒序
	 
     QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
//    cout << "起泡排序后" <<endl;
//    for (int j = 0; j < 100; j++){
//	   cout<<v[j]<<" ";
//    }
    cout<<endl;
    cout<<"倒序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"倒序归并执行时间："<<time*1000<<"ms"<<endl;
        
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.shellSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"倒序插入执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.selectSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"倒序选择执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.quickSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"倒序快排执行时间："<<time*1000<<"ms"<<endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.heapSort(0,100); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"倒序堆排序执行时间："<<time*1000<<"ms"<<endl;
	
    
}
