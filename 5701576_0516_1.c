#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트의 처음에 노드를 삽입하는 함수
ListNode* insert_first(ListNode* head, element value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->link = head;
    return newNode;
}

// 주어진 위치에 노드를 삽입하는 함수
ListNode* insert(ListNode* head, int pos, element value, int* move_count) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;

    *move_count = 0;
    if (pos == 0) {
        newNode->link = head;
        return newNode;
    }

    ListNode* p = head;
    while (*move_count < pos - 1 && p != NULL) {
        p = p->link;
        (*move_count)++;
    }

    if (p == NULL) {
        fprintf(stderr, "오류: 위치가 리스트 길이를 초과했습니다\n");
        free(newNode);
        return head;
    }

    newNode->link = p->link;
    p->link = newNode;
    (*move_count)++;
    return head;
}

// 주어진 위치의 노드를 삭제하는 함수
ListNode* delete(ListNode* head, int pos, int* move_count) {
    *move_count = 0;

    if (head == NULL) {
        fprintf(stderr, "오류: 빈 리스트\n");
        return NULL;
    }

    ListNode* temp;
    if (pos == 0) {
        temp = head;
        head = head->link;
        free(temp);
        (*move_count)++;
        return head;
    }

    ListNode* p = head;
    while (*move_count < pos - 1 && p->link != NULL) {
        p = p->link;
        (*move_count)++;
    }

    if (p->link == NULL) {
        fprintf(stderr, "오류: 위치가 리스트 길이를 초과했습니다\n");
        return head;
    }

    temp = p->link;
    p->link = temp->link;
    free(temp);
    (*move_count) += 2;
    return head;
}

// 리스트를 출력하는 함수
void print_list(const ListNode* head) {
    const ListNode* p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL \n");
}

// 메인 함수
int main() {
    ListNode* head = NULL;
    int choice, value, pos, move_count;

    while (1) {
        printf("메뉴:\n");
        printf("1. 리스트에 추가\n");
        printf("2. 리스트에서 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가 할 숫자: ");
            scanf("%d", &value);
            printf("추가 할 위치 : ");
            scanf("%d", &pos);
            head = insert(head, pos, value, &move_count);
            printf("이동한 링크 수: %d\n", move_count);
            break;
        case 2:
            printf("삭제할 위치 입력: ");
            scanf("%d", &pos);
            head = delete(head, pos, &move_count);
            printf("이동한 링크 수: %d\n", move_count);
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            // 리스트 메모리 해제
            while (head != NULL) {
                head = delete(head, 0, &move_count);
            }
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}
