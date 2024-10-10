#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// ʱȭ Լ
void init(LinkedStackType* s)
{
	s->top = NULL;
}
//    Լ
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
// ȭ   Լ
int is_full(LinkedStackType* s)
{
	return 0;
}
//  Լ
void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item->data; // 수정된 부분
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data = temp->data; // 수정된 부분
	s->top = temp->link;
	free(temp);
	return data; // 수정된 부분
}

void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data);  // implementation specific
	printf("NULL \n");
}

