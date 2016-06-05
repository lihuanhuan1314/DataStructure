#pragma once

enum PointerTag{THREAD,LINK};

template<class T>
struct BinaryTreeThdNode
{
	T _data;//����
	BinaryTreeThdNode<T>* _left;  //����
	BinaryTreeThdNode<T>* _right; //�Һ���
	BinaryTreeThdNode<T>* _parent;
	PointerTag _leftTag; //����������־
	PointerTag _rightTag;//�Һ���������־

	BinaryTreeThdNode(const T& data)
		: _data(data)     
		, _left(NULL)    
		, _right(NULL) 
		, _parent(NULL)
		, _leftTag(LINK) 
		, _rightTag(LINK)
	{}
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd(const T* array,int size)
		:_root(NULL)
	{
		int index = 0;
		_CreateTree(_root,array,size,index);
	}
	//�����������������
	void InThreadOrder()
	{
		BinaryTreeThdNode<T>* cur = _root;
		while (cur)
		{
			while (cur && cur->_leftTag != THREAD)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			// �����Һ�̽ڵ�
			while (cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}

			if (cur)
			{
				cur = cur->_right;
			}
		}
	}
	void PrevThreadOrder()
	{
		BinaryTreeThdNode<T>* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			if(cur->_leftTag==THREAD)
			{
				break;
			}
			cur=cur->_left;
		}
		while (cur->_rightTag == THREAD&&cur->_right)
		{
			cur = cur->_right;
			cout << cur->_data << " ";
		}
		
	}
	void PostThreadOrder()
	{
		BinaryTreeThdNode<T>* cur = _root;
		BinaryTreeThdNode<T>* visited = NULL;

		if (_root)
		{
			cur = _root->_left;
		}
		while (cur != _root)
		{
			//��������
			if (cur&&cur->_leftTag == LINK&&cur->_left != visited)
			{
				cur = cur->_left;
			}
			//���ʺ�̽ڵ�
			while (cur&&cur->_rightTag==THREAD)
			{
				cout << cur->_data << " ";
				visited = cur;

				cur = cur->_right;
			}
			if (cur == _root)
			{
				cout << cur->_data << " ";
				return;
			}
			//�����ǰ�ڵ���ҽڵ��ѷ��ʣ����������ڵ�
			while (cur&&cur->_right == visited)
			{
				cout << cur->_data << " ";
				visited = cur;

				cur = cur->_parent;
			}
			//�ߵ�ǰ�ڵ������
			if (cur&&cur->_rightTag == LINK)
			{
				cur= cur->_right;
			}
		}
	} 
	void InOrderThreading()
	{
		BinaryTreeThdNode<T>* _prev = NULL;
		_InOrderThreading(_root, _prev);
	}
	void PrevOrderThreading()
	{
		BinaryTreeThdNode<T>* _prev = NULL;
		_PrevOrderThreading(_root, _prev);
	}
	void PostOrderThreading()
	{
		BinaryTreeThdNode<T>* _prev = NULL;
		_PostOrderThreading(_root, _prev);
	}
protected:
	void _CreateTree(BinaryTreeThdNode<T>*& root,const T* array,int size,int& index)
	{
		if (index < size&&array[index] != '#')
		{
			root = new BinaryTreeThdNode<T>(array[index]);
			_CreateTree(root->_left, array, size, ++index);
			_CreateTree(root->_right, array, size, ++index);
		}
	}
	void _InOrderThreading(BinaryTreeThdNode<T>* cur, BinaryTreeThdNode<T> *&prev)
	{
		if (cur)
		{
			_InOrderThreading(cur->_left, prev);//�ݹ�������������
			// ����->������ ->�ڵ���ֵ�˳��������������˳��

			// ��������ǰ��
			if (cur->_left==NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;//����ָ��ָ��ǰ��
			}
			//�������Һ��
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;//�Һ���ָ��ָ����
			}
			prev = cur;
			_InOrderThreading(cur->_right, prev);//�ݹ�������������
		}
	}
	void _PrevOrderThreading(BinaryTreeThdNode<T>* cur, BinaryTreeThdNode<T>*& prev)
	{
		if (cur)
		{
			//��������ǰ��
			if (cur->_left == NULL)
			{
				cur->_leftTag=THREAD;
				cur->_left = prev;
			}
			//�������Һ��
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}
			prev = cur;

			if (cur->_leftTag == LINK)
			{
				_PrevOrderThreading(cur->_left, prev);
			}
			if (cur->_rightTag == LINK)
			{
				_PrevOrderThreading(cur->_right, prev);
			}
		}
	}
	void _PostOrderThreading(BinaryTreeThdNode<T>* cur, BinaryTreeThdNode<T>*& prev)
	{
		if (cur)
		{
			if (cur->_leftTag == LINK)
			{
				_PostOrderThreading(cur->_left, prev);
			}
			if (cur->_rightTag == LINK)
			{
				_PostOrderThreading(cur->_right, prev);
			}
			
			//��������ǰ��
			if (cur->_left == NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;
			}
			//�������Һ��
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}
			prev = cur;
		}
	}
private:
	BinaryTreeThdNode<T> *_root;
};

// ����
void TestBinaryTreeThd_In()
{
	int array1[20] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd<int> tree1(array1, 10);

	tree1.InOrderThreading();
	tree1.InThreadOrder();
	cout << endl;
	int array2[20] = { 1, 2, 3, '#', '#', '#', 5, 6 };
	BinaryTreeThd<int> tree2(array2, 8);

	tree2.InOrderThreading();
	tree2.InThreadOrder();
}

// ǰ��
void TestBinaryTreeThd_Prev()
{
	int array[20] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd<int> tree1(array, 10);

	tree1.PrevOrderThreading();
	tree1.PrevThreadOrder();
}

void TestBinaryTreeThd_Post()
{
	int array[20] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd<int> tree1(array, 10);

	tree1.PostOrderThreading();
	tree1.PostThreadOrder();
}

