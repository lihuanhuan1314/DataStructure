#include<iostream>
#include<vector>

using namespace std;

template<class T>
class Less
{
public:
	bool operator()(const T&l, const T&r)
	{
		return l < r;
	}
};

template<class T>
class Great
{
public:
	bool operator()(const T&l, const T&r)
	{
		return l > r;
	}
};
template<class T, template<class> class Compare>//Compare是模版类型的模版形参
//template<class T,class Compare>  //Compare是模版形参
class Heap
{
public:
	Heap()
	{}
	Heap(const T*array, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_array.push_back(array[i]);
		}
		//从第一个非叶子节点开始向下调整
		for (int begin = _array.size() / 2 - 1; begin >= 0; --begin)
		{
			_AdjustDown(begin);
		}
	}
	Heap(vector<T>& array)
	{
		_array.swap(array);
		for (int begin = _array.size() / 2 - 1; begin >= 0; --begin)
		{
			_AdjustDown(begin);
		}
	}
	/*~Heap()
	{
	if (_array)
	delete[] _array;
	}*/
	void Push(const T& x)
	{
		_array.push_back(x);
		_AdjustUp(_array.size() - 1);
	}
	void Pop()
	{
		if (_array.size() != NULL)
		{
			_array[0] = _array[_array.size() - 1];
			_array.pop_back();
			_AdjustDown(0);
		}
	}
	bool Empty()
	{
		return _array.empty();
	}
	const T& Top()
	{
		return _array[0];
	}
	int Size()
	{
		return _array.size();

	}
	void PrintfHeap()
	{
		for (int i = 0; i < _array.size(); ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

protected:
	void _AdjustDown(int root)
	{
		int left = root * 2 + 1;
		int right = left + 1;
		while (left < _array.size())
		{
			int key = left;
			if (right < _array.size()
				&& Compare<T>()(_array[right], _array[left]))
			{
				key = right;
			}
			//if (_array[min] < _array[root])
			if (Compare<T>()(_array[key], _array[root]))
			{
				swap(_array[key], _array[root]);
				root = key;
				left = root * 2 + 1;
				right = left + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdjustUp(int child)
	{
		while (1)
		{
			int root = (child - 1) / 2;
			//if (_array[root]>_array[child])
			if (Compare<T>()(_array[root], _array[child]))
			{
				swap(_array[root], _array[child]);
				child = root;
			}
			else
			{
				break;
			}
			if (root == 0)
			{
				break;
			}
		}
	}
private:
	vector<T> _array;
};

void Test()
{
	int array[10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	Heap<int, Less> hp1(array, 10);
	hp1.PrintfHeap();
	int ret = hp1.Size();
	cout << ret << endl;
}
