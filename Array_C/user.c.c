// 2.c���� ����ڰ� �����ϴ� �ڵ常 ������ ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Array.h"

// ���� �ڷᱸ���� ���� ������ ���е��� �ʾ� �ڵ尡 �ùٸ��� �������� ���� �� �ִٴ�
// ������ �ֽ��ϴ�. �̸� �ذ��ϱ� ���� ����ü ��� ������ ������ :D
typedef struct {
	char name[32];
	int age;
} Person;

const char* toPerson(const void* data) {
	static char buf[32];
	const Person* person = (const Person*)data;
	sprintf(buf, "%s(%d)", person->name, person->age);
	return (const char*)buf;
}

int main() {
	Person people[5] = {
		{"daniel",20}, {"susan",30}, {"pororo", 40}, {"eddy", 50}, {"poby",60}
	};

	Array* arr = arrayCreate();


	arrayDisplay(arr, toPerson);
	for (int i = 0; i < 4; i++) {
		arrayAdd(arr, people + i);
		arrayDisplay(arr, toPerson);
		// arr->contents = NULL;	// �� �ڵ尡 ������ �߻��ǵ��� �ڵ带 ������ ������ :D
	}

	arrayInsert(arr, 0, people + 4);
	arrayDisplay(arr, toPerson);

	arrayDestroy(arr);
}

// ���ۿ��� androidxref�� �˻��ϼ���


