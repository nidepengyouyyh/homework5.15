#ifndef GRAPH
#define GRAPH
#include "Stack.h"
#include "List.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //��״̬

template <typename Tv, typename Te> //�������͡�������
class Graph { //ͼGraphģ����
	private:
		void reset() {
			//ȫ�����㡢�ߵĸ�����Ϣ��λ
			for (int i = 0; i < n; i++) { //ȫ�������
				status(i) = UNDISCOVERED;
				dTime(i) = fTime(i) = -1; //״̬��ʱ���ǩ
				parent(i) = -1;
				priority(i) = INT_MAX; //���ڱ������еģ����ڵ㣬���ȼ���
				for (int j = 0; j < n; j++) //ȫ���ߵ�
					if (exists(i, j))
						type(i, j) = UNDETERMINED; //״̬
			}
		}
		void BFS(int, int&); //����ͨ�򣩹�����������㷨
		void DFS(int, int&); //����ͨ��������������㷨
		void BCC(int, int&, Stack<int>&); //����ͨ�򣩻���DFS��˫��ͨ�����ֽ��㷨
		bool TSort(int, int&, Stack<Tv>*); //����ͨ�򣩻���DFS�����������㷨
		template <typename PU> void PFS(int, PU); //����ͨ�����ȼ��������
	public:
// ����
		int n; //��������
		virtual int insert(Tv const &) = 0; //���붥�㣬���ر��
		virtual Tv remove(int) = 0; //ɾ�����㼰������ߣ����ظö�����Ϣ
		virtual Tv& vertex(int) = 0; //����v�����ݣ��ö����ȷ���ڣ�
		virtual int inDegree(int) = 0; //����v����ȣ��ö����ȷ���ڣ�
		virtual int outDegree(int) = 0; //����v�ĳ��ȣ��ö����ȷ���ڣ�
		virtual int firstNbr(int) = 0; //����v���׸��ڽӶ���
		virtual int nextNbr(int, int) = 0; //����v�ģ�����ڶ���j�ģ���һ�ڽӶ���
		virtual VStatus& status(int) = 0; //����v��״̬
		virtual int& dTime(int) = 0; //����v��ʱ���ǩdTime
		virtual int& fTime(int) = 0; //����v��ʱ���ǩfTime
		virtual int& parent(int) = 0; //����v�ڱ������еĸ���
		virtual int& priority(int) = 0; //����v�ڱ������е����ȼ���
// �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
		int e; //������
		virtual bool exists(int, int) = 0; //��(v, u)�Ƿ����
		virtual void insert(Te const &, int, int, int) = 0; //�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
		virtual Te remove(int, int) = 0; //ɾ������v��u֮��ı�e�����ظñ���Ϣ
		virtual EType& type(int, int) = 0; //��(v, u)��״̬
		virtual Te& edge(int, int) = 0; //��(v, u)�����ݣ��ñߵ�ȷ���ڣ�
		virtual int& weight(int, int) = 0; //��(v, u)��Ȩ��
// �㷨
		void bfs(int); //������������㷨
		void dfs(int); //������������㷨
		void bcc(int); //����DFS��˫��ͨ�����ֽ��㷨
		Stack<Tv>* tSort(int); //����DFS�����������㷨
		void prim(int); //��С֧����Prim�㷨
		void dijkstra(int); //���·��Dijkstra�㷨
		template <typename PU> void pfs(int, PU); //���ȼ��������
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
	cout<<"�������"<<endl;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s) {
	reset();
	int clock=0;
	int v=s;
	do { //��һ������ж��㣬һ��������δ���ֵĶ���
		if(UNDISCOVERED==status(v))
			DFS(v,clock);//���Ӹö����������һ��DFS
	} while(s != (v = (++v%n) ) ); //����ŷ���
	cout<<endl;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int & clock) {
	dTime(v)=++clock;
	status(v)=DISCOVERED;//���ֵ�ǰ����
	for(int u=firstNbr(v); -1<u; u=nextNbr(v,u)) { //����ÿһ�ھӣ�ע����Ҫ���ھӶ�������ϲ�ת������Ȩ
		switch(status(u)) {
			case UNDISCOVERED://u��δ�����֣���ζ��֧�������ڴ˷�չ
				type(v,u)=TREE;
				parent(u)=v;
				DFS(u,clock);//�ݹ�
				cout<<"->"<<u;
				break;
			case DISCOVERED:
				type(v,u)=BACKWARD;//����� �����ָ�����ȣ�
				break;
			default://��u��v˭���类���֣���Ϊǰ��ߣ�����ָ���������߿�� (��������֮��û�����Ȼ���ֱϵ�����ѪԵ��ϵ )
				type(v,u)=dTime(v)<dTime(u)?FORWARD:CROSS;
				break;
		}
	}

	status(v)=VISITED;//���ˣ���ǰ����������
	fTime(v)=++clock;//�ڵ㱻������ϵ�ʱ��
}


template <typename Tv, typename Te> //����DFS�����������㷨
Stack<Tv>* Graph<Tv, Te>::tSort ( int s ) { //assert: 0 <= s < n
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>; //��ջ��¼���򶥵�
	do {
		if ( UNDISCOVERED == status ( v ) )
			if ( !TSort ( v, clock, S ) ) { //clock���Ǳ���
				while ( !S->empty() ) //��һ��ͨ���༴��ͼ����DAG
					S->pop();
				break; //�򲻱ؼ������㣬��ֱ�ӷ���
			}
	} while ( s != ( v = ( ++v % n ) ) );
	return S; //������ΪDAG����S�ڸ������Զ�������򣻷��򣨲������������򣩣�S��
}

template <typename Tv, typename Te> //����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort ( int v, int& clock, Stack<Tv>* S ) { //assert: 0 <= v < n
	dTime ( v ) = ++clock;
	status ( v ) = DISCOVERED; //���ֶ���v
	for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //ö��v�������ھ�u
		switch ( status ( u ) ) { //����u��״̬�ֱ���
			case UNDISCOVERED:
				parent ( u ) = v;
				type ( v, u ) = TREE;
				if ( !TSort ( u, clock, S ) ) //�Ӷ���u��������������
					return false; //��u��������������������ȫͼ�����ˣ����ʷ��ز�����
				break;
			case DISCOVERED:
				type ( v, u ) = BACKWARD; //һ�����ֺ���ߣ���DAG������
				return false; //�������룬�ʷ��ز�����
			default: //VISITED (digraphs only)
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
				break;
		}
	status ( v ) = VISITED;
	S->push ( vertex ( v ) ); //���㱻���ΪVISITEDʱ���漴��ջ
	return true; //v������������������
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


//�������ж��㣬���û�з��ʹ������ν���PFS���õ���ò���ɵı�����
//��Ҫ��Ϊ���������ж��㣬��ֹ��©��ͨ��
template <typename Tv, typename Te> template <typename PU> //���ȼ�������ȫͼ��
void Graph<Tv, Te>::pfs ( Rank s, PU prioUpdater ) { //s < n
	reset();
	Rank v = s; //��ʼ��
	do //��һ������ж���
		if ( UNDISCOVERED == status ( v ) ) //һ��������δ���ֵĶ���
			PFS ( v, prioUpdater ); //���Ӹö����������һ��PFS
	while ( s != ( v = ( ( ++v ) % n ) ) ); //����ż�飬�ʲ�©����
}

template <typename Tv, typename Te> template <typename PU> //�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS ( Rank s, PU prioUpdater ) { //���ȼ�������������ͨ��
	priority ( s ) = 0;
	status ( s ) = VISITED;
	parent ( s ) = -1; //��ʼ�������v����PFS����
	while ( 1 ) { //����һ����ͱ߼���PFS����
		for ( Rank w = firstNbr ( s ); -1 < w; w = nextNbr ( s, w ) ) //��v��ÿһ���ھ�u
			prioUpdater ( this, s, w ); //���������ȼ����丸��
		for ( int shortest = INT_MAX, w = 0; w < n; w++ )
			if ( UNDISCOVERED == status ( w ) ) //����δ����������Ķ�����
				if ( shortest > priority ( w ) ) { //ѡ����һ��
					shortest = priority ( w );    //���ȼ���ߵĶ���v
					s = w;
				}
		if ( VISITED == status ( s ) ) break; //ֱ�����ж�����Ѽ���
		status ( s ) = VISITED;
		type ( parent ( s ), s ) = TREE; //��v�����丸�����߼��������
	}
} //ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

//prim MST
template <typename Tv, typename Te> //Prim�㷨��������ͨͼ�����߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
void Graph<Tv, Te>::prim ( Rank s ) { //s < n
	reset();
	priority ( s ) = 0;
	for ( int i = 0; i < n; i++ ) { //��������n�������n-1����
		status ( s ) = VISITED;
		if ( -1 < parent ( s ) ) type ( parent ( s ), s ) = TREE; //���뵱ǰ��s
		for ( Rank j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) ) //ö��s�������ھ�j
			if ( ( status ( j ) == UNDISCOVERED ) && ( priority ( j ) > weight ( s, j ) ) ) { //���ڽӶ���j���ɳ�
				priority ( j ) = weight ( s, j );    //��Dijkstra�㷨Ψһ�Ĳ�֮ͬ��
				parent ( j ) = s;
			}
		for ( int shortest = INT_MAX, j = 0; j < n; j++ ) //ѡ����һ���̿��
			if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) ) {
				shortest = priority ( j );
				s = j;
			}
	}
}
template <typename Tv, typename Te> struct PrimPU { //���Prim�㷨�Ķ������ȼ�������
	virtual void operator() ( Graph<Tv, Te>* g, Rank v, Rank u ) {
		if ( UNDISCOVERED == g->status ( u ) ) //����vÿһ��δ�����ֵ��ڽӶ���u
			if ( g->priority ( u ) > g->weight ( v, u ) ) { //��Prim�������ɳ�
				g->priority ( u ) = g->weight ( v, u ); //�������ȼ�������
				g->parent ( u ) = v; //���¸��ڵ�
			}
	}
};
template <typename Tv, typename Te> struct DijkstraPU { //���Dijkstra�㷨�Ķ������ȼ�������
	virtual void operator() ( Graph<Tv, Te>* g, Rank uk, Rank v ) {
		if ( UNDISCOVERED == g->status ( v ) ) //����vÿһ��δ�����ֵ��ڽӶ���u����Dijkstra����
			if ( g->priority ( v ) > g->priority ( uk ) + g->weight ( uk, v ) ) { //���ɳ�
				g->priority ( v ) = g->priority ( uk ) + g->weight ( uk, v ); //�������ȼ�������
				g->parent ( v ) = uk; //��ͬʱ���¸��ڵ�
			}
	}
};
template <typename Tv, typename Te> //���·��Dijkstra�㷨��������һ�������ͼ
void Graph<Tv, Te>::dijkstra ( Rank s ) { //s < n
	reset();
	priority ( s ) = 0;
	for ( int i = 0; i < n; i++ ) { //��������n�������n-1����
		status ( s ) = VISITED;
		if ( -1 < parent ( s ) ) type ( parent ( s ), s ) = TREE; //���뵱ǰ��s
		for ( Rank j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) ) //ö��s�������ھ�j
			if ( ( status ( j ) == UNDISCOVERED ) && ( priority ( j ) > priority ( s ) + weight ( s, j ) ) ) { //���ڽӶ���j���ɳ�
				priority ( j ) = priority ( s ) + weight ( s, j );    //��Prim�㷨Ψһ�Ĳ�֮ͬ��
				parent ( j ) = s;
			}
		for ( int shortest = INT_MAX, j = 0; j < n; j++ ) //ѡ����һ�������
			if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) ) {
				shortest = priority ( j );
				s = j;
			}
	}
} //����������ͨͼ������ÿһ���߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
#endif
