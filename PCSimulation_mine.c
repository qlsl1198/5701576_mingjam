#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 50

typedef struct {
	int id;
	int arrival_time;
	int service_time;
}element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s", message);
	return -1;
}

int is_full(QueueType* q) {
	return (q->front == ((q->rear + 1) % MAX_QUEUE_SIZE));
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		error("Queue is full\n");
	}
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("Queue is empty\n");
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return (q->data[q->front]);
	}
}

void print_queue(QueueType* q) {
	int i;
	for (i = (q->front + 1) % MAX_QUEUE_SIZE; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
		printf("[%2d] %2d, ", i, q->data[i]);
	}
	printf("[%2d] %2d\n", i, q->data[i]);
}


main() {

	QueueType queue;
	int minutes = 60;
	int total_customers = 0;
	int service_time = 0;
	int total_wait = 0;
	int service_customer = 0;;

	init_queue(&queue);
	srand(time(NULL));

	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각 = %d\n", clock);
		//producer
		if (rand() % 10 < 6) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간=%d분\n",
				customer.id, customer.arrival_time, customer.service_time);
		}
		//consummer
		if (service_time == 0) {/*작업처리 완료, 새로운 작업 가져오기*/
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_time = customer.service_time;
				service_customer = customer.id;
				printf("고객 %d가 업무를 시작합니다. 대기시간은 %d분입니다.\n",
					customer.id, clock - customer.arrival_time);
				total_wait = total_wait + (clock - customer.arrival_time);



			}
			
		}
		else {
			service_time--;
			printf("고객 %d의 업무처리 중입니다.\n", service_customer);
		}
	}
	printf("\n Total Wait = %d, No of Customers = %d, Average Wait = %f", 
		total_wait, total_customers, total_wait / (float)total_customers);
}