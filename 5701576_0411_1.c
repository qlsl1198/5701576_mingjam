#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5

typedef int element;
typedef struct Stacktype {
    element* data;
    int capacity;
    int top;
} Stacktype;

int init(Stacktype* sptr, int nos) {
    sptr->data = (element*)malloc(sizeof(element) * nos);
    if (sptr->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    sptr->top = -1;
    sptr->capacity = nos;
    return 0;
}

int is_full(Stacktype* sptr) {
    if (sptr->top == sptr->capacity - 1) {
        sptr->capacity *= 2;
        sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
        printf("capacity has extented\n");

    }
    return 0;
}

int is_empty(Stacktype* sptr) {
    return (sptr->top == -1);
}

void push(Stacktype* sptr, element item) {
    if (is_full(sptr)) {
        fprintf(stderr, "Stack is FULL\n");
        return;
    }
    else {
        sptr->top++;
        sptr->data[sptr->top] = item;
    }
}

void print_stack(Stacktype* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n\n");
        return;
    }
    printf("Stack contents: ");
    for (int i = sptr->top; i >= 0; i--) {
        printf("%d ", sptr->data[i]);
    }
    printf("\n\n");
}

element pop(Stacktype* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n\n");
        return -1;
    }
    else {
        return sptr->data[sptr->top--];
    }
}

int main() {
    srand(time(NULL));

    Stacktype s;

    int rand_num;
    int data;

    if (init(&s, MAX_STACK_SIZE) == -1) {
        fprintf(stderr, "Failed to initialize the stack\n");
        return 1;
    }

    for (int i = 0; i < 30; i++) {
        rand_num = (rand() % 100) - 1;
        if (rand_num % 2 == 0) {
            data = rand_num;
            printf("Current rand_num: %d | Even\n", rand_num);
            if (is_full(&s)) {
                printf("Stack Overflow\n");
                print_stack(&s);
            }
            else {
                printf("Push: %d\n", data);
                push(&s, data);
                print_stack(&s);
            }
        }
        else {
            printf("Current rand_num: %d | Odd\n", rand_num);
            if (is_empty(&s)) {
                printf("Stack Underflow\nStack is empty\n\n");
            }
            else {
                data = pop(&s);
                printf("Pop: %d\n", data);
                print_stack(&s);
            }
        }
    }

    free(s.data);

    return 0;
}
