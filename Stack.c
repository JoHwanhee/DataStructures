#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct node{
	element data;
	struct node* link;
} Node;

typedef struct stack
{
	Node* top;
} Stack;

Stack* createStack();
void push(Stack** stack, element data);
element pop(Stack** stack);
element pick(Stack** stack);
int isEmpty(Stack** stack);
void printStack(Stack** stack);

int main(void)
{
	Stack* stack = createStack();

	int data = 31;
	printf("PUSH %d\n", data);
	push(&stack, 31);

	data = 27;
	printf("PUSH %d\n", data);
	push(&stack, data);

	data = 61;
	printf("PUSH %d\n", data);
	push(&stack, data);

	data = 90;
	printf("PUSH %d\n", data);
	push(&stack, data);
	
	printf("POP : %d\n", pop(&stack));
	printf("POP : %d\n", pop(&stack));

	printf("PICK : %d\n", pick(&stack));



	printStack(&stack);

	return 0;
}

Stack* createStack()
{
	Stack* stack = malloc(sizeof(Stack));
	stack->top = NULL;

	return stack;
}

void push(Stack** input_stack, element data)
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

element pop(Stack** input_stack)
{
	if (isEmpty(input_stack) == 1)
	{
		exit(1);
	}

	const int return_data = (*input_stack)->top->data;
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


element pick(Stack** input_stack)
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
		printf("Stack is null");
		return 1;
	}

	if ((*input_stack)->top == NULL)
	{
		printf("Stack is empty");
		return 1;
	}

	return 0;
}
