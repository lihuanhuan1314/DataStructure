#include<iostream>
using namespace std;

#include"Queue.hpp"

int main()
{
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.Pop();
	q.push(4);
	q.push(5);
	q.push(6);
	q.Pop();
	int ret = q.Size();
	
	while (!q.Empty())
	{
		cout << q.Front() << " ";
		q.Pop();
	}
	cout << endl;
	cout << "Size:" << ret << endl;
	return 0;
}