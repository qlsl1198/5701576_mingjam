#pragma once
#include "LevTreeTrv.h"

#define MAX_QUEUE_SIZE 10


typedef TreeNode* element;

typedef struct Queuenode{ // 구조체 이름 수정
    element data;
    struct Queuenode* link; // 수정된 부분: QueueNode -> Queuenode
} QueueNode;

typedef struct {
    QueueNode* front, *rear;
} QueueType;

extern void init_queue(QueueType* q);
extern int is_full(QueueType* q);
extern int is_empty(QueueType* q);
extern void enqueue(QueueType* q, element item);
extern void print_queue(QueueType* q);
extern element dequeue(QueueType* q); // 수정된 부분
