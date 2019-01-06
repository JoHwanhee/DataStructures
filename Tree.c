#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct node
{
	int data;
	struct ndoe* left;
	struct ndoe* right;
} Node;

void setLeft(Node* parent, Node* child)
{
	if(parent == NULL || child == NULL)
	{
		return;
	}

	parent->left = child;
}

void setRight(Node* parent, Node* child)
{
	if (parent == NULL || child == NULL)
	{
		return;
	}

	parent->right = child;
}

int isEvenNumber(int number)
{
	return number % 2 == 0;
}

void preorder(Node* node)
{
	if(node == NULL)
	{
		return;
	}

	printf("%d ", node->data);
	preorder(node->left);
	preorder(node->right);
}

void inorder(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	inorder(node->left);
	printf("%d ", node->data);
	inorder(node->right);
}


void postorder(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	postorder(node->left);
	postorder(node->right);
	printf("%d ", node->data);
}





int main(int argc, char* argv[])
{
	Node* nodes = (Node*)malloc(sizeof(Node) * 16);

	for (int i = 1; i <= 15; ++i)
	{
		nodes[i].data = i;
		nodes[i].left = NULL;
		nodes[i].right = NULL;
	}

	for (int i = 1; i <= 15; ++i)
	{
		if(isEvenNumber(i))
		{
			setLeft(&nodes[i / 2], &nodes[i]);
		}
		else
		{
			setRight(&nodes[i / 2], &nodes[i]);
		}
	}


	printf("preorder!! \n");
	preorder(&nodes[1]);
	printf("\n");

	printf("inorder!! \n");
	inorder(&nodes[1]);
	printf("\n");

	printf("postorder!! \n");
	postorder(&nodes[1]);
	printf("\n");


	getchar();

	return 0;
}
