#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}   

TreeNode* insertNode_iter(TreeNode* root, int data) {
    TreeNode* newNode = createNode(data);
    TreeNode* temp = root;
    TreeNode* prev = root;



    while (temp != NULL) {
        if(temp->data == data) {    
            return temp;
        }
        else if(temp->data > data) {
            prev = temp;
            temp = temp->left;
        }
        else {
            prev = temp;
            temp = temp->right;
        }
    }
    if(data < prev->data) {
        prev->left = newNode;
    }
    else {
        prev->right = newNode;
    }
    return root;
}

TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}


TreeNode* findMinNode(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


void printTree(TreeNode* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

void printTreeShape(TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }
    space += 10;
    printTreeShape(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    printTreeShape(root->left, space);
}


int main() {
    
    TreeNode* root = NULL;

    root = insertNode_iter(root, 3);
    root = insertNode_iter(root, 6);
    root = insertNode_iter(root, 4);
    root = insertNode_iter(root, 2);
    root = insertNode_iter(root, 8);
    root = insertNode_iter(root, 7);



    printf("이진 탐색 트리: ");
    printTree(root);
    printf("\n");

    printf("이진 탐색 트리 모양: \n");
    printTreeShape(root, 0);

    root = deleteNode(root, 30);
    printf("30 삭제 후 이진 탐색 트리: ");
    printTree(root);
    printf("\n");

    printf("이진 탐색 트리 모양: \n");
    printTreeShape(root, 0);

    return 0;

}

