
#include <stdlib.h>
#include <stdio.h>

// 1. �ؽ� ������ Ÿ�� ����
#define KEY_LEN_MAX		(32)
#define VALUE_LEN_MAX	(92)
typedef struct HashData {
	char key[KEY_LEN_MAX];
	char value[VALUE_LEN_MAX];
} HashData;

// 2. �ؽø� ���� ����ü(context) ����
typedef struct Hashmap {
	size_t count;		// �ؽøʿ� ����� �������� ����
	size_t capacity;	// �ؽøʿ� ������ �� �ִ� �ִ� ������ ����
	size_t offsets[];
} Hashmap;

Hashmap* hashmapCreate(size_t nData) {
	if (nData == 0) {
		fprintf(stderr, "hashmapCreate: argument is zero\n");
		return NULL;
	}

	size_t mapSize = sizeof(Hashmap) +  (sizeof(size_t) * nData) + (sizeof(HashData) * nData);
	Hashmap* map = calloc(1, mapSize);
	if (map == NULL) {
		perror("hashmapCreate");
		return NULL;
	}
	map->capacity = nData;
	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;
	free(map);
}

int main() {
	Hashmap* map = hashmapCreate(10);
	if (map == NULL)
		return -1;

	hashmapDestroy(map);
}
