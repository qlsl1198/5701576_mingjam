#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead->rlink = phead;
}

void dinsert(DListNode* current, element data) {
    if (current == NULL) {
        printf("현재 노드가 유효하지 않습니다.\n");
        return;
    }

    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    if (newnode == NULL) {
        printf("메모리 할당 오류입니다.\n");
        return;
    }

    strcpy(newnode->data, data);
    newnode->rlink = current->rlink;
    newnode->llink = current;
    current->rlink->llink = newnode;
    current->rlink = newnode;
}

void ddelete(DListNode* current) {
    if (current == NULL) {
        printf("현재 노드가 유효하지 않습니다.\n");
        return;
    }

    if (current->llink == current || current->rlink == current) {
        printf("유효한 노드가 하나뿐이므로 삭제할 수 없습니다.\n");
        return;
    }

    DListNode* removed = current;
    current->llink->rlink = current->rlink;
    current->rlink->llink = current->llink;
    current = current->llink;  // 현재 노드를 이전 노드로 변경
    free(removed);
}

void print_dlist(DListNode* head, DListNode* current) {
    DListNode* p;
    for (p = head->rlink; p != head; p = p->rlink) {
        printf("%s", p->data);
        if (p == current)
            printf(" <==");
        printf("\n");
    }
}

void print_menu() {
    printf("\n N(다음), P(이전), I(삽입), D(삭제), Q(종료): ");
}

char get_command() {
    char command;
    scanf(" %c", &command);
    return command;
}

DListNode* do_command(DListNode* head, DListNode* current, char cmd) {
    element data;

    switch (cmd) {
    case 'N':
        if (current == NULL) {
            printf("현재 노드가 유효하지 않습니다.\n");
            return current;
        }
        if (current->rlink == head) {
            return head->rlink; // 첫 번째 노드로 이동
        }
        return current->rlink;
    case 'P':
        if (current == NULL) {
            printf("현재 노드가 유효하지 않습니다.\n");
            return current;
        }
        if (current == head->rlink) {
            return head->llink; // 마지막 노드로 이동
        }
        return current->llink;
    case 'I':
        printf("\n노래 제목 입력: ");
        scanf("%s", data);
        dinsert(current, data);
        printf("%s를 현재 노드 뒤에 삽입했습니다.\n", data);
        return current->rlink;  // 현재 노드를 다음 노드로 변경
    case 'D':
        ddelete(current);
        printf("현재 노드를 삭제했습니다.\n");
        return current->llink;  // 삭제 후 현재 노드를 이전 노드로 변경
    case 'Q':
        printf("프로그램을 종료합니다.\n");
        exit(0);
    default:
        printf("잘못된 명령입니다.\n");
        return current;
    }
}

int main() {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    if (head == NULL) {
        printf("메모리 할당 오류입니다.\n");
        return -1;
    }
    init(head);

    // 초기에 리스트에 팝송 5개를 추가
    element songs[5] = { "Song1", "Song2", "Song3", "Song4", "Song5" };
    DListNode* current = head;
    for (int i = 0; i < 5; ++i) {
        dinsert(current, songs[i]);
        current = current->rlink;
        for (int i = 0; i < 5; ++i) {
            dinsert(current, songs[i]);
            current = current->rlink;
        }

        char command;

        while (1) {
            printf("\n현재 리스트:\n");
            print_dlist(head, current);
            print_menu();
            command = get_command();
            current = do_command(head, current, command);
        }
    }

}
