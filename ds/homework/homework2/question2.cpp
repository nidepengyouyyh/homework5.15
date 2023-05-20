#include <iostream>
#include "../../Header/queue.h"
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define ll long long
using namespace std;
const int maxn=100001;
ll arr[maxn];
ll ans=0;//��ans��¼�����������
queue st;
void s(ll* arr,int n)
{
	ans=0;
    arr[n+1]=-1;
    for(int i=1;i<=n+1;++i)
    {
        if(st.isEmpty()||arr[st.getBack()]<=arr[i])
            st.push(i);
        else
        {
            int tmp;//������¼���������εĸ߶�
            while(st.getLength() && arr[st.getBack()]>arr[i])
            {
                tmp=st.getBack(); 
                ans=max(arr[st.getBack()]*(i-st.getBack()),ans);
                st.pop2();
            }
            st.push(tmp);
            arr[tmp]=arr[i];
        }
    }
    
    cout<<endl<<"���������Ϊ"<<ans<<endl;
}
int main()
{
	cout << "�������ʮ������:" <<endl; 
    ll n=10;
	for(int i=1;i<=n;++i)//�������105���� 
    {
		arr[i]=rand()%105;
		cout<<arr[i]<<" ";
    }
	s(arr,n);
	cout<<"�����������:"<<endl;
	cin>>n;
	cout<<"��������:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>arr[i];
	}
	s(arr,n);
    return 0;
}
