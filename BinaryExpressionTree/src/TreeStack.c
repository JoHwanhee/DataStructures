#include <stdio.h>
#include <stdlib.h>
#include "TreeStack.h"

Stack* createStack()
{
	Stack* stack = malloc(sizeof(Stack));
	stack->top = NULL;

	return stack;
}

void push(Stack** input_stack, TreeNode data)
{
	if ((*input_stack) == NULL)
	{
		printf("Stack is null");
		exit(1);
	}

	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->link = (*input_stack)->top;
	(*input_stack)->top = newNode;
}

TreeNode pop(Stack** input_stack)
{
	if (isEmpty(input_stack) == 1)
	{
		exit(1);
	}

	const TreeNode return_data = (*input_stack)->top->data;
	Node* temp = (*input_stack)->top->link;

	free((*input_stack)->top);
	(*input_stack)->top = temp;

	return return_data;
}

void printStack(Stack** input_stack)
{
	if(isEmpty(input_stack) == 1)
	{
		exit(1);
	}

	Node* temp = (*input_stack)->top;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->link;
	}
}


TreeNode pick(Stack** input_stack)
{
	if(isEmpty(input_stack) == 0)
	{
		return (*input_stack)->top->data;
	}

	exit(1);
}

int isEmpty(Stack** input_stack)
{
	if ((*input_stack) == NULL)
	{
		return 1;
	}

	if ((*input_stack)->top == NULL)
	{
		return 1;
	}

	return 0;
}

