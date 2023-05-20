//BinNode ______________________________________________________________
#include<iostream>
#include <stdlib.h>
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p)?(p)->height:-1)//�ڵ�߶ȣ�������߶�Ϊ-1��Լ���໥ͳһ
typedef enum{RB_RED,RB_BLACK} RBColor;//�ڵ���ɫ
template <typename T>
struct BinNode {
	//��Ա
	T data;//��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;//���ڵ㣬������Ҷ���
	int height;
    int npl;//Null Path Length(��ʽ��Ҳ����height����)
    RBColor color;//��ɫ(�����)
	//���캯��
	BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0):
		data(e), parent(p), lc(lc), rc(rc), height(h) {}

	//�����ӿ�
	int size();//��ǰ�ڵ�������
	BinNodePosi(T) insertAsLc (T const&); //��Ϊ����������
	BinNodePosi(T) insertAsRc (T const&); //��Ϊ����������
	BinNodePosi(T) succ(); // ��ǰ�ڵ��ֱ�Ӻ��
	template<typename VST> void travLevel(VST&); //��α���
	template<typename VST> void travPre(VST&);   //�������
	template<typename VST> void travIn(VST&);    //�������
	template<typename VST> void travPOost(VST&); //�������
	//�Ƚ������е���
	bool operator < (BinNode const& bn){
		return data < bn.data;
	}
	bool operator > (BinNode const& bn){
		return data > bn.data;
	}
	bool operator <= (BinNode const& bn){
		return data <= bn.data;
	}
	bool operator >= (BinNode const& bn){
		return data >= bn.data;
	}
	bool operator == (BinNode const& bn){
		return data == bn.data;
	}
    bool operator!=(const BinNode& bn) {
	 	return data != bn.data; 
	}	//������
};
//��������������������������������������ݷ�ʽ���������������������������������������� 
 
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))	//����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))	//ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))
/************************************************************************************
*��BinNode�����ض���ϵ�Ľڵ㼰ָ��
*************************************************************************************/
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)	//�ֵ�
#define uncle(x) sibling((x)->parent)	//����
#define FromParentTo(x) /*���Ը��׵�����*/\
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))
 
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))	//�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsRed(p) (!IsBlack(p))	//�Ǻڼ���
#define BlackHeightUpdated(x) (/*RedBlack�߶ȸ�������*/ \
	(stature((x).lc)==stature((x).rc)) && \
	((x).height == (IsRed(&x)?stature((x).lc):stature((x).lc)+1)) \
)
//���������������������������������������������������������������������������������������������������� 


template <typename T> 
BinNodePosi(T) BinNode<T>::insertAsLc( T const& e)
{
	return lc = new BinNode( e, this);//left child
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(T const& e)
{//right child
	return rc = new BinNode(e, this);
}

 template <typename T> template <typename VST>//Ԫ�����Ͳ�����
 void BinNode<T>::travIn(VST& visit){//�������������ͳһ���
    //switch( rand() % 5)
	switch(4){
    case 1:travIn_I1(this,visit);break;
    case 2:travIn_I2(this,visit);break;
    case 3:travIn_I3(this,visit);break;
    case 4:travIn_I4(this,visit);break;
    default:travIn_R(this,visit);break;
    }
 }
template <typename T>
int BinNode<T>::size(){
	int s = 1;//���뱾��
	if (lc) s += lc->size();
	if (rc) s += rc->size();
	return s;
}

