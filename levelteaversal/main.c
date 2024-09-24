#include <stdio.h>
#include <stdlib.h>
#include "LevTreeTrv.h"

int main() {
    // 트리 생성 예시
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 9;
    root->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->data = 6;
    root->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->data = 5;
    root->left->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->left->data = 3;
    root->left->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->right->data = 7;
    root->right->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->left->data = 8;

    // 레벨 순회 호출
    printf("레벨 순회 결과: ");
    level_order_traversal(root);

    // 메모리 해제 (생략)
    return 0;
}

