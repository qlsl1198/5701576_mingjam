#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int is_full() {
    return (top == MAX_STACK_SIZE - 1);
}

int is_empty() {
    return (top == -1);
}

void push(element item) {
    if (is_full()) {
        fprintf(stderr, "Stack is FULL\n");
        return;
    }
    else {
        top++;
        stack[top] = item;
    }
}

void print_stack() {
    if (is_empty()) {
        fprintf(stderr, "Stack is empty\n\n");
        return;
    }
    printf("Stack contents: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n\n");
}

element pop() {
    if (is_empty()) {
        fprintf(stderr, "Stack is empty\n\n");
        return -1;
    }
    else {
        return stack[top--];
    }
}

int main() {
    srand(time(NULL));
    int rand_num = (rand() % 100) - 1;
    int data;


    for (int i = 0; i < 30; i++) {
        int rand_num = (rand() % 100) - 1;
        if (rand_num % 2 == 0) {
            data = rand_num;
            printf("Current rand_num: %d | Even\n", rand_num);
            if (top == MAX_STACK_SIZE - 1) {
                printf("Stack Overflow\n");
                print_stack();
            }
            else {
                printf("Push: %d\n", data);
                push(data);
                print_stack();
            }
        }
        else {
            printf("Current rand_num: %d | Odd\n", rand_num);
            if (top == -1) {
                printf("Stack Underflow\nStack is empty\n\n");
            }
            else {
                data = pop();
                printf("Pop: %d\n", data);
                print_stack();
            }
        }
    }
    return 0;
}
