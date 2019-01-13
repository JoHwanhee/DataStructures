#pragma once

typedef struct TreeNodeType {
	int data;
	int isNumber;
	struct TreeNodeType* left;
	struct TreeNodeType* right;
} TreeNode;

typedef struct tree {
	TreeNode* head;
} Tree;

