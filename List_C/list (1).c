
#include <stdlib.h>
#include <stdio.h>

// ��� ����
typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

// �����͸� �������� �߰��ϴ� listAdd �Լ��� ������ ������ :D
int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));	// malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	// node->next = NULL;

	// ���� ����Ʈ�� ��� �ִ� ���
	if (head == NULL) {
		head = node;
		return 0;
	}

	// ���� ����Ʈ�� ��� ���� ���� ���
	Node* cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return 0;
}

void listDisplay() {
	system("cls");	// clear("clear");
	printf("[head]");
	for (Node* node = head; node != NULL; node = node->next)
		printf("->[%2d]", node->data);
	getchar();
}

int main() {
	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}