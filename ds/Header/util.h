#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "rand.h"
#include <typeinfo>
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#if defined(DSA_DEBUG) //���뿪�أ����Ƶ������
#define DSA(x)  { x } //���
#else
#define DSA(x) //�����
#endif
