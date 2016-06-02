#include<iostream>
#include<stack>
#include<queue>
using namespace std;

template <class T>
struct TreeNode
{
	T _value;  //节点值
	TreeNode<T> *_firstChild;  //左孩子
	TreeNode<T> *_nextBrother; //右兄弟
};

template <class T>
struct BinaryTreeNode
{
	T _value;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T> *_right;

	BinaryTreeNode(const T& value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(char *str)
	{
		_CreateTree(_root,str);
	}
	BinaryTree(BinaryTree<T>& t)
	{
		_root = _CopyTree(t._root);
	}
	/*BinaryTree& operator=(BinaryTree<T>& t)
	{
		if (this != &t)
		{
			_Destroy(t._root);
			_CopyTree(t._root);
		}
		
		return *this;
	}*/
	BinaryTree& operator=(BinaryTree<T> t)
	{
		swap(_root, t._root);
		return *this;
	}

	~BinaryTree()
	{
		_DestoryTree(_root);
	}

	void _CreateTree(BinaryTreeNode<T>*& root,char*& str)
	{
		if (*str != '#'&&*str != '\0')
		{
			root = new BinaryTreeNode<T>(*str);
			_CreateTree(root->_left,++str);

			if (*str == '\0')
				return;

			_CreateTree(root->_right, ++str);
		}
	}
	void PrevOrder_NonR()  //前序遍历（非递归）
	{
		stack<BinaryTreeNode<T>* > s;
		if (_root)
		{
			s.push(_root);
		}
		while (!s.empty())
		{
			BinaryTreeNode<T>* top = s.top();
			cout << top->_value << " ";
			s.pop();

			if (top->_right)
				s.push(top->_right);
			if (top->_left)
				s.push(top->_left);
		}
		cout << endl;
	}
	void InOrder_NonR() //中序遍历（非递归）
	{
		stack<BinaryTreeNode<T>* > s;
		BinaryTreeNode<T>* cur = _root;

		while (cur || !s.empty())
		{
			//左节点都入栈
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				cout << top->_value << " ";
				s.pop();

				if (top->_right)
				{
					cur = top->_right;
				}
			}
		}
		cout << endl;
	}
	void PostOrder_NonR()  //后序遍历（非递归）
	{
		stack<BinaryTreeNode<T>* > s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* vistedNode = NULL;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			// 右为空或者右节点等于上一个访问的节点时，表示左右子树均已访问
			BinaryTreeNode<T>* top = s.top();
			if (top->_right == NULL || top->_right == vistedNode)
			{
				s.pop();
				cout << top->_value << " ";
				vistedNode = top;
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	void Size()
	{
		_Size(_root);
	}
	void LeafNodeNum()//叶子节点个数
	{
		_LeafNodeNum(_root);
	}
	void Depth()  //深度
	{
		_Depth(_root);
	}
	void KLevelNodeNum()//第K层节点个数
	{
		_KLevelNodeNum(_root);
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder() //层序遍历
	{
		_LevelOrder(_root);
		cout << endl;
	}
protected:
	void _DestoryTree(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			_DestoryTree(root->_left);
			_DestoryTree(root->_right);

			delete root;
			root = NULL;
		}
	}
	BinaryTreeNode<T>* _CopyTree(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* copyRoot = NULL;
		if (root)
		{
			copyRoot = new BinaryTreeNode<T>(root->_value);
			copyRoot->_left = _CopyTree(root->_left);
			copyRoot->_right = _CopyTree(root->_right);
		}
		return copyRoot;
	}
	int _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->_left == NULL&&root->_right == NULL)
		{
			return 1;
		}
		else
		{
			return 1 + _Size(root->left) + _Size(root->_right);
		}
	}
	int _LeafNodeNum(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		else if (root->_left == NULL&&root->_right == NULL)
		{
			return 1;
		}
		else
		{
			int leftNum = _LeafNodeNum(root->_left);
			int rightNum = _LeafNodeNum(root->_right);
			return (leftNum + rightNum);
		}
	}
	int _Depth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return 0;
		int leftDepth = _Depth(root->_left);
		int rightDepth = _Depth(root->_right);

		return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
	}
	void _KLevelNodeNum(BinaryTreeNode<T>* root,int k)
	{
		if (root == NULL || k < 1)
		{
			return 0;
		}
		else if (k == 1)
		{
			return 1;
		}
		else
		{
			int leftNum = _LeafNodeNum(root->_left,k-1);// 左子树中k-1层的节点个数
			int rightNum = _LeafNodeNum(root->_right,k-1);// 右子树中k-1层的节点个数
			return (leftNum + rightNum);
		}
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			cout << root->_value << " ";

			if (root->_left)
				_PrevOrder(root->_left);
			if (root->_right)
				_PrevOrder(root->_right);
		}
	}
	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			if (root->_left)
				_InOrder(root->_left);
			cout << root->_value << " ";
			if (root->_right)
				_InOrder(root->_right);
		}
	}
	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			if (root->_left)
				_PostOrder(root->_left);
			
			if (root->_right)
				_PostOrder(root->_right);

			cout << root->_value << " ";
		}
	}
	void _LevelOrder(BinaryTreeNode<T>* root)
	{
		queue<BinaryTreeNode<T>* > q;
		if (root)
		{
			q.push(root);
		}
		while (!q.empty())
		{
			BinaryTreeNode<T>* front = q.front();
			cout << front->_value << " ";
			q.pop();

			if (front->_left)
				q.push(front->_left);
			if (front->_right)
				q.push(front->_right);
		}
	}
	
private:
	BinaryTreeNode<T> *_root;
};

int main()
{
	char* str = "123##4##56###";
	BinaryTree<char> bt1(str);

	bt1.PrevOrder();
	bt1.PrevOrder_NonR();
	bt1.InOrder();
	bt1.InOrder_NonR();
	bt1.PostOrder();
	bt1.PostOrder_NonR();
	bt1.LevelOrder();
	
	

	//cout<<"Size:"<<bt1.Size()<<endl;
	//cout<<"Depth:"<<bt1.Depth()<<endl;

	

	BinaryTree<char> bt2(bt1);
	bt2.PrevOrder_NonR();

	BinaryTree<char> bt3;
	bt3 = bt1;
	bt3.PrevOrder_NonR();
	return 0;
}


