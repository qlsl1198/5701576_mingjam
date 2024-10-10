#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode* create_node(int key) {
    TreeNode* temp;
    temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->data) {
        root->left = insert_node(root->left, key);
    } else {
        root->right = insert_node(root->right, key);
    }
    return root;
}

void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%2d", root->data);
        inorder_traversal(root->right);
    }
}
