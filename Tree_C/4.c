#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
// ���� �˻� Ʈ��(BST)
typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
} Node;
Node* root;

int bstInsert(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("bstInsert");
		return -1;
	}
	node->data = data;
	if (root == NULL) {	// Ʈ���� ��� �ִ� ���
		root = node;
		return 0;
	}
	Node* parent = NULL;
	Node* cur = root;
	while (cur != NULL) {
		parent = cur;
		if (data < cur->data)
			cur = cur->left;
		else if (data > cur->data)
			cur = cur->right;
		else {
			free(node);
			return -1;
		}
	}
	if (data < parent->data) parent->left = node;
	else parent->right = node;
	return 0;
}

static void fillArray(int(*arr)[10], int* row, int* col, Node* node) {
	if (node == NULL)
		return;
	++(*row);
	fillArray(arr, row, col, node->left);
	arr[*row][(*col)++] = node->data;
	fillArray(arr, row, col, node->right);
	--(*row);
}

void bstDisplay() {
	int arr[10][10] = { 0, };
	int row = -1, col = 0;

	system("cls");
	fillArray(arr, &row, &col, root);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (arr[i][j])
				printf("(%2d)", arr[i][j]);
			else
				printf("%4c", ' ');
		}
		printf("\n");
	}
	getchar();
}

int bstGet(int key) {
	if (root == NULL)
		return -1;

	Node* cur = root;
	while (cur != NULL) {
		if (key < cur->data)
			cur = cur->left;
		else if (key > cur->data)
			cur = cur->right;
		else
			return cur->data;
	}
	return -1;
}

int bstRemove(int key, int* out) {
	if (root == NULL || out == NULL)
		return -1;

	Node* parent = NULL;
	Node* target = root;
	while (target != NULL && target->data != key) {
		parent = target;
		if (key < target->data)
			target = target->left;
		else if (key > target->data)
			target = target->right;
	}

	if (target == NULL)
		return -1;

	if ((target->left == NULL) && (target->right == NULL)) {	// �ܸ� ����� ���
		if (parent != NULL) {
			if (target == parent->left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else {	// ������ ��尡 ��Ʈ ����� ���
			root = NULL;
		}
	}
	else if ((target->left == NULL) || (target->right == NULL)) {
		// ������ ����� �ڽ� �����͸� ���
		Node* child;
		if (target->left == NULL)
			child = target->right;
		else
			child = target->left;

		// �ڽ� ��带 ������ ����� �θ� ��忡�� �Ծ�
		if (parent != NULL) {
			if (target == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		else {	// ������ ��尡 ��Ʈ�� ���
			root = child;
		}
	}
	else {	// 2���� �ڽ��� �ִ� ���
		Node* cParent = target;
		Node* candidate = target->right;

		// �ĺ� ��� ã��
		while (candidate->left != NULL) {
			cParent = candidate;
			candidate = candidate->left;
		}

		if (cParent->left == candidate)
			cParent->left = candidate->right;
		else
			cParent->right = candidate->right;

		int temp = target->data;
		target->data = candidate->data;
		candidate->data = temp;

		target = candidate;
	}

	*out = target->data;
	free(target);
	return 0;
}

int main() {
	bstDisplay();
	for (int i = 0; i < 8; i++) {
		bstInsert(i + 1);
		bstDisplay();
	}

	return 0;
}