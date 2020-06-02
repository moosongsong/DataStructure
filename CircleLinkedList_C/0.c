
#include <stdio.h>
#include <stdlib.h>

// ���� �ڷᱸ���� �޸� ��� ��å�� ����ڿ��� �����ϰ� �ִٴ� ������ �ֽ��ϴ�.
// �̸� �ذ� �ϱ����� �޸� �Ҵ� ��å�� ����ڿ��� �����ϵ��� �մϴ�.
typedef struct Node {
    int data;
    struct Node* next;
} Node;

int listInitialize(Node** head) {
    if (head == NULL) {
        fprintf(stderr, "listInitialize(): argument is null\n");
        return -1;
    }

    *head = calloc(1, sizeof(Node));
    if (*head == NULL) {
        perror("listInitialize()");
        return -1;
    }

    (*head)->next = *head;
    return 0;
}

void listFinalize(Node** head) {
    if (head == NULL) {
        fprintf(stderr, "listFinalize(): argument is null\n");
        return;
    }

    if (*head == NULL) {
        fprintf(stderr, "listFinalize(): list is wrong\n");
        return;
    }

    if ((*head)->next == *head) {
        fprintf(stderr, "listFinalize(): list is empty\n");
        return;
    }

    Node* cur = (*head)->next;
    while (cur->next != *head) {
        Node* target = cur;
        cur = cur->next;
        free(target);
    }

    free(*head);
    *head = NULL;
}

// �Ʒ��� �ڵ带 ������ ������ :D
// �Ʒ��� �ڵ带 �� �����Ͻ� �е��� �����͸� ���� �����ϴ� �ڵ�� ���ÿ� �����ϴ� �ڵ带
// 2�� �ۼ��� ������ :D -> main �Լ��� �����Ͻø� �˴ϴ�.
//int listAdd(Node* head, int data) {
int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd(): argument is null\n");
        return -1;
    }

    //Node* node = calloc(1, sizeof(Node));
    //if (node == NULL) {
    //    perror("listAdd()");
    //    return -1;
    //}
    //node->data = data;

    node->next = head;  // node->next = tail;

    Node* cur = head;
    while (cur->next != head)
        cur = cur->next;
    cur->next = node;

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
        printf("->[%2d]", node->data);
    printf("->[head]");
    getchar();
}

int listReverse(Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listReverse(): argument is null\n");
        return -1;
    }

    Node* prev = head;
    Node* cur = head->next;
    Node* next;

    while (cur != head) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    cur->next = prev;
    return 0;
}

int main(void) {
    Node* head;
    listInitialize(&head);

    Node nodes[5];  // ���ÿ� ����

    listDisplay(head);
    for (int i = 0; i < 5; i++) {
        //Node* node = malloc(sizeof(Node));  // ���� ����
        //node->data = i + 1;
        nodes[i].data = i + 1;
        listAdd(head, nodes + i);
        listDisplay(head);
    }

    listReverse(head), listDisplay(head);
    listReverse(head), listDisplay(head);

    listFinalize(&head);
    return 0;
}
