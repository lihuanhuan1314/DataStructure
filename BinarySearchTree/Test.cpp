#include<iostream>
using namespace std;
#include"BinarySearchTree.hpp"

int main()
{
	BSTree<int,int> bst;
	bst.Insert_NR(1, 1);
	bst.Insert_NR(2, 2);
	bst.Insert_NR(3, 3);
	bst.Insert_NR(4, 4);
	bst.Insert_NR(6, 6);
	bst.InOrder();
	
	bst.Delete_NR(6);
	bst.Delete_NR(2);
	bst.Delete_NR(3);
	bst.Delete_NR(4);
	bst.InOrder();
	

	bst.Insert_R(1, 1);
	bst.Insert_R(2, 2);
	bst.Insert_R(3, 3);
	bst.Insert_R(4, 4);
	bst.Insert_R(6, 6);
	bst.InOrder();
	
	bst.Delete_R(6);
	bst.Delete_R(2);
	bst.Delete_R(3);
	bst.Delete_R(4);
	bst.InOrder();
	
	return 0;
}

