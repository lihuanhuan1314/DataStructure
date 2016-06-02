#pragma once
#include<assert.h>

template<class T>
class Stack
{
public:
	Stack()
		:_array(NULL)
		, _capicity(0)
		, _topIndex(-1)
	{}
	~Stack()
	{
		delete[]_array;
		_capicity = 0;
		_topIndex = -1;
	}

	void Push(const T& x)//入栈
	{
		if (_topIndex + 1 == _capicity)
		{
			_capicity = 2 * _capicity + 3;
			T* tmp = new T[_capicity];
			if (tmp == NULL)
			{
				cout << " New Failed!" << endl;
				exit(-1);
			}
			memcpy(tmp,_array,sizeof(T)*(_topIndex+1));

			delete[] _array;
			_array = tmp;
		}
		_array[++_topIndex] = x;
	}
	void Pop()//出栈
	{
		assert(_topIndex > -1);
		--_topIndex;
	}
	bool Empty()
	{
		return _topIndex == -1;
	}
	bool Full() const
	{
		return _topIndex == _capicity - 1;
	}
	const T& Top()
	{
		return _array[_topIndex];
	}
	
private:
	T* _array;         //数据块
	size_t _capicity;  //容量
	int _topIndex;     //栈顶数据的下标
};

