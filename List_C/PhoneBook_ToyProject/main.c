#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Array.h"

typedef struct {
	char name[32];
	char tel[32];
} Person;


#define STDIN_FLUSH()					\
	do {								\
		char ch;						\
		do {							\
			ch = getchar();				\
		} while(ch != '\n' && ch != EOF);	\
	} while(0)

void getString(const char* msg, char* out) {
	printf("%s: ", msg);
	scanf("%s", out);
	STDIN_FLUSH();
}

void pause(const char* msg) {
	printf("%s\n", msg);
	system("pause");
}

int menu() {
	system("cls");
	printf(
		"# ��ȭ��ȣ�� ���� ���α׷� #\n"
		"1. ���\n"
		"2. ����\n"
		"3. �˻�\n"
		"4. ����\n"
		"5. ���\n"
		"-------------------------\n"
		"�Է�(0. ����): "
	);
	int cmd;
	scanf("%d", &cmd);
	STDIN_FLUSH();
	return cmd;
}

int findPerson(const Array *array, const char* name) {
	for (int i = 0; i < arrayCount(array); i++) {
		Person* person = arrayGet(array, i);
		if (person != NULL) {
			if (strcmp(person->name, name) == 0) {
				return 1;
			}
		}
	}
	return 0;
}


void register_(Array *array) {
	system("cls");
	printf("# ��ȭ��ȣ�� ��� #\n");

	Person* p = malloc(sizeof(Person));
	getString("�̸� �Է�", p->name);
	if (findPerson(array, p->name)) {
		pause("�̹� ��ϵ� �̸��Դϴ�.");
		free(p);
		return;
	}

	getString("��ȭ��ȣ �Է�", p->tel);
	arrayAdd(array, p);
	pause("��ϵǾ����ϴ�.");
}


void edit(Array *array) {
	system("cls");
	printf("# ��ȭ��ȣ�� ���� #\n");

	char name[32];
	getString("�̸� �Է�", name);
	if (!findPerson(array, name)) {
		pause("�׷� �̸��� �����ϴ�.");
		return;
	}

	Person* person = NULL;
	for (int i = 0; i < arrayCount(array); i++) {
		person = arrayGet(array, i);
	}

	if (person != NULL) {
		getString("���ο� ��ȭ��ȣ �Է�", person->tel);
		pause("�����Ǿ����ϴ�.");
	}
}

void search(const Array *array) {
	system("cls");
	printf("# ��ȭ��ȣ�� �˻� #\n");

	char name[32];
	getString("�̸� �Է�", name);
	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		if (strcmp(p->name, name) == 0) {
			printf("��ȭ��ȣ�� %s�Դϴ�\n", p->tel);
			system("pause");
			return;
		}
	}
	pause("�׷� �̸��� �����ϴ�.");
}
void delete(Array *array) { 
	system("cls");
	printf("# ��ȭ��ȣ�� ���� #\n");

	char name[32];
	getString("�̸� �Է�", name);
	if (!findPerson(array, name)) {
		pause("�׷� �̸��� �����ϴ�.");
		return;
	}

	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		if (strcmp(p->name, name) == 0) {
			free(arrayRemove(array, i));
			pause("�����Ǿ����ϴ�.");
			return;
		}
	}
}
void list(const Array* array) {
	system("cls");
	printf("# ��ȭ��ȣ�� ��� #\n");

	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		printf("%d. %s, %s\n", i + 1, p->name, p->tel);
	}
	pause("��");
}

void run(Array *array) {
	while (1) {
		int cmd = menu();
		switch (cmd) {
		case 0: printf("���α׷��� �����մϴ�.\n"); return;
		case 1: register_(array); break;
		case 2: edit(array); break;
		case 3: search(array); break;
		case 4: delete(array); break;
		case 5: list(array); break;
		default:
			pause("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���.");
			continue;
		}
	}
}

int main() {
	Array* array = arrayCreate();
	if (array != NULL)
		run(array);
	arrayDestroy(array);
}