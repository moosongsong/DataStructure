
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;

	Node* cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return 0;
}

void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != NULL; node = node->next)
		printf("->[%2d]", node->data);
	getchar();
}

// ���� �ڷᱸ���� ������ �ڷᱸ���� �ʱ�ȭ�� ����ڰ� �ؾ� �Ѵٴ� ������ �ֽ��ϴ�.
// �̸� �ذ��ϱ� ���� �ڷᱸ���� �ʱ�ȭ�ϴ� �Լ��� �����ϵ��� �մϴ�.
int listInitialize() {
	head = calloc(1, sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}
	return 0;
}

int main() {
	//head = calloc(1, sizeof(Node));
	listInitialize();

	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}