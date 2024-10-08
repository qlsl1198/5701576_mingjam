
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

TreeNode* search_bst(TreeNode* root, int key) {
    if(root == NULL) return NULL;
    else{
        if(key == root->data) return root;
        else if(key < root->data) return search_bst(root->left, key);
        else return search_bst(root->right, key);
    }
}

TreeNode* min_value_node(TreeNode* root){
    TreeNode* current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return current;
}

TreeNode* delete_node(TreeNode* root, int key) {
    TreeNode* temp;

    if(root == NULL) return root;
    if(root->data > key){
        root->left = delete_node(root->left, key);
        return root;
    }
    else if (root->data < key){
        root->right = delete_node(root->right, key);
        return root;
    }

    else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if(root->left == NULL && root->right != NULL){
            temp = root->right;
            free(root);
            return temp;
        }

        else if(root->left != NULL && root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }

        else{
            temp = min_value_node(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
            return root;
        }
    }  
}




void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%2d ", root->data);
        inorder_traversal(root->right);
    }
}




int main() {
    TreeNode* bst = NULL;
    TreeNode* temp;

    bst = insert_node(bst, 14);
    bst = insert_node(bst, 5);
    bst = insert_node(bst, 3);
    bst = insert_node(bst, 4);
    bst = insert_node(bst, 2);
    bst = insert_node(bst, 9);
    bst = insert_node(bst, 8);
    bst = insert_node(bst, 18);
    bst = insert_node(bst, 15);
    bst = insert_node(bst, 19);
    bst = insert_node(bst, 16);
    bst = insert_node(bst, 20);

    printf("inorder traversal: ");
    inorder_traversal(bst);
    printf("\n");

    int search_key = 14;
    temp = search_bst(bst, search_key);
    if(temp != NULL) printf("key found %d\n", temp->data);
    else printf("key not found %d\n", search_key);


    int delete_key = 14;
    bst = delete_node(bst, delete_key);
    printf("inorder traversal after deleting %d: ", delete_key);
    inorder_traversal(bst);
    printf("\n");

    return 0;
}


