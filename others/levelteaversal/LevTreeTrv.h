#pragma once  
#include "LevTreeTrv.c"

typedef int value;

struct tree_node{
    value data;
    struct tree_node* left, *right;
};


typedef struct tree_node TreeNode;
extern void level_order_traversal(TreeNode* root); // 레벨 순회 함수 추가