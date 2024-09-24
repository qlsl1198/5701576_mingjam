#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queue.h"
#define MAX_QUEUE_SIZE 10

void error(char* message) {
    fprintf(stderr, "%s", message);
}

int is_full(QueueType* q) {
    return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (is_full(q)) {
        error("Queue is Full.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // 수정된 부분: % MAX_QUEUE_SIZE 추가
    temp->data = item; // 수정된 부분: temp에 데이터 저장
    temp->link = NULL; // 수정된 부분: 링크 초기화
    if (q->front == NULL) { // 수정된 부분: 큐가 비어있을 때
        q->front = temp;
    } else {
        q->rear->link = temp; // 수정된 부분: 이전 rear의 링크를 새 노드로 설정
    }
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue is Empty.\n");
        return -1; // 에러 처리
    }
    QueueNode* temp = q->front; // 수정된 부분: front 노드를 임시로 저장
    q->front = q->front->link; // 수정된 부분: front를 다음 노드로 업데이트
    element data = temp->data; // 수정된 부분: 데이터 저장
    free(temp); // 수정된 부분: 임시 노드 메모리 해제
    return data; // 수정된 부분: 데이터 반환
}

void print_queue(QueueType* q) {
    int i;
    if (is_empty(q)) {
        printf("Queue is Empty.\n");
        return;
    }
    for (i = (q->front + 1) % MAX_QUEUE_SIZE; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
        printf("%2d -> ", q->data[i]);
    }
    printf("%2d\n", q->data[i]);
}
