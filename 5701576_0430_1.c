#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

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
    if (is_full(q)) {
        error("Queue is Full.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue is Empty.\n");
        return -1; // 에러 처리
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
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

int main() {
    QueueType queue;
    element e;
    int choice;

    init_queue(&queue);

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. 큐에 원소를 삽입\n");
        printf("2. 큐에서 원소를 삭제\n");
        printf("3. 큐의 원소를 출력\n");
        printf("4. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("큐에 삽입할 숫자를 입력하세요: ");
            scanf_s("%d", &e);
            enqueue(&queue, e);
            break;
        case 2:
            e = dequeue(&queue);
            if (e != -1)
                printf("큐에서 삭제된 원소: %d\n", e);
            break;
        case 3:
            printf("현재 큐의 상태: ");
            print_queue(&queue);
            break;
        case 4:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid menu. Please select again.\n");
            break;
        }
    }

    return 0;
}
