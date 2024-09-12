#include <stdio.h>
#include <stdlib.h>
#include "ItrTreeTrv.h"

void itr_inorder_traversal(TreeNode* root);
int main(){
    
    TreeNode n1,n2,n3,n4,n5,n6;

    n1.data = 1;
    n2.data = 2;
    n3.data = 3;
    n4.data = 4;
    n5.data = 5;
    n6.data = 6;

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    

    itr_inorder_traversal(&n1);
    return 0;


}