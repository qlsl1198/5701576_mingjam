#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink, * rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead->rlink = phead;
}

void dinsert_first(DListNode* head, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = head;
    newnode->rlink = head->rlink;
    head->rlink->llink = newnode;
    head->rlink = newnode;
}

void dinsert_last(DListNode* head, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = head->llink;
    newnode->rlink = head;
    head->llink->rlink = newnode;
    head->llink = newnode;
}

void ddelete_first(DListNode* head) {
    if (head->rlink == head) return;
    DListNode* removed = head->rlink;
    head->rlink = removed->rlink;
    removed->rlink->llink = head;
    free(removed);
}

void ddelete_last(DListNode* head) {
    if (head->rlink == head) return;
    DListNode* removed = head->llink;
    head->llink = removed->llink;
    removed->llink->rlink = head;
    free(removed);
}

void print_dlist(DListNode* head) {
    DListNode* p; 
    for (p = head->rlink; p != head; p = p->rlink) {
        printf("%d -> ", p->data);
    }
    printf("(head) \n");
}

int main() {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    int choice;
    element data;

    while (1) {
        printf("\n\n[메뉴]\n");
        printf("(1) 숫자 입력 받아서 리스트 처음에 추가\n");
        printf("(2) 숫자 입력 받아서 리스트 마지막에 추가\n");
        printf("(3) 리스트 처음 노드 삭제\n");
        printf("(4) 리스트 마지막 노드 삭제\n");
        printf("(5) 리스트 프린트\n");
        printf("(6) 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 숫자 입력: ");
            scanf("%d", &data);
            dinsert_first(head, data);
            printf("리스트에 %d 추가됨.\n", data);
            break;
        case 2:
            printf("추가할 숫자 입력: ");
            scanf("%d", &data);
            dinsert_last(head, data);
            printf("리스트에 %d 추가됨.\n", data);
            break;
        case 3:
            if (head->rlink == head) {
                printf("리스트가 비어있습니다.\n");
            }
            else {
                ddelete_first(head);
                printf("리스트의 처음 노드 삭제됨.\n");
            }
            break;
        case 4:
            if (head->rlink == head) {
                printf("리스트가 비어있습니다.\n");
            }
            else {
                ddelete_last(head);
                printf("리스트의 마지막 노드 삭제됨.\n");
            }
            break;
        case 5:
            if (head->rlink == head) {
                printf("리스트가 비어있습니다.\n");
            }
            else {
                printf("리스트 출력: ");
                print_dlist(head);
            }
            break;
        case 6:
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }

    return 0;
}
