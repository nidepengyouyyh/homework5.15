#include "Vector.h"
#include <iostream>
template<typename T>
struct SkipNode
{
	int key;
	T value;
	Vector<SkipNode*> next;

	SkipNode(int k, T v, int level);
};
//���캯������ʼ��
template<typename T> SkipNode<T>::SkipNode(int k, T v, int level) 
	: key(k), value(v)
{
	for (int i = 0; i < level; i++)
	{
		next.push_back(nullptr);
	}
}


template<class T>
class SkipList
{

public:
	//ͷ���
	SkipNode<T>* head;
	
	//�б�������
	int maxLevel;

	//���͵���Сֵ�����ֵ
	const int minInt = numeric_limits<int>::min();
	const int maxInt = numeric_limits<int>::max();

public:
	//���캯��
	SkipList(int maxLevel, T iniValue);

	//��������
	~SkipList();

	//�����������
	int randomLevel();

	//����, ���ң� ɾ��
	SkipNode<T>* insert(int k, T v);
	SkipNode<T>* find(int k);
	SkipNode<T>* deleteNode(int k);

	//��ӡ
	void printNode();

private:

	//β�ڵ�
	SkipNode<T>* tail;
	
	//�ҵ���ǰ�б����node��������
	int nodeLevel(Vector<SkipNode<T>*> p);
};

//��ʼ��
template<class T> SkipList<T>::SkipList(int maxLevel, T iniValue)
	: maxLevel(maxLevel)
{
	//��ʼ��ͷ����β�ڵ�Ϊ������Сֵ�����ֵ
	head = new SkipNode<T>(minInt, iniValue, maxLevel);
	tail = new SkipNode<T>(maxInt, iniValue, maxLevel);

	//���в����ϵ�ͷ���ָ��β�ڵ�
	for (int i = 0; i < maxLevel; i++)
	{
		head->next[i] = tail;
	}
}

template<class T> SkipList<T>::~SkipList()
{
	delete head;
	delete tail;
}

template<class T> int SkipList<T>::randomLevel()
{
	int random_level = 1;
	int seed = time(NULL);
	static default_random_engine e(seed);
	static uniform_int_distribution<int> u(0, 1);

	while (u(e) && random_level < maxLevel)
	{
		random_level++;
	}

	return random_level;
}
template<class T> int SkipList<T>::nodeLevel(vector<SkipNode<T>*> next)
{
	int node_level = 0;
	
	if (next[0]->key == maxInt)
	{
		return node_level;
	}

	for (int i = 0; i < next.size(); i++)
	{
		if (next[i] != nullptr && next[i]->key != maxInt)
		{
			node_level++;
		}
		else
		{
			break;
		}
	}
	return node_level;
}
/*���룺
1�������ò��Һ������жϸý���Ƿ��Ѿ����ڣ�������ڣ�����¸ý���ֵ
2����ȡ�½ڵ���������
3���ҵ����ʵĲ���λ��
4�����룬������ÿ��ǰ��node��ָ��*/
template<class T> SkipNode<T>* SkipList<T>::insert(int k, T v)
{
	int x_level = randomLevel();
	SkipNode<T>* new_node = nullptr;
	SkipNode<T>* tmp = head;

	new_node = find(k);

	if (new_node) {
		
		new_node->value = v;
		cout << "\nThis node " << k << " has already existed. And its value has been updated to " << v << endl;
		return head;
	}

	cout << "key: " << k << ", randomLevel: " << x_level << endl;

	new_node = new SkipNode<T>(k, v, x_level);

	for (int i = (x_level - 1); i > -1; i--)
	{
		while (tmp->next[i] != nullptr && tmp->next[i]->key < k)
		{
			tmp = tmp->next[i];
		}

		new_node->next[i] = tmp->next[i];
		tmp->next[i] = new_node;
	}

	return head;
}

/*���ң�
�����б����������ҵ�С�ڸý�������Ľ�㣬�����һ��������Ŀ���㣬�򷵻ظýڵ㡣
������ǣ��򷵻ؿ�*/
template<class T> SkipNode<T>* SkipList<T>::find(int x)
{
	SkipNode<T>* tmp = head;
	int current_level = nodeLevel(tmp->next);

	for (int i = (current_level - 1); i > -1; i--)
	{
		while (tmp->next[i] != nullptr && tmp->next[i]->key < x)
		{
			tmp = tmp->next[i];
		}
	}
	tmp = tmp->next[0];

	if (tmp->key == x)
	{
		cout << "\nThis key " << x << " has been found\n";
		return tmp;
	}
	else
	{
		//cout << " \nThis key " << x << " doesn't exit\n";
		return nullptr;
	}
}

/*ɾ����
1) �� find(x) �����жϸý���Ƿ����. ��������ڣ��򷵻ص�ǰlist, ����֪�ý�㲻���ڡ�
2) �ҵ�С�ڸý�������Ľ�㡣
3) ���ĸýڵ�ÿ���ǰ��Ľ���ָ�롣*/
template<class T> SkipNode<T>* SkipList<T>::deleteNode(int x)
{
	SkipNode<T>* node = find(x);
	if (!node)
	{
		cout << "\n This deleting node" << x << "doesn't exist" << endl;
		return head;
	}
	else
	{
		SkipNode<T>* tmp = head;
		int x_level = node->next.size();

		cout << "\nThe deleting node " << x << "'s level is " << x_level << endl;

		for (int i = (x_level - 1); i > -1; i--)
		{
			while (tmp->next[i] != nullptr && tmp->next[i]->key < x)
			{
				tmp = tmp->next[i];
			}
			tmp->next[i] = tmp->next[i]->next[i];

			cout << "This node " << x << " has been deleted from level " << i << endl;
		}

		return head;
	}
}
// �ֲ��ӡ
template<class T> void SkipList<T>::printNode()
{

	for (int i = 0; i < maxLevel; i++)
	{
		SkipNode<T>* tmp = head;
		int lineLen = 1;

		if (tmp->next[i]->key != maxInt)
		{
			cout << "\n";
			cout << "This is level " << i << ":" << endl;
			cout << "{";

			while (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
			{
				cout << "(" << "Key: " << tmp->next[i]->key << ", ";
				cout << "Value: " << tmp->next[i]->value << ")";

				tmp = tmp->next[i];

				if (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
				{
					cout << ", ";
				}

				if (lineLen++ % 5 == 0) cout << "\n";
			}
			cout << "}" << "\n";
		}
	}
}


