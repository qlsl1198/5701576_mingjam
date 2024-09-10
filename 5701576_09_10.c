#include <stdio.h>
#include <stdlib.h>

typedef struct TreNode{
	int data;
	struct TreeNode* left, * right;

}TreeNode;

main() {
	int Tree[8] = { -1, 10, 5, 9, 6, 3, -1, 7 };

	TreeNode n1, n2, n3, n4, n5, n6, n7, n8;

	n1.data = 10, n1.left = &n2, n1.right = &n3;
	n2.data = 5, n2.left = &n4, n2.right = &n5;
	n3.data = 9, n3.left = NULL, n3.right = &n6;
	n4.data = 6, n4.left = NULL, n4.right = NULL;
	n5.data = 3, n5.left = NULL, n5.right = NULL;
	n6.data = 7, n6.left = NULL, n6.right = NULL;
}

void Pre_Order_By_Printer(TreeNode *np) {

}