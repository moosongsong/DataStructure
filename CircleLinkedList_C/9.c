
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    struct Node* prev;
} Node;

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

#define list_entry(ptr, type, member)    \
    (type*)((char*)ptr - (long)&((type*)0)->member)

#define list_foreach(node, head)    \
    for (node = head->next; node != head; node = node->next)
 
#define list_foreach_reverse(node, head)    \
    for (node = head->prev; node != head; node = node->prev)

#define LIST_HEAD(name) \
    Node name = { &(name), &(name)}

// ���� �ڵ�� ���̺귯���� �����ϴ� �ڵ��Դϴ�.
// ----------------------------------------------------------------------------------
// �Ʒ��� �ڵ�� ����ڰ� �����ϴ� �ڵ��Դϴ�.

// ������ �ڵ�� �ڷᱸ���� Ž���� ��ƴٴ� ������ �ֽ��ϴ�. �̸� �ذ��ϱ� ����
// �ݺ��� ���� �Լ��� �����մϴ�.
typedef struct Person {
    char name[32];
    int age;
    Node list;
} Person;

void display(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "display(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    Node* node;
    list_foreach(node, head) {
        Person* p = list_entry(node, Person, list);
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
    Node* node;
    list_foreach_reverse(node, head) {
        Person* p = list_entry(node, Person, list);
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

int main(void) {
    Person people[4] = {
        {"eddy", 20}, {"pororo", 30}, {"petty", 40}, {"poby", 50}
    };

    //Node head;
    //listInitialize(&head);
    LIST_HEAD(head);

    display(&head);
    for (int i = 0; i < 4; i++) {
        listAdd(&head, &(people[i].list));
        display(&head);
    }
    displayBackwardly(&head);
    return 0;
}
