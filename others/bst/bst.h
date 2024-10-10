#pragma once

typedef struct tree_node {
    int data;
    struct tree_node* left, *right;
} TreeNode;

extern TreeNode* create_node(int key);
extern TreeNode* insert_node(TreeNode* root, int key);
extern void inorder_traversal(TreeNode* root);
