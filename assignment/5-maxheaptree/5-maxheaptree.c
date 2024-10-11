#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

typedef int element;

typedef struct tree_node {
    element data;
    struct tree_node* left, *right, *parent;
} TreeNode;

typedef struct {
    TreeNode* data[MAX_ELEMENTS];
    int front, rear;
} QueueType;

// 큐 초기화 함수
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

// 큐가 비어있는지 확인하는 함수
int is_empty(QueueType* q) {
    return q->front == q->rear;
}

// 큐에 요소를 추가하는 함수
void enqueue(QueueType* q, TreeNode* item) {
    q->rear = (q->rear + 1) % MAX_ELEMENTS;
    q->data[q->rear] = item;
}

// 큐에서 요소를 제거하고 반환하는 함수
TreeNode* dequeue(QueueType* q) {
    q->front = (q->front + 1) % MAX_ELEMENTS;
    return q->data[q->front];
}

// 새 노드를 생성하는 함수
TreeNode *createNode(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

// 레벨 순서로 트리를 출력하는 함수
void print_level_order(TreeNode* root) {
    if (root == NULL) return;
    QueueType q;
    init_queue(&q);
    enqueue(&q, root);
    while (!is_empty(&q)) {
        TreeNode* temp = dequeue(&q);
        printf("%d ", temp->data);
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    printf("\n");
}

// 최대 힙에 노드를 삽입하는 함수 (이동 과정 출력)
void insertMaxHeapNode(TreeNode** root, int key) {
    if (*root == NULL) {
        *root = createNode(key);
        return;
    }

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);

    TreeNode* temp = NULL;
    while (!is_empty(&q)) {
        temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = createNode(key);
            temp->left->parent = temp;
            temp = temp->left;
            break;
        } else if (temp->right == NULL) {
            temp->right = createNode(key);
            temp->right->parent = temp;
            temp = temp->right;
            break;
        } else {
            enqueue(&q, temp->left);
            enqueue(&q, temp->right);
        }
    }

    int move = 0;
    print_level_order(*root);
    while (temp->parent != NULL && temp->data > temp->parent->data) {
        int swap = temp->data;
        temp->data = temp->parent->data;
        temp->parent->data = swap;
        temp = temp->parent;
        print_level_order(*root);
        move++;
    }
    printf("move: %d\n", move);
}

// 최대 힙에 노드를 삽입하는 함수 (이동 과정 출력 없음)
void insertWithoutPrint(TreeNode** root, int key) {
    if (*root == NULL) {
        *root = createNode(key);
        return;
    }

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);

    TreeNode* temp = NULL;
    while (!is_empty(&q)) {
        temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = createNode(key);
            temp->left->parent = temp;
            temp = temp->left;
            break;
        } else if (temp->right == NULL) {
            temp->right = createNode(key);
            temp->right->parent = temp;
            temp = temp->right;
            break;
        } else {
            enqueue(&q, temp->left);
            enqueue(&q, temp->right);
        }
    }
    
    while (temp->parent != NULL && temp->data > temp->parent->data) {
        int swap = temp->data;
        temp->data = temp->parent->data;
        temp->parent->data = swap;
        temp = temp->parent;

    }
}

// 입력 데이터로 최대 힙 트리를 생성하는 함수
TreeNode *generateMaxHeapTree(int inputData[], int size) {
    TreeNode *root = NULL;
    for (int i = 0; i < size; i++) {
        insertWithoutPrint(&root, inputData[i]);
    }
    return root;
}

// 최대 힙에서 최대값(루트)을 삭제하는 함수
void deleteMaxHeapNode(TreeNode** root) {
    if (*root == NULL) return;

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);
    TreeNode* last = NULL;

    while (!is_empty(&q)) {
        last = dequeue(&q);
        if (last->left) enqueue(&q, last->left);
        if (last->right) enqueue(&q, last->right);
    }

    int deleted = (*root)->data;
    (*root)->data = last->data;

    if (last->parent) {
        if (last->parent->left == last)
            last->parent->left = NULL;
        else
            last->parent->right = NULL;
    }

    if (last == *root) {
        free(last);
        *root = NULL;
        return;
    }

    free(last);

    TreeNode* temp = *root;
    int move = 0;
    print_level_order(*root);
    while (1) {
        TreeNode* largest = temp;
        if (temp->left && temp->left->data > largest->data)
            largest = temp->left;
        if (temp->right && temp->right->data > largest->data)
            largest = temp->right;
        
        if (largest == temp) break;

        int swap = temp->data;
        temp->data = largest->data;
        largest->data = swap;
        temp = largest;
        print_level_order(*root);
        move++;
    }

    printf("Deleted: %d, move: %d\n", deleted, move);
}

// 트리를 레벨별로 출력하는 함수
void printTree(TreeNode* root) {
    if (root == NULL) return;
    QueueType q;
    init_queue(&q);
    enqueue(&q, root);
    int level = 1;
    while (!is_empty(&q)) {
        int level_size = (q.rear - q.front + MAX_ELEMENTS) % MAX_ELEMENTS;
        printf("[%d] ", level);
        for (int i = 0; i < level_size; i++) {
            TreeNode* temp = dequeue(&q);
            printf("%d ", temp->data);
            if (temp->left) enqueue(&q, temp->left);
            if (temp->right) enqueue(&q, temp->right);
        }
        printf("\n");
        level++;
    }
}

// 트리의 모든 노드를 해제하는 함수
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 사용자 인터페이스를 실행하는 함수
void runUserInterface(TreeNode** root) {
    while (1) {
        printf("┌────────────────┐\n");
        printf("│ i  : 노드 추가        │\n");
        printf("│ d  : 노드 삭제        │\n");
        printf("│ p  : 레벨별 출력      │\n");
        printf("│ c  : 종료             │\n");
        printf("└────────────────┘\n");
        printf("메뉴 입력: ");
        char input;
        scanf(" %c", &input);
        if (input == 'i') {
            int key;
            printf("추가할 값 입력: ");
            scanf("%d", &key);
            insertMaxHeapNode(root, key);
        }
        else if (input == 'd') {
            deleteMaxHeapNode(root);
        }
        else if (input == 'p') {
            printTree(*root);
        }
        else if (input == 'c') {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 입력입니다.\n");
        }
    }
}

// 메인 함수
int main() {
    // 초기 데이터 설정
    int inputData[] = {90, 89, 70, 36, 75, 63, 13, 21, 18, 5};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    
    // 최대 힙 트리 생성
    TreeNode *root = generateMaxHeapTree(inputData, size);

    // 사용자 인터페이스 실행
    runUserInterface(&root);
    
    // 메모리 해제
    freeTree(root);
    return 0;
}