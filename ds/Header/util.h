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

#if defined(DSA_DEBUG) //编译开关，控制调试输出
#define DSA(x)  { x } //输出
#else
#define DSA(x) //不输出
#endif
