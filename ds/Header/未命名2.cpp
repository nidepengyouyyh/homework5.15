#include<bits/stdc++.h>

using namespace std;
#define max 50
//两种遍历图的算法 

int a[max][max];	//存储边 
int n,k;	//存储顶点和边
int flag[max];	//标记数组
queue<int> qu;	//广搜队列 
 
//深度优先遍历 
void dfs(int i){
	if(i>n){
		return;
	}
	else{
		for(int j=1;j<=n;j++){	//相邻顶点未必按照自然数访问 
			if(flag[j]==0&&a[i][j]==1){
				flag[j]=1;
				cout<<j<<" ";
				dfs(j);	//不需要回溯 
			} 
		}
	}
}

//广度优先遍历 
void bfs(int i){
	qu.push(i);
	flag[i]=1;
	while(!qu.empty()){
		int t=qu.front();
		cout<<t<<" ";
		qu.pop();
		for(int j=1;j<=n;j++){	//相邻顶点全部进栈 
			if(flag[j]==0&&a[t][j]==1){
				flag[j]=1;
				qu.push(j);
			}
		}
	}
	
}

//主函数 
int main(){
	cin>>n;
	cin>>k;
	
	memset(a,0,sizeof(a));	//初始化数组
	int x=0;
	int y=0;
	
	//输入边之间信息,默认顶点值为1~N 
	for(int i=1;i<=k;i++){
		cin>>x;
		cin>>y;
		a[x][y]=1;
		a[y][x]=1;
	} 
	
	cout<<"深搜："<<endl;
	dfs(1);	//顶点1开始
	cout<<endl;
	memset(flag,0,sizeof(flag));	//重新初始化标记数组 
	
	cout<<"广搜："<<endl;
	bfs(1);	//顶点2开始 

	return 0;
} 

