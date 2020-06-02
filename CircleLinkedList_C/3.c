
#include <stdio.h>
#include <stdlib.h>


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

// ���� �ڷᱸ���� ��� ���� ��å�� �̿�ȭ�Ǿ� �ִٴ� ������ �ֽ��ϴ�.
// �̸� �ذ��ϱ� ���� ���� ��å�� �Ͽ�ȭ �Ǵ� �Ϲ�ȭ�غ����� �մϴ�.
int insertNode(Node* new, Node* prev, Node* next) {
    if (new == NULL || prev == NULL || next == NULL)
        return -1;

    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
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
        // insertNode(nodes + i, head.prev, &head);     //listAdd(&head, nodes + i);
        insertNode(nodes + i, &head, head.next);       // listAddHead(&head, nodes + i);
        listDisplay(&head);
    }

    listDisplayBackwardly(&head);
    return 0;A
}
