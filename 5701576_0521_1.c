#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUITS 10
#define MAX_NAME_LENGTH 50

typedef struct ListNode {
    char fruit[MAX_NAME_LENGTH];
    struct ListNode* link;
} ListNode;

const char* initial_fruits[MAX_FRUITS] = {
    "Mango", "Orange", "Apple", "Grape", "Cherry",
    "Plum", "Guava", "Raspberry", "Banana", "Peach"
};

ListNode* insert_last(ListNode* head, ListNode** tail, const char* fruit) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->fruit, fruit);
    newNode->link = NULL;

    if (head == NULL) {
        *tail = newNode;
        return newNode;
    }

    (*tail)->link = newNode;
    *tail = newNode;
    return head;
}

ListNode* delete_fruit(ListNode* head, ListNode** tail, const char* fruit, ListNode** deleted_head) {
    ListNode* p = head, * prev = NULL;

    while (p != NULL && strcmp(p->fruit, fruit) != 0) {
        prev = p;
        p = p->link;
    }

    if (p == NULL) {
        printf("해당 과일이 리스트에 없습니다.\n");
        return head;
    }

    if (prev == NULL) {
        head = head->link;
    }
    else {
        prev->link = p->link;
    }

    if (*tail == p) {
        *tail = prev;
    }

    p->link = *deleted_head;
    *deleted_head = p;

    printf("과일 '%s'을(를) 삭제했습니다.\n", fruit);
    return head;
}

void print_list(const ListNode* head) {
    const ListNode* p = head;
    while (p != NULL) {
        printf("%s ", p->fruit);
        p = p->link;
    }
    printf("\n");
}

int is_fruit_found(const ListNode* head, const char* fruit) {
    const ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->fruit, fruit) == 0) {
            return 1;
        }
        p = p->link;
    }
    return 0;
}

// 메인 함수
int main() {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    ListNode* deleted_head = NULL;
    int choice;
    char fruit[MAX_NAME_LENGTH];

    // 초기 과일 리스트 생성
    for (int i = 0; i < MAX_FRUITS; i++) {
        head = insert_last(head, &tail, initial_fruits[i]);
    }

    while (1) {
        printf("메뉴:\n");
        printf("1. 리스트의 마지막에 과일 추가\n");
        printf("2. 리스트에서 과일 삭제\n");
        printf("3. 삭제된 과일 목록 출력\n");
        printf("4. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 과일 입력: ");
            scanf("%s", fruit);
            if (is_fruit_found(head, fruit)) {
                printf("[%s] 이미 리스트에 존재합니다.\n", fruit);
            }
            else {
                head = insert_last(head, &tail, fruit);
                printf("[%s] 리스트에 추가했습니다.\n", fruit);
            }
            break;
        case 2:
            printf("삭제할 과일 이름 입력: ");
            scanf("%s", fruit);
            head = delete_fruit(head, &tail, fruit, &deleted_head);
            break;
        case 3:
            printf("삭제된 과일 목록:\n");
            print_list(deleted_head);
            break;
        case 4:
            while (head != NULL) {
                ListNode* temp = head;
                head = head->link;
                free(temp);
            }
            while (deleted_head != NULL) {
                ListNode* temp = deleted_head;
                deleted_head = deleted_head->link;
                free(temp);
            }
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}
