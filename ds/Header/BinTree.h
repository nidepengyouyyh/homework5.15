#include "BinNode.h" //���ö��������ģ����
#include "Stack.h"
#include "queue.h"

template <typename T> class BinTree {
	protected:
		int _size; //��ģ
		BinNodePosi(T) _root; //���ڵ�
		virtual int updateHeight(BinNodePosi(T) x); //���µ�ǰ�ڵ�߶�
		void updateHeightAbove(BinNodePosi(T) x); //�����������Ƚڵ�߶�
	public:
		/*--��������������--*/
		BinTree(): _size(0), _root(NULL) {}
		~BinTree() {
			if (_size > 0) remove(_root);
		}
		/*--���ýӿ�--*/
		int size() const {
			return _size;    //��ģ
		}
		bool empty() const {
			return !_root;    //�п�
		}
		
		BinNodePosi(T) root() const {
			return _root;    //ȡ��
		}
		
		BinNodePosi(T)  insertAsRoot(T const &e); //������ڵ�
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e); //��Ϊ���ӽڵ����
		BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e); //��Ϊ�Һ��ӽڵ����
		BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S); //��Ϊ����������
		BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S); //��Ϊ����������
		int remove(BinNodePosi(T) x); //ɾ����x�ڵ�Ϊ������������������ԭ�ȵĹ�ģ
		BinTree<T>* secede(BinNodePosi(T) x); //ɾ��������������ת��Ϊ��������
		/*--�����ӿ�--*/
		template <typename VST>
		void travLevel(VST&visit) { //��α���
			if (_root) _root->travLevel(visit);
		}

		template <typename VST>
		void travPre(VST&visit) { //�������
			if (_root) _root->travPre(visit);
		}

		template <typename VST>
		void travIn(VST&visit) { //�������
			if (_root) _root->travIn(visit);
		}

		template <typename VST>
		void travPost(VST&visit) { //�������
			if (_root) _root->travPost(visit);
		}

		/*--�ж������Ƚ���--*/

		bool operator>(BinTree<T> const& t) {
			return _root && t._root && lt(_root, t._root);
		}

		bool operator<(BinTree<T> const& t) {
			return _root && t._root && lt(_root, t._root);
		}

		bool operator==(BinTree<T> const& t) {
			return _root && t._root && (_root == t._root);
		}

		bool operator!=(BinTree<T> const& t) {
			return _root && t._root && (_root != t._root);
		}

		bool operator>=(BinTree<T> const& t) {
			return _root && t._root && (_root >= t._root);
		}

		bool operator<=(BinTree<T> const& t) {
			return _root && t._root && (_root <= t._root);
		}

};

//����������������������������������������������������������������������������������
template <typename T> int BinTree<T>::updateHeight( BinNodePosi(T) x ) {
	return x->height = 1 + max( stature (x -> lc), stature (x -> rc));
}
template <typename T> void BinTree<T>::updateHeightAbove( BinNodePosi(T) x ) {
	while(x) {
		updateHeight (x);
		x = x->parent;
	}
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
	_size ++;    //���嵱�����ڵ����յĶ�����
	return _root = new BinNode<T>(e);
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e) {
	_size ++;    //�����Ϊ��������
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lchild;
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e) {
	_size ++;    //�����Ϊ�����Һ���
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rchild;
}

template <typename T>//��Ϊ������
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {//��������

	if ( x->lc = S->_root ) 
		x->lc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	//delete S;
	releases(S);
	S = NULL;
	return x;

}
template <typename T>//as right child tree
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) {
	if ( x->rc = S->_root ) 
		x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	delete S;
	//release(S);
	S = NULL;
	return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
//________________________________________________________warning!!!!!!!!!!!!!!!
template <typename T>
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) +  removeAt(x->rc);
	//releases(x->data);
	//releases(x);
	//delete x->data;
	delete x;
	return n;
}

template <typename T>//�������룬�����װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede ( BinNodePosi(T) x ) {
	FromParentTo( *x ) = NULL;
	updateHeightAbove( x->parent );
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

template <typename T, typename VST>//first
void travPre_R( BinNodePosi(T) x, VST& visit ) {
	if( !x ) return;
	visit( x->data );
	travPre_R( x->lc, visit);
	travPre_R( x->rc, visit);
}

template <typename T, typename VST>
void travPost_R( BinNodePosi(T) x, VST& visit) {//���� 
	if( !x ) return;
	travPost_R( x->lc, visit );
	travPost_R( x->rc, visit );
	visit( x->data );
}


template <typename T, typename VST>
void travIn_R( BinNodePosi(T) x, VST& visit) {//���� 
	if( !x ) return;
	travIn_R( x->lc, visit );
	visit( x->data );
	travIn_R( x->rc, visit );
}

template <typename T, typename VST>
static void visitAlongLeftBranch( BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S) {
	while( x ) {
		visit( x->data );
		S.push( x->rc );
		x = x->lc;
	}
}

template <typename T, typename VST>
void travPre_I2( BinNodePosi(T) x, VST& visit ) {
	Stack<BinNodePosi(T)> S;
	while(true) {
		visitAlongLeftBranch(x, visit, S);
		if( S.empty() ) break;
		x = S.pop();
	}
}


template <typename T>
static void goAlongLeftBranch( BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while( x ) {
		S.push( x );
		x = x->lc;
	}
}

template <typename T, typename VST>
void travIn_I1 (BinNodePosi(T) x, VST& visit)//������������� 
{
	Stack<BinNodePosi(T)> S;//support stack
	while( true )
	{
		goAlongLeftBranch( x, S );
		if( S.empty() ) break;
		x = S.pop();
		visit ( x->data );
		x = x->rc;
	}
}

template <typename T, typename VST>
void travIn_I2 (BinNodePosi(T) x, VST& visit)//������������� 
{
	Stack<BinNodePosi(T)> S;//support stack
	while( true )
	
		if( x ){
			S.push( x );
			x = x->lc;
		} else if( !S.empty() ){
			x = S.pop();
			visit( x->data );
			x = x->rc;
		} else 
			break;
	
}

template <typename T, typename VST>
void travIn_I3 (BinNodePosi(T) x, VST& visit)//������������� 
{
	bool backtrack = false;
	while( true )
		if( !backtrack && HasLChild( *x ) )
			x = x->lc;
		else{
			visit(x->data);
			if(HasRChild(*x)){
				x = x->rc;
				backtrack = false;
			}else{
				if(!(x = x->succ())) break;
				backtrack = true;
			}
		}
}


template <typename T>
static void gotoHLVFL (Stack<BinNodePosi(T)>& S) 
{
	while( BinNodePosi(T) x = S.top())
		if( HasLChild( *x )){
			if( HasRChild( *x ) ) S.push( x->rc );
			S.push( x->lc );
		} else
			S.push( x->rc );
	S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){
	Stack<BinNodePosi(T)> S;
	if( x ) S.push( x );
	while( !S.empty( ) ){
		if(S.top()!=x->parent)
			gotoHLVFL( S );
		x = S.pop(); visit( x-> data);
	}
}

template <typename T> template<typename VST>
void BinNode<T>::travLevel( VST& visit ){
	Queue<BinNodePosi(T)> Q;
	Q.enqueue( this );
	while( !Q.empty()){
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if(HasLChild (*x))
			Q.enqueue( x->lc );
		if(HasRChild(*x))
			Q.enqueue( x->rc );
	}
}




