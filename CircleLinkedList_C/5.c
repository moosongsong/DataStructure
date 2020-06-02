
#include <stdio.h>
#include <stdlib.h>


// ������ �ڷᱸ���� ���� Ÿ���� �����͸� ������ �� �ִٴ� ������ �ֽ��ϴ�.
// ���� ��� Ÿ���� ó���ϱ� ���� void*�� ����� �ڵ�� ������ ������ :D
typedef struct Node {
    void* data; // int data;
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

static void insertNode(Node* new, Node* prev, Node* next) {
    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
}

int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd: argument is null\n");
        return -1;
    }
    insertNode(node, head->prev, head);
    return 0;
}

int listAddHead(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAddHead: argument is null\n");
        return -1;
    }
    insertNode(node, head, head->next);
    return 0;
}

// ���� �ڵ�� ���̺귯���� �����ϴ� �ڵ��Դϴ�.
// ----------------------------------------------------------------------------------
// �Ʒ��� �ڵ�� ����ڰ� �����ϴ� �ڵ��Դϴ�.
typedef struct Person {
    char name[32];
    int age;
} Person;

void display(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "display(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->next; node != head; node = node->next) {
        // printf("<->[%2d]", node->data);
        Person* p = (Person*)node->data;
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

void displayBackwardly(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "displayBackwardly(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->prev; node != head; node = node->prev) {
        // printf("<->[%2d]", node->data);
        Person* p = (Person*)node->data;
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

int main(void) {
    Person people[4] = {
        {"eddy", 20}, {"pororo", 30}, {"petty", 40}, {"poby", 50}
    };

    Node nodes[4];

    Node head;
    listInitialize(&head);
    display(&head);
    for (int i = 0; i < 4; i++) {
        nodes[i].data = people + i; // nodes[i].data = &people[i];
        listAdd(&head, nodes + i);
        // listAddHead(&head, nodes + i);
        display(&head);
    }
    displayBackwardly(&head);
    return 0;
}
