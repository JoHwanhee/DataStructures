#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct node
{
	Element data;
	struct node* next;
	struct node* previous;
} Node;

typedef struct list
{
	struct node* head;
} List;

void add(List** list, int index, Element data);
void addFirst(List** list, Element data);
void addLast(List** list, Element data);
void removeNode(List** list, int index);
void removeAll(List** list);
void reverse(List** list);
int size(List** list);
// order 1이면 내림차순, 0 이면 오름차순
void sort(List* list, int order);
Node* get(List** list, int index);
void printAll(List* list);

void init(List** list, Element data);
Node* moveNode(List** list, int index);
Node* makeNode(Element data);
void println();

int main()
{
	List* list = NULL;

	add(&list, 0, 1);
	add(&list, 1, 2);
	add(&list, 2, 3);
	add(&list, 3, 15);
	add(&list, 4, 15);
	addFirst(&list, 1);
	addLast(&list, 5);
	removeNode(&list, 2);
	reverse(&list);
	printAll(list);
	printf("The value of 4th : %d\n", get(&list, 4)->data);
	printf("The size : %d", size(&list));
	removeAll(&list);
}

void init(List** list, Element data)
{
	if (*list == NULL)
	{
		*list = malloc(sizeof(List));
		(*list)->head = malloc(sizeof(Node));
		(*list)->head->data = data;
		(*list)->head->next = NULL;
		(*list)->head->previous = NULL;
	}
}


void add(List** list, int index, Element data)
{
	if (*list == NULL)
	{
		init(list, data);
		return;
	}

	if (index == 0)
	{
		Node* head = (*list)->head;
		Node* newNode = makeNode(data);
		newNode->next = head;
		head->previous = newNode;

		(*list)->head = newNode;
	}
	else
	{
		Node* current = moveNode(list, index - 1);
		Node* newNode = makeNode(data);
		Node* nextNode = current->next;

		newNode->next = nextNode;

		if (nextNode != NULL)
		{
			nextNode->previous = newNode;
		}

		current->next = newNode;
		newNode->previous = current;
	}
}

void addFirst(List** list, Element data)
{
	add(list, 0, data);
}

void addLast(List** list, Element data)
{
	add(list, size(list), data);
}

void removeNode(List** list, Element index)
{
	Node* previous = moveNode(list, index - 1);
	Node* current = previous->next;

	if (current != NULL)
	{
		Node* next = current->next;

		previous->next = next;
		next->previous = previous;

		free(current);
	}
}

void removeAll(List** list)
{
	Node* movingNode = (*list)->head;
	Node* temp = NULL;
	for (int i = 0; movingNode != NULL; i++)
	{
		temp = movingNode;
		movingNode = movingNode->next;

		if (temp != NULL) free(temp);
	}
}

void reverse(List** list)
{
	Node* current = (*list)->head;
	int index = 0;

	for (; current->next != NULL; index++)
	{
		current = current->next;
	}

	int isFirst = 1;
	for (; current != NULL; index--)
	{
		if (isFirst == 1)
		{
			(*list)->head = makeNode(current->data);
			isFirst = 0;
		}
		else
		{
			addLast(list, current->data);
		}

		Node* temp = current;
		current = current->previous;
		free(temp);
	}
}

int size(List** list)
{
	Node* temp = (*list)->head;
	int i = 0;

	for (; temp != NULL; temp = temp->next, i++)
		;

	return i;
}

void sort(List* list, int order)
{
	List* bucket = NULL;
	init(&bucket, 0);


}

Node* get(List** list, int index)
{
	Node* temp = (*list)->head;
	int i = 0;

	for (; i < index; temp = temp->next, i++)
		;

	return temp;
}

void printAll(List* list)
{
	Node* temp = list->head;
	for (int i = 0; temp != NULL; i++)
	{
		printf("[%d] %d \n", i, temp->data);
		temp = temp->next;
	}
}

Node* moveNode(List** list, int index)
{
	if ((*list)->head == NULL)
	{
		return NULL;
	}

	if (index == 0)
	{
		return (*list)->head;
	}

	Node* temp = (*list)->head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}

	return temp;
}

Node* makeNode(Element data)
{
	Node* newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->previous = NULL;

	return newNode;
}

void println()
{
	printf("\n");
}