#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    p->data = value;
    p->link = h;
    return p;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (pre == NULL) {
        fprintf(stderr, "에러");
        return NULL;
    }

    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

void print_list(const ListNode* h) {
    while (h != NULL) {
        printf("[%d] ", h->data);
        h = h->link;
    }
}

ListNode* delete_First(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }
    ListNode* remove = head;
    head = remove->link;
    free(remove);
    return head;
}


ListNode* delete(ListNode* h, ListNode* pre) {
    ListNode* remove = pre->link;
    element r = pre->link->data;

    pre->link = remove->link;
    free(remove);

    return h;
}

int main() {
    ListNode* head = NULL;

    head = insert_first(head, 10);
    head = insert(head, head->link, 12);
    head = insert(head, head->link, 15);

    ListNode* p = head;

    for (int i = 0; i < 2; i++) {
        p = p->link;
    }
    head = insert(head, p, 40);
    print_list(head);

    element value;
    head = delete_First(head); // 함수 호출 수정
    free(head); // 메모리 해제 추가

    return 0;
}
