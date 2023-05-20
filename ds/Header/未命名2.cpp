#include<bits/stdc++.h>

using namespace std;
#define max 50
//���ֱ���ͼ���㷨 

int a[max][max];	//�洢�� 
int n,k;	//�洢����ͱ�
int flag[max];	//�������
queue<int> qu;	//���Ѷ��� 
 
//������ȱ��� 
void dfs(int i){
	if(i>n){
		return;
	}
	else{
		for(int j=1;j<=n;j++){	//���ڶ���δ�ذ�����Ȼ������ 
			if(flag[j]==0&&a[i][j]==1){
				flag[j]=1;
				cout<<j<<" ";
				dfs(j);	//����Ҫ���� 
			} 
		}
	}
}

//������ȱ��� 
void bfs(int i){
	qu.push(i);
	flag[i]=1;
	while(!qu.empty()){
		int t=qu.front();
		cout<<t<<" ";
		qu.pop();
		for(int j=1;j<=n;j++){	//���ڶ���ȫ����ջ 
			if(flag[j]==0&&a[t][j]==1){
				flag[j]=1;
				qu.push(j);
			}
		}
	}
	
}

//������ 
int main(){
	cin>>n;
	cin>>k;
	
	memset(a,0,sizeof(a));	//��ʼ������
	int x=0;
	int y=0;
	
	//�����֮����Ϣ,Ĭ�϶���ֵΪ1~N 
	for(int i=1;i<=k;i++){
		cin>>x;
		cin>>y;
		a[x][y]=1;
		a[y][x]=1;
	} 
	
	cout<<"���ѣ�"<<endl;
	dfs(1);	//����1��ʼ
	cout<<endl;
	memset(flag,0,sizeof(flag));	//���³�ʼ��������� 
	
	cout<<"���ѣ�"<<endl;
	bfs(1);	//����2��ʼ 

	return 0;
} 

