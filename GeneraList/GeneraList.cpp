#include<iostream>
using namespace std;


enum NodeType
{
	HEAD_TYPE,   //头结点
	VALUE_TYPE, //值节点
	SUB_TYPE,  //子表节点
};
struct GeneralListNode
{
	NodeType _type;//节点类型
	GeneralListNode* _next;
	
	union
	{
		char _value;
		GeneralListNode* _subLink;
	};
	GeneralListNode(NodeType type = HEAD_TYPE, char value = '\0')
		:_type(type)
		,_next(NULL)
	{
		if (type == VALUE_TYPE)
		{
			_value = value;
		}
		else if (type == SUB_TYPE)
		{
			_subLink = NULL;
		}
	}
};
class GeneralList
{
public:
	GeneralList(const char* str)
		:_link(NULL)
	{
		_CreateGeneralList(_link,str);
	}
	GeneralList(const GeneralList&gl)
	{
		_link = _CopyGeneralList(gl._link);
	}
	/*GeneralList& operator=(const GeneralList&gl)
	{
		if (this != &gl)
		{
			this->_DestoryGeneralList(_link);
			_link = _CopyGeneralList(gl._link);
		}
		return *this;
	}*/
	GeneralList& operator=(GeneralList gl)
	{
		swap(_link, gl._link);
		return *this;
	}
	~GeneralList()
	{
		_DestoryGeneralList(_link);
		_link == NULL;
	}
	void Print()
	{
		_Print(_link);
		cout << endl;
	}
	int Size()
	{
		return _Size(_link);
	}
	int Depth()
	{
		return _Depth(_link);
	}
protected:
	bool _IsValue(char ch)
	{
		if (ch >= '0'&& ch <= '9'
			|| ch>= 'a'&& ch <= 'z'
			|| ch >= 'A'&& ch <= 'Z')
			return true;
		return false;
	}
	void _CreateGeneralList(GeneralListNode*& link,const char*& str)
	{
		if (*str ++!= '(')
		{
			cout << " Invalid Str" << endl;
			exit(-1);
		}
		//头结点
		GeneralListNode* head = new GeneralListNode(HEAD_TYPE);
		link = head;

		GeneralListNode* begin = head;
		while (*str != '\0')
		{
			//值节点
			if (_IsValue(*str))
			{
				GeneralListNode* valueNode = new GeneralListNode(VALUE_TYPE,*str);
				++str;
				begin->_next = valueNode;
				begin = begin->_next;
			} 
			else if (*str == '(')
			{
				//递归创建子表
				GeneralListNode* subNode = new GeneralListNode(SUB_TYPE);
				begin->_next = subNode;
				begin = begin->_next;
				_CreateGeneralList(subNode->_subLink,str);
			}
			else if (*str == ')')
			{
				++str; 
				return;
			}
			else
			{
				//, 空格
				++str;
			}
		}
	}
	void _Print(GeneralListNode* link)
	{
		GeneralListNode* begin = link;
		while (begin)
		{
			if (begin->_type == HEAD_TYPE)
			{
				cout << "(";
			}
			else if (begin->_type == VALUE_TYPE)
			{
				cout << begin->_value;
				if (begin->_next)
				{
					cout << ",";
				}
			}
			else if (begin->_type == SUB_TYPE)
			{
				_Print(begin->_subLink);
				if (begin->_next)
				{
					cout << ",";
				}
			}
			begin = begin->_next;
		}
		cout << ")";
	}
	int _Size(GeneralListNode* head)
	{
		int size = 0;
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				++size;
			}
			else if (cur->_type == SUB_TYPE)
			{
				size += _Size(cur->_subLink);
			}
			cur = cur->_next;
		}
		return size;
	}
	int _Depth(GeneralListNode* head)
	{
		int depth = 1;
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB_TYPE)
			{
				int subDepth = _Depth(cur->_subLink);
				if (subDepth + 1>depth)
				{
					depth = subDepth+1;
				}
				
			}
			cur = cur->_next;
		}
		return depth;
	}
	void _DestoryGeneralList(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB_TYPE)
			{
				_DestoryGeneralList(cur->_subLink);
			}
			GeneralListNode* del = cur;
			cur = cur->_next;
			delete del;
		}
	}
	GeneralListNode* _CopyGeneralList(GeneralListNode* head)
	{
		GeneralListNode* newList = new GeneralListNode(HEAD_TYPE);
		GeneralListNode* cur = head->_next;
		
		GeneralListNode* begin = newList;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				GeneralListNode* valueNode = new GeneralListNode(VALUE_TYPE, cur->_value);
				begin->_next = valueNode;
			}
			else if(cur->_type == SUB_TYPE)
			{
				GeneralListNode* subNode = new GeneralListNode(SUB_TYPE);
				begin->_next = subNode;

				subNode->_subLink = _CopyGeneralList(cur->_subLink);
			}

			begin = begin->_next;
			cur = cur->_next;
		}

		return newList;
	}
private:
	GeneralListNode* _link;
};
void Test1()
{
	//空广义表
	const char* str1 = "()";
	GeneralList gl1(str1);
	gl1.Print();
	
	//单层
	const char* str2 = "(a,b)";
	GeneralList gl2(str2);
	gl2.Print();
	
	//带子表
	const char* str3 = "(a,b,(c,d))";
	GeneralList gl3(str3);
	gl3.Print();
	
	//带空格
	const char* str4 = "(a, b, (c,d))";
	GeneralList gl4(str4);
	gl4.Print();

	//多层嵌套
	const char* str5 = "(a,b,(c,d),(e,(f),h))";
	GeneralList gl5(str5);
	gl5.Print();

	cout << "gl5.Size=" << gl5.Size() << endl;
	cout << "gl5.Depth=" << gl5.Depth() << endl;
}

void Test2()
{
	//空广义表
	const char* str1 = "()";
	GeneralList gl1(str1);
	gl1.Print();

	//单层
	const char* str2 = "(a,b)";
	GeneralList gl2(str2);
	gl2.Print();

	//带子表
	const char* str3 = "(a,b,(c,d))";
	GeneralList gl3(str3);
	gl3.Print();

	GeneralList gl4(gl3);
	gl4.Print();

	const char* str5 = "()";
	GeneralList gl5(str5);
	gl5 = gl3;
	gl5.Print();
}

int main()
{
	//Test1();
	Test2();
	return 0;
}