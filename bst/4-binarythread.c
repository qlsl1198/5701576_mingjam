#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node* left, *right;
} TreeNode;

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
TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for(int i = 0; i < 15; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

TreeNode* BinaryTreeInOrder(TreeNode* root){
    if(root != NULL){
        BinaryTreeInOrder(root->left);
        printf("%2d ", root->data);
        BinaryTreeInOrder(root->right);
    }
    return root;
}


typedef struct thread_tree_node {
    int data;
    struct thread_tree_node* left, *right;
    int is_thread;
} ThreadTree;


ThreadTree* create_thread_node(int key) {
    ThreadTree* temp;
    temp = (ThreadTree*)malloc(sizeof(ThreadTree));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->is_thread = 0;
    return temp;
}

ThreadTree* insert_thread_node(ThreadTree* root, int key) {
    if (root == NULL) {
        return create_thread_node(key);
    }
    if (key < root->data) {
        root->left = insert_thread_node(root->left, key);
    } else {
        root->right = insert_thread_node(root->right, key);
    }
    return root;
}

void create_right_thread(ThreadTree* root, ThreadTree** prev) {
    if (root == NULL) return;
    
    create_right_thread(root->left, prev);
    
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->is_thread = 1;
    }
    
    *prev = root;
    
    create_right_thread(root->right, prev);
}

ThreadTree* GenerateThreadTree(int inputData[]) {
    ThreadTree* root = NULL;
    for(int i = 0; i < 15; i++) {
        root = insert_thread_node(root, inputData[i]);
    }

    ThreadTree* prev = NULL;
    create_right_thread(root, &prev);
    
    return root;
}



void ThreadTreeInOrder(ThreadTree* root) {
    if (root == NULL) return;
    
    ThreadTree* current = root;
    
    while (current->left != NULL) {
        current = current->left;
    }
    
    while (current != NULL) {
        printf("%2d ", current->data);
        
        if (current->right == NULL) {
            break;
        } else if (current->is_thread) {
            current = current->right;
        } else {
            current = current->right;
            while (current->left != NULL) {
                current = current->left;
            }
        }
    }
    printf("\n");
}



void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void free_thread_tree(ThreadTree* root) {
    if (root == NULL) return;
    if (root->left) free_thread_tree(root->left);
    if (root->right && !root->is_thread) free_thread_tree(root->right);
    free(root);
}

int main() {
    int inputData[] = {4,1,9,13,15,3,6,14,7,10,12,2,5,8,11};
    TreeNode* root = GenerateBinaryTree(inputData);
    
    printf("binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadTree *troot = GenerateThreadTree(inputData);
    printf("thread tree inorder: ");
    ThreadTreeInOrder(troot); 

    free_tree(root);
    free_thread_tree(troot);

    return 0;
}


