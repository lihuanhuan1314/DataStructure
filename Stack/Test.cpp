#include<iostream>
#include"Stack.hpp"
using namespace std;
void Test()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Pop();
	while (!s.Empty())
	{
		cout << s.Top() << " ";
		s.Pop();
	}
	cout << endl;
}

int main()
{
	Test();
	return 0;
}