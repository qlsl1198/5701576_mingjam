#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENTS];
    int heap_size;
 } HeapType;


void init_heap(HeapType* h) {
    h->heap_size = 0;
}

HeapType* create_heap() {
    HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
    return heap;
}

void destroy_heap(HeapType* h) {
    free(h);
}

int is_empty_heap(HeapType* h) {
    return h->heap_size == 0;
}

int is_full_heap(HeapType* h) {
    return h->heap_size == MAX_ELEMENTS - 1;
}

void insert_max_heap(HeapType* h, element item) {
    int i = h->heap_size + 1;

    if (is_full_heap(h)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }

    while ((i != 1) && (item.key > h->heap[i/2].key)) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
    (h->heap_size)++;
}

// void insert_min_heap(HeapType* h, element item) {
//     int i = h->heap_size + 1;
//     if (is_full_heap(h)) {
//         fprintf(stderr, "The heap is full.\n");
//         exit(1);
//     }
//     while ((i != 1) && (item.key < h->heap[i/2].key)) {
//         h->heap[i] = h->heap[i/2];
//         i /= 2;
//     }
//     h->heap[i] = item;
//     (h->heap_size)++;
// }

element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    if (is_empty_heap(h)) {
        fprintf(stderr, "The heap is empty.\n");
        exit(1);
    }
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    for (parent = 1 , child = 2; child <= h->heap_size; parent = child, child *= 2) {
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child+1].key))
            child++;
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
    }
    h->heap[parent] = temp;
    return item;
}

// element delete_min_heap(HeapType* h) {
//     int parent, child;
//     element item, temp;
//     if (is_empty_heap(h)) {
//         fprintf(stderr, "The heap is empty.\n");
//         exit(1);
//     }
//     item = h->heap[1];
//     temp = h->heap[(h->heap_size)--];
//     parent = 1;
//     child = 2;
//     for (parent = 1 , child = 2; child <= h->heap_size; parent = child, child *= 2) {
//         if ((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
//             child++;
//         if (temp.key <= h->heap[child].key) break;
//         h->heap[parent] = h->heap[child];
//     }
//     h->heap[parent] = temp;
//     return item;
// }

element find_max_heap(HeapType* h) {
    if (is_empty_heap(h)) {
        fprintf(stderr, "The heap is empty.\n");
        exit(1);
    }
    return h->heap[1];
}

void display_heap(HeapType* h) {
    int i;
    for (i = 1; i <= h->heap_size; i++) {
        printf("%d(%d) ", h->heap[i].key, i);
    }
    printf("\n");
}


void GenerateMaxHeap(HeapType* h) {
    int i;
    int arr[] = {10, 5, 30, 20, 40, 25, 35, 45, 50, 60};
    for (i = 0; i < 10; i++) {
        element item;
        item.key = arr[i];
        insert_max_heap(h, item);
    }
}

// void GenerateMinHeap(HeapType* h) {
//     int i;
//     int arr[] = {10, 5, 30, 20, 40, 25, 35, 45, 50, 60};
//     for (i = 0; i < 10; i++) {
//         element item;
//         item.key = arr[i];
//         insert_min_heap(h, item);
//     }
// }

char menu() {
    char choice;    
    printf("i: 노드추가\nd: 노드삭제\np: 레벨별 출력\nc: 종료\n");
    printf("Enter your choice: ");
    scanf("%c", &choice);
    return choice;
}

void user_interface(HeapType* heap) {
    char choice;
    element item;

    while ((choice = menu()) != 'c') {
        switch (choice) {
            case 'i':
                printf("추가할 원소: ");
                scanf("%d", &item.key);
                insert_max_heap(heap, item);
                break;
            case 'd':
                item = delete_max_heap(heap);
                printf("삭제된 원소: %d\n", item.key);
                break;
            case 'p':
                display_heap(heap);
                break;
            case 'c':
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }
}


int main() {
    HeapType* heap = create_heap();
    char choice;
    element item;

    user_interface(heap);
    destroy_heap(heap);
    return 0;
}
