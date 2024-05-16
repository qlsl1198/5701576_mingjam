#include <stdio.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size;
} ArrayListType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
}

int is_full(ArrayListType* L) {
    return L->size == MAX_LIST_SIZE;
}

void insert(ArrayListType* L, int pos, element item) {
    int move = 0;
    if (!is_full(L) && pos >= 0 && pos <= L->size) {
        for (int i = L->size - 1; i >= pos; i--) {
            L->array[i + 1] = L->array[i];
            move++;
        }
        L->array[pos] = item;
        L->size++;
        printf("Insertion complete. Data moved %d times.\n", move);
    }
    else {
        error("Insertion failed: invalid position or list full.");
    }
}

void insert_first(ArrayListType* L, element item) {
    insert(L, 0, item);
}

void init(ArrayListType* L) {
    L->size = 0;
}

void clear(ArrayListType* L) {
    init(L);
}

element get_entry(ArrayListType* L, int pos) {
    if (pos >= 0 && pos < L->size) {
        return L->array[pos];
    }
    else {
        error("Access error: invalid position.");
        return -1; // 예외 처리를 위해 임의의 값 반환
    }
}

int get_length(ArrayListType* L) {
    return L->size;
}

int is_empty(ArrayListType* L) {
    return (L->size == 0);
}

void print_list(ArrayListType* L) {
    printf("List: ");
    for (int i = 0; i < L->size; i++) {
        printf("%d -> ", L->array[i]);
    }
    printf("NULL\n");
}

void insert_last(ArrayListType* L, element item) {
    int move = 0;
    if (L->size >= MAX_LIST_SIZE) {
        error("Insertion failed: list overflow.");
    }
    else {
        L->array[L->size++] = item;
        printf("Insertion complete. Data moved %d times.\n", move);
    }
}

void delete(ArrayListType* L, int pos) {
    int move = 0;
    if (pos < 0 || pos >= L->size) {
        error("Deletion failed: invalid position.");
    }
    else {
        for (int i = pos; i < L->size - 1; i++) {
            L->array[i] = L->array[i + 1];
            move++;
        }
        L->size--;
        printf("Deletion complete. Data moved %d times.\n", move);
    }
}

int main(void) {
    ArrayListType list;
    int choice = 1;
    init(&list);

    while (choice != 0) {
        printf("\nMenu:\n");
        printf("1. Insert in list\n");
        printf("2. Delete in list\n");
        printf("3. Print list\n");
        printf("0. Exit program\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (is_full(&list)) {
                printf("List is full.\n");
            }
            else {
                int num, pos;
                printf("Number: ");
                scanf("%d", &num);
                printf("Position: ");
                scanf("%d", &pos);
                insert(&list, pos, num);
            }
            break;
        case 2:
            if (is_empty(&list)) {
                printf("List is empty.\n");
            }
            else {
                int pos;
                printf("Position: ");
                scanf("%d", &pos);
                delete(&list, pos);
            }
            break;
        case 3:
            print_list(&list);
            break;
        case 0:
            printf("Exit program.\n");
            return 0;
        default:
            printf("Wrong choice, try again.\n");
        }
    }
    return 0;
}
