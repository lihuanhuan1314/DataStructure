#pragma once
#include<set>
#include<map>
enum Color
{
	RED,
	BLACK,
};
template<class K, class V>
struct Pair
{
	K _first;
	V _second;

	Pair<K,V>(const K&key, const V& value)
		:_first(key)
		, _second(value)
	{}
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	Color _color;
	RBTreeNode<K, V>(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _color(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
public:
	Pair<Node*,bool> Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return Pair<Node*, bool>(_root,true);
		}
		//先插入节点
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return Pair<Node*, bool>(cur, false);
			}
		}
		cur = new Node(key, value);
		Node* newNode = cur;
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//再调颜色
		while (cur != _root && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				//第一种情况，uncle存在且为红，进行变色处理
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//然后把grandfather当成cur，继续向上调整。
					cur = grandfather;
					parent = cur->_parent;
				}
				else  // uncle不存在/uncle存在为黑
				{
					//第三种情况,左右双旋   '<'-->'/'-->'/\'
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent,cur);
					}

					grandfather->_color = RED;
					parent->_color = BLACK;
					RotateR(grandfather);

					break;
				}
			}
			else //grandfather->_right == parent
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//右左双旋      '>'-->'\'-->'/\'
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}

					grandfather->_color = RED;
					parent->_color = BLACK;
					RotateL(grandfather);

					break;
				}
			}
		}
		_root->_color = BLACK;
		return Pair<Node*, bool>(newNode, true);
	}
	void InOrder()
	{
		if (_root == NULL)
			return;
		_InOrder(_root);
		cout << endl;
	}
	bool IsBalance()
	{
		if (_root == NULL ||(_root && _root->_color == RED))
			return false;
		//统计最左路径中黑色节点个数
		int k = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
			{
				++k;
			}
			cur = cur->_left;
		}
		int count = 0;
		return _IsBalance(_root,k,count);
	}
public:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _IsBalance(Node* root,const int k,int count)
	{
		if (root->_color == RED && root->_parent->_color == RED)
		{
			return false;
		}
		if (root->_color == BLACK)
		{
			++count;
		}
		if (root->_left == NULL&&root->_right == NULL)
		{
			if (k != count)
			{
				cout << "黑色节点个数不相等" << root->_key << endl;
				return false;
			}
			else
			{
				cout << "平衡" << endl;
				return true;
			}
		}
		return _IsBalance(root->_left, k,count);
		return _IsBalance(root->_right, k, count);
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
		}
		subR->_parent = ppNode;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
		}
		subL->_parent = ppNode;
	}
protected:
	Node* _root;
};

void TestInsert()
{
	int arr[] = {16,3,7};
	RBTree<int, int> rb;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		rb.Insert(arr[i], i);
		cout << arr[i] << endl;
		cout << "IsBalance  " << rb.IsBalance() << endl;
	}
	cout<<"IsBalance  "<<rb.IsBalance()<<endl;
	rb.InOrder();
}
void TestSet()
{
	set<int> s;
	s.insert(1);
	s.insert(7);
	s.insert(6);

	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
}


