#ifndef GRAPH
#define GRAPH
#include "Stack.h"
#include "List.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边状态

template <typename Tv, typename Te> //顶点类型、边类型
class Graph { //图Graph模板类
	private:
		void reset() {
			//全部顶点、边的辅助信息复位
			for (int i = 0; i < n; i++) { //全部顶点的
				status(i) = UNDISCOVERED;
				dTime(i) = fTime(i) = -1; //状态，时间标签
				parent(i) = -1;
				priority(i) = INT_MAX; //（在遍历树中的）父节点，优先级数
				for (int j = 0; j < n; j++) //全部边的
					if (exists(i, j))
						type(i, j) = UNDETERMINED; //状态
			}
		}
		void BFS(int, int&); //（连通域）广度优先搜索算法
		void DFS(int, int&); //（连通域）深度优先搜索算法
		void BCC(int, int&, Stack<int>&); //（连通域）基于DFS的双连通分量分解算法
		bool TSort(int, int&, Stack<Tv>*); //（连通域）基于DFS的拓扑排序算法
		template <typename PU> void PFS(int, PU); //（连通域）优先级搜索框架
	public:
// 顶点
		int n; //顶点总数
		virtual int insert(Tv const &) = 0; //插入顶点，返回编号
		virtual Tv remove(int) = 0; //删除顶点及其关联边，返回该顶点信息
		virtual Tv& vertex(int) = 0; //顶点v的数据（该顶点的确存在）
		virtual int inDegree(int) = 0; //顶点v的入度（该顶点的确存在）
		virtual int outDegree(int) = 0; //顶点v的出度（该顶点的确存在）
		virtual int firstNbr(int) = 0; //顶点v的首个邻接顶点
		virtual int nextNbr(int, int) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
		virtual VStatus& status(int) = 0; //顶点v的状态
		virtual int& dTime(int) = 0; //顶点v的时间标签dTime
		virtual int& fTime(int) = 0; //顶点v的时间标签fTime
		virtual int& parent(int) = 0; //顶点v在遍历树中的父亲
		virtual int& priority(int) = 0; //顶点v在遍历树中的优先级数
// 边：这里约定。无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
		int e; //边总数
		virtual bool exists(int, int) = 0; //边(v, u)是否存在
		virtual void insert(Te const &, int, int, int) = 0; //在顶点v和u之间插入权重为w的边e
		virtual Te remove(int, int) = 0; //删除顶点v和u之间的边e，返回该边信息
		virtual EType& type(int, int) = 0; //边(v, u)的状态
		virtual Te& edge(int, int) = 0; //边(v, u)的数据（该边的确存在）
		virtual int& weight(int, int) = 0; //边(v, u)的权重
// 算法
		void bfs(int); //广度优先搜索算法
		void dfs(int); //深度优先搜索算法
		void bcc(int); //基于DFS的双连通分量分解算法
		Stack<Tv>* tSort(int); //基于DFS的拓扑排序算法
		void prim(int); //最小支撑树Prim算法
		void dijkstra(int); //最短路径Dijkstra算法
		template <typename PU> void pfs(int, PU); //优先级搜索框架
};


template <typename Tv, typename Te>
void Graph<Tv,Te>::bfs(int s) {
	reset();
	int clock = 0;
	int v = s;
	do
		if(UNDISCOVERED == status(v))
			BFS(v,clock);
	while(s!=(v = (++v%n))) ;

}


template <typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v, int& clock) {
	List<int> Q;
	status(v) = DISCOVERED;
	Q.insertAsLast(v);
	while(!Q.empty()) {
		int v = Q.dequeue2();
		dTime(v) = ++clock;
		for(int u = firstNbr(v); -1<u; u = nextNbr(v,u))
			if(UNDISCOVERED == status(u)) {
				status(u) == DISCOVERED;
				Q.insertAsLast(u);
				type(v,u) = TREE;
				parent(u) = v;
				cout<<"->"<<u;

			} else {
				type(v,u) = CROSS;

			}

		status(v) = VISITED;
	}
	cout<<"访问完毕"<<endl;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s) {
	reset();
	int clock=0;
	int v=s;
	do { //逐一检查所有顶点，一旦遇到尚未发现的顶点
		if(UNDISCOVERED==status(v))
			DFS(v,clock);//即从该顶点出发启动一次DFS
	} while(s != (v = (++v%n) ) ); //按序号访问
	cout<<endl;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int & clock) {
	dTime(v)=++clock;
	status(v)=DISCOVERED;//发现当前顶点
	for(int u=firstNbr(v); -1<u; u=nextNbr(v,u)) { //考察每一邻居，注意是要等邻居都遍历完毕才转交控制权
		switch(status(u)) {
			case UNDISCOVERED://u尚未被发现，意味着支撑树可在此发展
				type(v,u)=TREE;
				parent(u)=v;
				DFS(u,clock);//递归
				cout<<"->"<<u;
				break;
			case DISCOVERED:
				type(v,u)=BACKWARD;//回向边 （后代指向祖先）
				break;
			default://看u和v谁更早被发现，分为前向边（祖先指向后代）或者跨边 (两个顶点之间没有祖先或者直系后代的血缘关系 )
				type(v,u)=dTime(v)<dTime(u)?FORWARD:CROSS;
				break;
		}
	}

	status(v)=VISITED;//至此，当前顶点访问完毕
	fTime(v)=++clock;//节点被访问完毕的时刻
}


template <typename Tv, typename Te> //基于DFS的拓扑排序算法
Stack<Tv>* Graph<Tv, Te>::tSort ( int s ) { //assert: 0 <= s < n
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>; //用栈记录排序顶点
	do {
		if ( UNDISCOVERED == status ( v ) )
			if ( !TSort ( v, clock, S ) ) { //clock并非必需
				while ( !S->empty() ) //任一连通域（亦即整图）非DAG
					S->pop();
				break; //则不必继续计算，故直接返回
			}
	} while ( s != ( v = ( ++v % n ) ) );
	return S; //若输入为DAG，则S内各顶点自顶向底排序；否则（不存在拓扑排序），S空
}

template <typename Tv, typename Te> //基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort ( int v, int& clock, Stack<Tv>* S ) { //assert: 0 <= v < n
	dTime ( v ) = ++clock;
	status ( v ) = DISCOVERED; //发现顶点v
	for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
		switch ( status ( u ) ) { //并视u的状态分别处理
			case UNDISCOVERED:
				parent ( u ) = v;
				type ( v, u ) = TREE;
				if ( !TSort ( u, clock, S ) ) //从顶点u处出发深入搜索
					return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
				break;
			case DISCOVERED:
				type ( v, u ) = BACKWARD; //一旦发现后向边（非DAG），则
				return false; //不必深入，故返回并报告
			default: //VISITED (digraphs only)
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
				break;
		}
	status ( v ) = VISITED;
	S->push ( vertex ( v ) ); //顶点被标记为VISITED时，随即入栈
	return true; //v及其后代可以拓扑排序
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s) {
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do
		if(UNDISCOVERED == status(v)) {
			BCC(v,clock,S);
			S.pop();
		}
	while(s!=(v=(++v%n)));

}
#define hca(x) (fTime(x))

template <typename Tv, typename Te>
void Graph<Tv,Te>::BCC(int v,int& clock,Stack<int>& S) {
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u))
		switch(status(u)) {
			case UNDISCOVERED:
				parent(u) = v;
				type(v,u) = TREE;
				BCC(u,clock,S);
				if(hca(u)<dTime(v))
					hca(v) = min(hca(v),hca(u));
				else {
					while(v!=S.pop());
					S.push(v);
				}
				break;
			case DISCOVERED:
				type(v,u) = BACKWARD;
				if(u!=parent(v))
					hca(v) = min(hca(v),dTime(u));
				break;
			default:
				type(v,u) = (dTime(v) < dTime(u))?FORWARD:CROSS;
				break;
		}
	status(v) = VISITED;
}
#undef hca


//遍历所有顶点，如果没有访问过就依次进行PFS，得到多棵不相干的遍历树
//主要是为了搜索所有顶点，防止遗漏连通域
template <typename Tv, typename Te> template <typename PU> //优先级搜索（全图）
void Graph<Tv, Te>::pfs ( Rank s, PU prioUpdater ) { //s < n
	reset();
	Rank v = s; //初始化
	do //逐一检查所有顶点
		if ( UNDISCOVERED == status ( v ) ) //一旦遇到尚未发现的顶点
			PFS ( v, prioUpdater ); //即从该顶点出发启动一次PFS
	while ( s != ( v = ( ( ++v ) % n ) ) ); //按序号检查，故不漏不重
}

template <typename Tv, typename Te> template <typename PU> //顶点类型、边类型、优先级更新器
void Graph<Tv, Te>::PFS ( Rank s, PU prioUpdater ) { //优先级搜索（单个连通域）
	priority ( s ) = 0;
	status ( s ) = VISITED;
	parent ( s ) = -1; //初始化，起点v加至PFS树中
	while ( 1 ) { //将下一顶点和边加至PFS树中
		for ( Rank w = firstNbr ( s ); -1 < w; w = nextNbr ( s, w ) ) //对v的每一个邻居u
			prioUpdater ( this, s, w ); //更新其优先级及其父亲
		for ( int shortest = INT_MAX, w = 0; w < n; w++ )
			if ( UNDISCOVERED == status ( w ) ) //从尚未加入遍历树的顶点中
				if ( shortest > priority ( w ) ) { //选出下一个
					shortest = priority ( w );    //优先级最高的顶点v
					s = w;
				}
		if ( VISITED == status ( s ) ) break; //直至所有顶点均已加入
		status ( s ) = VISITED;
		type ( parent ( s ), s ) = TREE; //将v及与其父的联边加入遍历树
	}
} //通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能

//prim MST
template <typename Tv, typename Te> //Prim算法：无向连通图，各边表示为方向互逆、权重相等的一对边
void Graph<Tv, Te>::prim ( Rank s ) { //s < n
	reset();
	priority ( s ) = 0;
	for ( int i = 0; i < n; i++ ) { //共需引入n个顶点和n-1条边
		status ( s ) = VISITED;
		if ( -1 < parent ( s ) ) type ( parent ( s ), s ) = TREE; //引入当前的s
		for ( Rank j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) ) //枚举s的所有邻居j
			if ( ( status ( j ) == UNDISCOVERED ) && ( priority ( j ) > weight ( s, j ) ) ) { //对邻接顶点j做松弛
				priority ( j ) = weight ( s, j );    //与Dijkstra算法唯一的不同之处
				parent ( j ) = s;
			}
		for ( int shortest = INT_MAX, j = 0; j < n; j++ ) //选出下一极短跨边
			if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) ) {
				shortest = priority ( j );
				s = j;
			}
	}
}
template <typename Tv, typename Te> struct PrimPU { //针对Prim算法的顶点优先级更新器
	virtual void operator() ( Graph<Tv, Te>* g, Rank v, Rank u ) {
		if ( UNDISCOVERED == g->status ( u ) ) //对于v每一尚未被发现的邻接顶点u
			if ( g->priority ( u ) > g->weight ( v, u ) ) { //按Prim策略做松弛
				g->priority ( u ) = g->weight ( v, u ); //更新优先级（数）
				g->parent ( u ) = v; //更新父节点
			}
	}
};
template <typename Tv, typename Te> struct DijkstraPU { //针对Dijkstra算法的顶点优先级更新器
	virtual void operator() ( Graph<Tv, Te>* g, Rank uk, Rank v ) {
		if ( UNDISCOVERED == g->status ( v ) ) //对于v每一尚未被发现的邻接顶点u，按Dijkstra策略
			if ( g->priority ( v ) > g->priority ( uk ) + g->weight ( uk, v ) ) { //做松弛
				g->priority ( v ) = g->priority ( uk ) + g->weight ( uk, v ); //更新优先级（数）
				g->parent ( v ) = uk; //并同时更新父节点
			}
	}
};
template <typename Tv, typename Te> //最短路径Dijkstra算法：适用于一般的有向图
void Graph<Tv, Te>::dijkstra ( Rank s ) { //s < n
	reset();
	priority ( s ) = 0;
	for ( int i = 0; i < n; i++ ) { //共需引入n个顶点和n-1条边
		status ( s ) = VISITED;
		if ( -1 < parent ( s ) ) type ( parent ( s ), s ) = TREE; //引入当前的s
		for ( Rank j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) ) //枚举s的所有邻居j
			if ( ( status ( j ) == UNDISCOVERED ) && ( priority ( j ) > priority ( s ) + weight ( s, j ) ) ) { //对邻接顶点j做松弛
				priority ( j ) = priority ( s ) + weight ( s, j );    //与Prim算法唯一的不同之处
				parent ( j ) = s;
			}
		for ( int shortest = INT_MAX, j = 0; j < n; j++ ) //选出下一最近顶点
			if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) ) {
				shortest = priority ( j );
				s = j;
			}
	}
} //对于无向连通图，假设每一条边表示为方向互逆、权重相等的一对边
#endif
