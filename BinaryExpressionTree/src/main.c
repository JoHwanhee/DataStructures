#include <stdio.h>
#include <stdlib.h>
#include "TreeStack.h"
#include "TreeList.h"

int myIsDigit(int data)
{
	return (data >= 48) && (data <= 57);
}

int myAtoi(char* charArr, int size)
{
	int i;
	int sum = 0;
	int isNegative = 0;

	if(charArr[0] == '-')
	{
		isNegative = 1;
		i = 1;
	}
	else
	{
		i = 0;
	}

	for (; i < size; i++)
	{
		sum += charArr[i] - 48;

		if(i == size - 1)
		{
			sum *= 1;
		}
		else
		{
			sum *= 10;
		}
	}

	return isNegative ? -sum : sum;
}

void printList(TreeNodeList* list)
{
	TreeNodeList* temp = list;

	for (; temp != NULL; temp = temp->next)
	{
		if (temp->treeNode.isNumber)
		{
			printf("%d ", temp->treeNode.data);
		}
		else
		{
			printf("%c ", temp->treeNode.data);
		}
	}
}

int getLength(const char* str)
{
	int i = 0;
	while (str[i++] != '\0')
		;

	return i - 1;
}

void addTreeListNode(TreeNodeList** tree_list_head, TreeNodeList* tree_list_node)
{
	TreeNodeList* temp = *tree_list_head;
	
	for (; temp->next != NULL; temp = temp->next)
		;

	temp->next = tree_list_node;
}

TreeNodeList* charToLinkedList(char* fullChatArray, int size)
{
	int i;
	int index = 0;
	char* numberBuffer = malloc(sizeof(char)* 100);
	TreeNodeList* tree_list_head = NULL;
			
	for(i = 0; i < size; i++)
	{
		if(myIsDigit(fullChatArray[i]))
		{
			numberBuffer[index++] = (fullChatArray[i]);
		}
		else if(i != size -1)
		{
			TreeNode element;
			element.data = myAtoi(numberBuffer, index);
			element.isNumber = 1;
			element.left = NULL;
			element.right = NULL;
			TreeNodeList* numberNode = malloc(sizeof(TreeNodeList));
			numberNode->treeNode = element;
			numberNode->next = NULL;

			TreeNode operato;
			operato.data = fullChatArray[i];
			operato.isNumber = 0;
			operato.left = NULL;
			operato.right = NULL;
			TreeNodeList* operatorNode = malloc(sizeof(TreeNodeList));
			operatorNode->treeNode = operato;
			operatorNode->next = NULL;

			if (tree_list_head == NULL)
			{
				tree_list_head = numberNode;
			}
			else
			{
				addTreeListNode(&tree_list_head, numberNode);
			}

			addTreeListNode(&tree_list_head, operatorNode);
			index = 0;
		}
		

		if(i == size - 1)
		{
			TreeNode operato;
			operato.data = myAtoi(numberBuffer, index);
			operato.isNumber = 1;
			operato.left = NULL;
			operato.right = NULL;
			TreeNodeList* operatorNode = malloc(sizeof(TreeNodeList));
			operatorNode->treeNode = operato;
			operatorNode->next = NULL;
			addTreeListNode(&tree_list_head, operatorNode);
		}
	}

	return tree_list_head;
}

TreeNodeList* inFixToPostFix(TreeNodeList* expression)
{
	TreeNodeList* temp = expression;
	Stack* operatorStack = createStack();
	TreeNodeList* tree_list_head = NULL;
	for (; temp != NULL; temp = temp->next)
	{
		TreeNodeList* newNode = malloc(sizeof(TreeNodeList));
		newNode->treeNode = temp->treeNode;
		newNode->next = NULL;

		if (temp->treeNode.isNumber)
		{
			if (tree_list_head == NULL)
			{
				tree_list_head = newNode;
			}
			else
			{
				addTreeListNode(&tree_list_head, newNode);
			}
		}
		else if (temp->treeNode.data == '+' || temp->treeNode.data == '-')
		{
			while (!isEmpty(&operatorStack))
			{
				TreeNodeList* popNode = malloc(sizeof(TreeNodeList));
				popNode->treeNode = pop(&operatorStack);
				popNode->next = NULL;

				addTreeListNode(&tree_list_head, popNode);
			}

			push(&operatorStack, temp->treeNode);
		}
		else
		{
			push(&operatorStack, temp->treeNode);
		}
	}

	while (!isEmpty(&operatorStack))
	{
		TreeNodeList* popNode = malloc(sizeof(TreeNodeList));
		popNode->treeNode = pop(&operatorStack);
		popNode->next = NULL;

		addTreeListNode(&tree_list_head, popNode);
	}

	return tree_list_head;
}

Tree* createTree()
{
	Tree* tree = malloc(sizeof(Tree));
	tree->head = NULL;

	return tree;
}

TreeNode* clone(TreeNode target)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->data = target.data;
	node->isNumber = target.isNumber;
	node->right = target.right;
	node->left = target.left;
	
	return node;
}

TreeNode* createExpressionTree(TreeNodeList* expression)
{
	TreeNodeList* temp = expression;
	Stack* stack = createStack();

	for (; temp != NULL; temp = temp->next)
	{
		TreeNode node = temp->treeNode;

		if (node.isNumber)
		{
			push(&stack, node);
		}
		else
		{
			TreeNode right = pop(&stack);
			TreeNode* rightPtr = clone(right);
			node.right = rightPtr;
			
			TreeNode left = pop(&stack);
			TreeNode* leftPtr = clone(left);
			node.left = leftPtr;

			push(&stack, node);
		}
	}

	TreeNode node = pop(&stack);
	
	return clone(node);
}

void calcu(TreeNode* node)
{
}

double calculate(TreeNode* node)
{
	if (node == NULL)
	{
		return 0;
	}
	double left = 0;
	double right = 0;

	if (!node->isNumber)
	{
		left = (double)calculate(node->left);
		right = (double)calculate(node->right);

		if(node->data == '+')
		{
			return left + right;
		}
		if(node->data == '-')
		{
			return left - right;
		}
		if (node->data == '/')
		{
			return left / right;
		}
		if (node->data == '*')
		{
			return left * right;
		}
	}
	
	return node->data;
}

void preorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	if (node->isNumber)
	{
		printf("%d ", node->data);
	}
	else
	{
		printf("%c ", node->data);
	}
	preorder(node->left);
	preorder(node->right);
}

void inorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	inorder(node->left);
	if (node->isNumber)
	{
		printf("%d ", node->data);
	}
	else
	{
		printf("%c ", node->data);
	}
	inorder(node->right);
}

void postorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	postorder(node->left);
	postorder(node->right);
	if (node->isNumber)
	{
		printf("%d ", node->data);
	}
	else
	{
		printf("%c ", node->data);
	}
}

int main(void)
{
	char buffer[100];
	scanf_s("%s", buffer, sizeof(char) * 100);
	int read_text_size = getLength(buffer);
	
	TreeNodeList* inFix = charToLinkedList(buffer, read_text_size);
	TreeNodeList* postFix = inFixToPostFix(inFix);
	TreeNode* expTree = createExpressionTree(postFix);
	
	printf("\n\n preoder \n");
	preorder(expTree);
	
	printf("\n\n inoder \n");
	inorder(expTree);

	printf("\n\n postoder \n");
	postorder(expTree);

	printf("\n\n result \n");
	printf("%.2f", calculate(expTree));

	return 0;
}
