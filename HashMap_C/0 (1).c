
// ��� ����
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char* key;
	char* value;
	struct Node* next;
} Node;

typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;
} Hashmap;

Hashmap* hashmapCreate(size_t bucketSize) {
	if (bucketSize == 0) {
		fprintf(stderr, "hashmapCreate: bucket size is zero\n");
		return NULL;
	}

	Node** buckets = calloc(bucketSize, sizeof(Node*));
	if (buckets == NULL) {
		perror("hashmapCreate");
		return NULL;
	}

	Hashmap* map = calloc(1, sizeof(Hashmap));
	if (map == NULL) {
		perror("hashmapCreate");
		free(buckets);
		return NULL;
	}

	map->buckets = buckets;
	map->bucketSize = bucketSize;
	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;

	// �ڿ��� ������ ������ �������� �ؾ� �մϴ�.
	free(map->buckets);
	free(map);
}

int main() {
	Hashmap* map = hashmapCreate(10);
	
	hashmapDestroy(map);
}