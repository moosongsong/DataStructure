
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

// ���� �ڷᱸ���� ���� �˰����� �̿�ȭ�Ǿ� �ִٴ� ������ �ֽ��ϴ�.
// �̸� �ذ� �ϱ� ���� ���� ��带 �����մϴ�.

int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;

	//if (head == NULL) {
	//	head = node;
	//	return 0;
	//}

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

int main() {
	// ���� ��带 �߰��մϴ�.
	head = calloc(1, sizeof(Node)); //head = malloc(sizeof(Node));
									//head->next = NULL;


	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}