#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* tail, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    if (tail == NULL) {
        tail = node;
        node->link = tail;
    }
    else {
        node->link = tail->link;
        tail->link = node;
    }
    return tail;
}

ListNode* insert_last(ListNode* tail, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    if (tail == NULL) {
        tail = node;
        node->link = tail;
    }
    else {
        node->link = tail->link;
        tail->link = node;
        tail = node;
    }
    return tail;
}

ListNode* delete_first(ListNode* tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    ListNode* head = tail->link;
    if (tail == head) {
        free(head);
        return NULL;
    }
    else {
        tail->link = head->link;
        free(head);
        return tail;
    }
}

ListNode* delete_last(ListNode* tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    ListNode* current = tail->link;
    if (tail == current) {
        free(tail);
        return NULL;
    }

    while (current->link != tail) {
        current = current->link;
    }
    current->link = tail->link;
    free(tail);
    return current;
}

void print_list(ListNode* tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return;
    }

    ListNode* p = tail->link;
    do {
        printf("%d -> ", p->data);
        p = p->link;
    } while (p != tail->link);

    printf("(head)");
}

int main() {
    ListNode* tail = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete from beginning\n");
        printf("4. Delete from end\n");
        printf("5. Print list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data to insert at beginning: ");
            scanf("%d", &data);
            tail = insert_first(tail, data);
            break;
        case 2:
            printf("Enter data to insert at end: ");
            scanf("%d", &data);
            tail = insert_last(tail, data);
            break;
        case 3:
            tail = delete_first(tail);
            break;
        case 4:
            tail = delete_last(tail);
            break;
        case 5:
            print_list(tail);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
