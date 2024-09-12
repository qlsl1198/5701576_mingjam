#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* data;
    struct StackNode* link;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

TreeNode* createNode(int data);
void PlaceNode(TreeNode* node, int direction, int data);
void GenerateLinkTree(TreeNode* root);
void LinkOrders(TreeNode* root);
void LinkPreOrder(TreeNode* root);
void LinkInOrder(TreeNode* root);
void LinkPostOrder(TreeNode* root);
Stack* createStack();
void push(Stack* s, TreeNode* data);
TreeNode* pop(Stack* s);
int isEmptyStack(Stack* s);
void freeStack(Stack* s);
void freeTree(TreeNode* root);

int main() {
    TreeNode* root = createNode(1);
    GenerateLinkTree(root);
    printf("순회 결과:\n");
    LinkOrders(root);
    freeTree(root);
    return 0;
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0) {
        node->left = createNode(data);
    }
    else {
        node->right = createNode(data);
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
    Stack* s = createStack();
    TreeNode* current = root;
    printf("전위 순회: ");
    while (current != NULL || !isEmptyStack(s)) {
        while (current != NULL) {
            printf("push(%d) ", current->data);
            push(s, current);
            printf("visit(%d) ", current->data);
            current = current->left;
        }
        if (!isEmptyStack(s)) {
            current = pop(s);
            printf("pop(%d) ", current->data);
            current = current->right;
        }
    }
    printf("\n");
    freeStack(s);
}

void LinkInOrder(TreeNode* root) {
    Stack* s = createStack();
    TreeNode* current = root;
    printf("중위 순회: ");
    while (current != NULL || !isEmptyStack(s)) {
        while (current != NULL) {
            printf("push(%d) ", current->data);
            push(s, current);
            current = current->left;
        }
        if (!isEmptyStack(s)) {
            current = pop(s);
            printf("pop(%d) visit(%d) ", current->data, current->data);
            current = current->right;
        }
    }
    printf("\n");
    freeStack(s);
}

void LinkPostOrder(TreeNode* root) {
    Stack* s1 = createStack();
    Stack* s2 = createStack();
    TreeNode* current = root;
    printf("후위 순회: ");
    push(s1, current);
    while (!isEmptyStack(s1)) {
        current = pop(s1);
        printf("push(%d) ", current->data);
        push(s2, current);
        if (current->left)
            push(s1, current->left);
        if (current->right)
            push(s1, current->right);
    }
    while (!isEmptyStack(s2)) {
        current = pop(s2);
        printf("pop(%d) visit(%d) ", current->data, current->data);
    }
    printf("\n");
    freeStack(s1);
    freeStack(s2);
}

void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

void push(Stack* s, TreeNode* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = s->top;
    s->top = newNode;
}

TreeNode* pop(Stack* s) {
    if (isEmptyStack(s)) {
        printf("스택이 비어있습니다.\n");
        return NULL;
    }
    StackNode* temp = s->top;
    TreeNode* data = temp->data;
    s->top = s->top->link;
    free(temp);
    return data;
}

int isEmptyStack(Stack* s) {
    return (s->top == NULL);
}

void freeStack(Stack* s) {
    while (!isEmptyStack(s)) {
        pop(s);
    }
    free(s);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}