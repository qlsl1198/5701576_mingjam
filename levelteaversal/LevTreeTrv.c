#include <stdio.h>
#include <stdlib.h>
#include "LevTreeTrv.h"
#include "queue.h"



void level_order_traversal(TreeNode* root) {
    if (root == NULL) return;

    QueueType q;
    init_queue(&q);
    enqueue(&q, root); // 루트 노드를 큐에 추가

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q); // 큐에서 노드 꺼내기
        printf("%d ", current->data); // 노드 데이터 출력

        // 왼쪽 자식이 있으면 큐에 추가
        if (current->left != NULL) {
            enqueue(&q, current->left);
        }
        // 오른쪽 자식이 있으면 큐에 추가
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }
    printf("\n"); // 레벨 순회 후 개행
}