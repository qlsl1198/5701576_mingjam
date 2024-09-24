#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
typedef TreeNode* element;

typedef struct QueueNode{
    element data;
    struct QueueNode *link;
}QueueNode;

typedef struct{
    QueueNode *front, *rear;
    int size;
}QueueType;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(QueueType *q){
    q->front = q->rear = NULL;
    q->size = 0;
}

int is_empty(QueueType *q){
    return q->size == 0;
}

void enqueue(QueueType *q, element item){
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    if(temp == NULL)
        error("Memory allocation failed");
    temp->data = item;
    temp->link = NULL;
    if(is_empty(q)){
        q->front = temp;
    }else{
        q->rear->link = temp;
    }
    q->rear = temp;
    q->size++;
}

element dequeue(QueueType *q){
    if(is_empty(q))
        error("Queue is empty");
    QueueNode *temp = q->front;
    element item = temp->data;
    q->front = q->front->link;
    if(q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->size--;
    return item;
}

int GetHeightOfTree(TreeNode* root){
    if(root == NULL)
        return 0;
    QueueType q;
    init(&q);
    enqueue(&q, root);
    int height = 0;
    while(!is_empty(&q)){
        int node_count = q.size;
        while(node_count > 0){
            TreeNode* current = dequeue(&q);
            if(current->left != NULL)
                enqueue(&q, current->left);
            if(current->right != NULL)
                enqueue(&q, current->right);
            node_count--;
        }
        height++;
    }
    return height;
}

// int get_height_rec(TreeNode *root){
//     int height;
//     if(root == NULL) return 0;
//     height = 1 + (get_height_rec(root->left) > get_height_rec(root->right)
//         ? get_height_rec(root->left) : get_height_rec(root->right));
//         return height;
// }

// int sum_of_nodes(TreeNode* root){
//     if(root == NULL)
//         return 0;
//     int sum = root->data;
//     sum += sum_of_nodes_rec(root->left);
//     sum += sum_of_nodes_rec(root->right);
//     return sum;
// }

// int get_node_count_rec(TreeNode* root){
//     int count;

//     if (root == NULL) return 0;
//     count = 1 + get_node_count_rec(root->left) + get_node_count_rec(root->right);
//     return count;
// }

int GetSumOfNodes(TreeNode* root){
    if(root == NULL)
        return 0;
    int sum = 0;
    QueueType q;
    init(&q);
    enqueue(&q, root);
    while(!is_empty(&q)){
        TreeNode* current = dequeue(&q);
        sum += current->data;
        if(current->left != NULL)
            enqueue(&q, current->left);
        if(current->right != NULL)
            enqueue(&q, current->right);
    }
    return sum;
}

int GetNumOfNodes(TreeNode* root){
    if(root == NULL)
        return 0;
    int count = 0;
    QueueType q;
    init(&q);
    enqueue(&q, root);
    while(!is_empty(&q)){
        TreeNode* current = dequeue(&q);
        count++;
        if(current->left != NULL)
            enqueue(&q, current->left);
        if(current->right != NULL)
            enqueue(&q, current->right);
    }
    return count;
}

int GetNumOfLeafNodes(TreeNode* root){
    if(root == NULL)
        return 0;
    int count = 0;
    QueueType q;
    init(&q);
    enqueue(&q, root);
    while(!is_empty(&q)){
        TreeNode* current = dequeue(&q);
        if(current->left == NULL && current->right == NULL)
            count++;
        if(current->left != NULL)
            enqueue(&q, current->left);
        if(current->right != NULL)
            enqueue(&q, current->right);
    }
    return count;
}

 
 
TreeNode* createNode(int data){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if(newNode == NULL)
        error("Memory allocation failed");
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


int GenerateLinkedTree(TreeNode *root){
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
    return 0;
}




int main(){

    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    GenerateLinkedTree(root);
 

    printf("Sum of Nodes: %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumOfNodes(root));
    printf("Height of tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumOfLeafNodes(root));


    return 0;
}