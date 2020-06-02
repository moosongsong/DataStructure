
#include <stdio.h>
#include <stdlib.h>

// ���� �ڷᱸ���� �� ���������� ������ Ž���� ���� ����� ���ٴ� ������ �ֽ��ϴ�.
// �̸� �ذ��ϱ� ���� ���� ���� ����Ʈ�� �����մϴ�.

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

int listInitialize(Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listInitialize(): argument is null\n");
        return -1;
    }
    head->next = head;
    head->prev = head;
    return 0;
}

// �Ʒ��� �Լ��� ������ ������ :D
int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd(): argument is null\n");
        return -1;
    }
    node->next = head;
    head->prev->next = node;
    node->prev = head->prev;
    head->prev = node;

    return 0;
}

int listAddHead(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAddHead(): argument is null\n");
        return -1;
    }

    node->next = head->next;
    head->next = node;
    node->prev = node->next->prev;
    node->next->prev = node;
    return 0;
}


void listDisplay(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listDisplay(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->next; node != head; node = node->next)
        printf("<->[%2d]", node->data);
    printf("<->[head]");
    getchar();
}

void listDisplayBackwardly(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listDisplayBackwardly(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->prev; node != head; node = node->prev)
        printf("<->[%2d]", node->data);
    printf("<->[head]");
    getchar();
}

int main(void) {
    Node nodes[5];  // ���ÿ� ����

    Node head;
    listInitialize(&head);
    listDisplay(&head);
    for (int i = 0; i < 5; i++) {
        nodes[i].data = i + 1;
        //listAdd(&head, nodes + i);
        listAddHead(&head, nodes + i);
        listDisplay(&head);
    }

    listDisplayBackwardly(&head);
    return 0;
}
