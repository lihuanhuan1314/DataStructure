#pragma once

template<class T> 
struct QueueNode
{
	QueueNode(const T &x)
		:_data(x)
		, _next(NULL)
	{}

	T _data;
	QueueNode<T>* _next;
};

template<class T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
	{}
	~Queue()
	{
		while (_head)
		{
			if (_head == _tail)
			{
				delete _head;
				_head = NULL;
				_tail = NULL;
			}

			QueueNode<T>* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
		_tail = NULL;
	}
	void push(const T& x)
	{
		if (_head == NULL)
		{
			_head = new QueueNode<T>(x);
			_tail = _head;
		}
		else
		{
			QueueNode<T>* tmp = new QueueNode<T>(x);
			_tail->_next = tmp;
			_tail = _tail->_next;
		}
	}
	void Pop()
	{
		if (_head == NULL)
		{
			_tail = NULL;
		}
		else if (_head==_tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			QueueNode<T>* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
	}
	int Size()
	{
		int count = 0;
		QueueNode<T>* begin = _head;
		while (begin)
		{
			++count;
			begin = begin->_next;
			
		}
		return count;
	}
	bool Empty()
	{
		return _head == NULL;
	}
	const T& Front()
	{
		return _head->_data;
	}
private:
	QueueNode<T>* _head;
	QueueNode<T>* _tail;
};