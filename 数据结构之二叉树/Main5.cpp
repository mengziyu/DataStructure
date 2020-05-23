#pragma  warning (disable:4996) 
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode
{
	char data[10];
	TreeNode* left_node = NULL;
	TreeNode* right_node = NULL;
};

//前序遍历
void fore_order(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	printf("%s",root->data);
	fore_order(root->left_node);
	fore_order(root->right_node);
}

void mid_order(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	mid_order(root->left_node);
	printf("%s", root->data);
	mid_order(root->right_node);
}

void after_order(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	after_order(root->left_node);
	after_order(root->right_node);
	printf("%s", root->data);
}

int size(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + size(root->left_node)+size(root->right_node);
}
int height(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	else
	{
		int left_h = 1 + height(root->left_node);
		int right_h = 1 + height(root->right_node);
		return left_h > right_h ? left_h : right_h;
	}
}

void main() {
	/*
		 二叉树
			A
		   / \
		  B   C
	     / \   \
		D   E   F
	
	*/

	TreeNode root;
	strcpy(root.data,"A");

	TreeNode nodeB;
	strcpy(nodeB.data, "B");

	TreeNode nodeC;
	strcpy(nodeC.data, "C");

	TreeNode nodeD;
	strcpy(nodeD.data, "D");

	TreeNode nodeE;
	strcpy(nodeE.data, "E");

	TreeNode nodeF;
	strcpy(nodeF.data, "F");

	root.left_node = &nodeB;
	root.right_node = &nodeC;
	nodeB.left_node = &nodeD;
	nodeB.right_node = &nodeE;
	nodeC.right_node = &nodeF;

	printf("==========遍历=========");
	printf("\n");
	fore_order(&root);
	printf("\n");
	mid_order(&root);
	printf("\n");
	after_order(&root);
	printf("\n");

	printf("size:%d",size(&root));
	printf("\n");
	printf("height:%d", height(&root));
	printf("\n");
}