#include <stdio.h>
#include <stdlib.h>
#include "ItrTreeTrv.h"
#include "Stack.h"

void itr_inorder_traversal(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);
    while(nptr != NULL || !is_empty(&s)) {
        while(nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("[%2d] ", nptr->data);
        nptr = nptr->right;
    }
}