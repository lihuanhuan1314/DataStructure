#pragma once
#include<assert.h>
class UnionSet
{
public:
	UnionSet(int N)
		:_size(N)
	{
		_set = new int[N];
		for (int i = 0; i < N; ++i)
		{
			_set[i] = -1;
		}
	}
	size_t Find(int child)
	{
		while (_set[child] >= 0)
		{
			child = _set[child];
		}
		return child;
	}
	void Union(int x1,int x2)
	{
		int root1 = Find(x1);
		int root2 = Find(x2);
		if (root1 != root2)
		{
			_set[root1] += _set[root2];
			_set[root2] = root1;
		}
	}
	int Count()
	{
		int count = 0;
		for (int i = 0; i < _size; ++i)
		{
			if (_set[i] < 0)
			{
				++count;
			}
		}
		return count;
	}
protected:
	int* _set;
	int _size;
};

int Friends(int n, int m, int r[][2])
{
	assert(r);
	UnionSet un(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int x1 = r[i][0];
		int x2 = r[i][1];
		un.Union(x1, x2);
	}
	return (un.Count()-1);
}

void Test()
{
	int r[4][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, {7, 8} };
	int ret=Friends(8,4,r);
	cout << "有多少朋友圈？" << ret << endl;
}
