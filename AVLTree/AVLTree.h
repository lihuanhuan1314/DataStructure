#include<math.h>

template<class K, class V>
struct AVLTreeNode
{
	K _key;  //�ؼ���
	V _value; 

	AVLTreeNode<K, V>* _parent;//����
	AVLTreeNode<K, V>* _left;//����
	AVLTreeNode<K, V>* _right;//�Һ���

	int _bf;//ƽ������
	AVLTreeNode<K, V>(const K& key, const V& value)//���캯��
		: _key(key)
		, _value(value)
		, _parent(NULL)
		, _left(NULL)
		, _right(NULL)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	Node* Find(const K& key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		if (key > _root->_key)
		{
			_root = _root->_right;
		}
		else if (key < _root->_key)
		{
			_root = _root->_left;
		}
		else
		{
			return _root;
		}
		return NULL;
	}
	bool Insert(const K& key,const V& value)
	{
		//�Ȳ���ڵ�
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		
		//�ٵ�ƽ������
		while (parent)
		{
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)  //�Ѿ���ƽ����
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1) //��������
			{
				cur = parent;
				parent = cur->_parent;
			}
			else // -2  2  ���� ��ת
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)  //  '\'   ����  
					{
						_RotateL(parent);
					}
					else  //-1   '>' ����˫��
					{
						_RotateRL(parent);
					}
				}
				else  //-2
				{
					if (cur->_bf == -1)  // '/' �ҵ���
					{
						_RotateR(parent);
					}
					else   // '<' ����˫��
					{
						_RotateLR(parent);
					}
				}
				break;
			}
		}
		return true;
	}
	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}
protected:
	void _RotateL(Node*& parent)  // '\'  ->   '/\'
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;

		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		//���½ڵ���Ϣ
		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else if (ppNode->_left == parent)
		{
			ppNode->_left = subR;
		}
		else
		{
			ppNode->_right = subR;
		}
		subR->_parent = ppNode;
		parent->_bf = subR->_bf = 0;//����ƽ������
	}
	void _RotateR(Node*& parent)   // '/'  ->   '/\'
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;

		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		subL->_parent = parent->_parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		//���½ڵ���Ϣ
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else if (ppNode->_left == parent)
		{
			ppNode->_left = subL;
		}
		else
		{
			ppNode->_right = subL;
		}
		subL->_parent = ppNode;
		parent->_bf = subL->_bf = 0;//����ƽ������
	}
	void _RotateLR(Node*& parent)   //  '<'  ->   '/'  ->   '/\'
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(parent->_left);
		_RotateR(parent);

		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else
		{
			subL->_bf = parent->_bf = 0;
		}
		subLR->_bf = 0;
		
	}
	void _RotateRL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			subR->_bf = parent->_bf = 0;
		}
		subRL->_bf = 0;
	}
	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int Left = _Height(root->_left);
		int Right = _Height(root->_right);
		return (Left > Right ?  Left:Right)+1;
	}
	void _Inorder(Node* root)
	{
		if (root == NULL)
			return ;

		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}
	bool _IsBalance(Node*& root)
	{
		if (root == NULL)
		{
			return true;
		}
		int bf = _Height(root->_right) - _Height(root->_left) ;
		if (abs(bf) > 1 || bf != root->_bf)
		{
			cout << "ƽ�����������⣺" << root->_key << endl;
			return false;
		}
		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}
protected:
	Node* _root;
};

void TestInsert()
{
	int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> alt1;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i)
	{
		alt1.Insert(arr1[i],i);
	}
	alt1.Inorder();
	cout << "isBlance? " << alt1.IsBalance() << endl;


	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14};
	AVLTree<int, int> alt2;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		alt2.Insert(arr[i], i);
	}
	alt2.Inorder();
	
	cout << "isBlance? " << alt2.IsBalance() << endl;
}