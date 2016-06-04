#pragma once 

template<class K,class V>
struct BSTreeNode
{
	K _key;     //��������
	V _val;    //�ýڵ������ֵ
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;

	BSTreeNode(const K& key, const V& val)
		: _key(key)
		, _val(val)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K,class V>
class BSTree
{
public:
	BSTree()
		:_root(NULL)
	{}
	
	BSTreeNode<K, V>* Find_NR(const K& key)   //�ǵݹ�ʵ��
	{
		while (_root)
		{
			//��key�͸��ڵ��key�Ƚ�,������ڣ���ô���ڸ��ڵ���ұ߲���
			if (key > _root->_key)
			{
				_root = _root->_right;
			}
			//��key�͸��ڵ��key�Ƚ�,���С�ڣ���ô���ڸ��ڵ����߲���
			else if (key < _root->_key)
			{
				_root = _root->_left;
			}
			else
			{
				return _root;
			}
		}
		return NULL;
	}
	BSTreeNode<K,V>* Find_R(const K& key)  //�ݹ�
	{
		return _Find(_root, key);
	}
	bool Insert_NR(const K& key, const V& val)
	{
		if (_root == NULL)
		{
			_root = new BSTreeNode<K, V>(key,val);
		}
		else
		{
			BSTreeNode<K, V>* cur = _root;
			BSTreeNode<K, V>* parent = NULL;
			while (cur)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key<cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			if (key>parent->_key)
			{
				parent->_right = new BSTreeNode<K, V>(key, val);
			}
			else
			{
				parent->_left = new BSTreeNode<K, V>(key,val);
			}
		}
		return true;
	}
	bool Insert_R(const K& key, const V& val)
	{
		if (_root == NULL)
		{
			_root =new BSTreeNode<K, V>(key,val);
			return true;
		}
		return _Insert(_root,key,val);
	}
	bool Delete_NR(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		BSTreeNode<K, V>* del = _root;
		BSTreeNode<K, V>* parent = NULL;
		while (del)
		{
			if (del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else if (del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else
			{
				break;
			}
		}
		if (del)
		{
			//���һ������
			if (del->_left == NULL)  //����Ϊ��
			{
				if (del == _root)
				{
					_root = del->_right;
				}
				else
				{
					if (del == parent->_left)
					{
						parent->_left = del->_right;
					}
					else
					{
						parent->_right = del->_right;
					}
				}
				delete del;
				del = NULL;
				return true;
			}
			else if (del->_right == NULL)  //�Һ���Ϊ��
			{
				if (del == _root)
				{
					_root = del->_left;
				}
				else
				{
					if (del == parent->_left)
					{
						parent->_left = del->_left;
					}
					else
					{
						parent->_right = del->_left;
					}
				}
				delete del;
				del = NULL;
				return true;
			}
			else   //��������
			{
				parent = del;
				BSTreeNode<K, V>* firstLeft = del->_right;

				//��������������ڵ�
				while (firstLeft->_left)
				{
					parent = firstLeft;
					firstLeft = firstLeft->_left;
				}
				
				swap(firstLeft->_key, del->_key);
				swap(firstLeft->_val, del->_val);

				if (firstLeft == parent->_left)
				{
					parent->_left = firstLeft->_right;
				}
				else
				{
					parent->_right = firstLeft->_right;
				}
				delete firstLeft;
				firstLeft = NULL;
				return true;
			}
		}
		return false;
	}
	bool Delete_R(const K& key)
	{
		return _Delete(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	BSTreeNode<K, V>* _Find(BSTreeNode<K, V>*& root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}
		if (key > root->_key)
		{
			_Find(root->_right, key);
		}
		else if (key < root->_key)
		{
			_Find(root->_left, key);
		}
		else
		{
			return root;
		}
	}
	bool _Insert(BSTreeNode<K, V>*& root, const K& key, const V& val)
	{
		if (root == NULL)
		{
			root = new BSTreeNode<K, V>(key, val);
			return true;
		}
		if (root->_key > key)
		{
			return _Insert(root->_left,key,val);
		}
		else if (root->_key < key)
		{
			return _Insert(root->_right, key, val);
		}
		else
		{
			return false;
		}
		return true;
	}
	bool _Delete(BSTreeNode<K, V>*& root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}
		if (key > root->_key)
		{
			return _Delete(root->_right, key);
		}
		else if (key < root->_key)
		{
			return _Delete(root->_left, key);
		}
		else
		{
			BSTreeNode<K, V>* del = root;
			if (root->_left == NULL)
			{
				root = root->_right; 
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				BSTreeNode<K, V>* firstLeft = root->_right;
				while (firstLeft->_left)
				{
					firstLeft = firstLeft->_left;
				}
				swap(del->_key, firstLeft->_key);
				swap(del->_val, firstLeft->_val);

				return _Delete(root->_right, key);
			}
		}
	}
	
	void _InOrder(BSTreeNode<K, V>* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_val << " ";
		_InOrder(root->_right);
		
	}
private:
	BSTreeNode<K, V>* _root;
};