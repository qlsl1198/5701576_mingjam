#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	TreeNode* left, * right;

}TreeNode;

main() {
	int Tree[8] = { -1, 10, 5, 9, 6, 3, -1, 7 };

	TreeNode n1, n2, n3, n4, n5, n6, n7, n8;

	n1.data = 10, n1.left = &n2, n1.right = &n3;

}