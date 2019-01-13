#pragma once
#include "tree.h"

typedef struct ListNode {
	TreeNode data;
	struct ListNode* link;
} Node;

typedef struct stack
{
	Node* top;
} Stack;

Stack* createStack();
void push(Stack** stack, TreeNode data);
TreeNode pop(Stack** stack);
TreeNode pick(Stack** stack);
int isEmpty(Stack** stack);
void printStack(Stack** stack);