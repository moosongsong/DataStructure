
// �ε� ����: ������
// ��Ŷ�� ũ�⸦ Ȯ���ϴ� �Ӱ���
// ������ ������ ���� > ������ * ���� �ؽ��� ��Ŷ ��

// ������: 75%
// �Ӱ����� �Ѿ�� ��Ŷ�� ���� 2��� �ø��ϴ�. -> ���ؽ�(rehashing)
// �Ӱ����� �Ѿ�� 2��� ���ؽ̵Ƿη� �ڵ带 ������ ������ :D
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	void* key;
	void* value;
	int hash;
	struct Node* next;
} Node;

typedef int(*HashFn)(void* key);
typedef int(*EqualsFn)(void* key1, void* key2);
typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;
	HashFn hash;
	EqualsFn equlas;
} Hashmap;

static size_t calculateIndex(size_t bucketSize, int hash) {
	return ((size_t)hash) & (bucketSize - 1);
}

#define DEFALUT_BUCKET_SIZE		(1)
static int expandIfNessary(Hashmap* map) {
	if (map == NULL) {
		fprintf(stderr, "expandIfNessary: argument is null\n");
		return -1;
	}

	if (map->count <= (map->bucketSize * 3 / 4))
		return 0;

	size_t newBucketSize = map->bucketSize << 1;  // or map->bucketSize * 2;
	Node** newBuckets = calloc(newBucketSize, sizeof(Node*));
	if (newBuckets == NULL) {
		perror("expandIfNassary");
		return -1;
	}

	for (size_t i = 0; i < map->bucketSize; i++) {
		Node* cur = map->buckets[i];
		while (cur != NULL) {
			Node* next = cur->next;
			size_t index = calculateIndex(newBucketSize, cur->hash);
			cur->next = newBuckets[index];
			newBuckets[index] = cur;
			cur = next;
		}
	}

	free(map->buckets);
	map->buckets = newBuckets;
	map->bucketSize = newBucketSize;
	return 0;
}

Hashmap* hashmapCreate(HashFn hash, EqualsFn equals) {
	if (hash == NULL || equals == NULL) {
		fprintf(stderr, "hashmapCreate: argument is null\n");
		return NULL;
	}

	Hashmap* map = calloc(1, sizeof(Hashmap));
	if (map == NULL) {
		perror("hashmapCreate");
		return NULL;
	}

	Node** buckets = calloc(DEFALUT_BUCKET_SIZE, sizeof(Node*));
	if (buckets == NULL) {
		perror("hashmapCreate");
		free(map);
		return NULL;
	}

	map->buckets = buckets;
	map->bucketSize = DEFALUT_BUCKET_SIZE;
	map->hash = hash;
	map->equlas = equals;

	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;
	// ��� ���� �ڵ�
	free(map->buckets);
	free(map);
}

static int hashKey(Hashmap* map, void* key) {
	int h = map->hash(key);
	h += ~(h << 9);
	h ^= (((unsigned int)h) >> 14);
	h += (h << 4);
	h ^= (((unsigned int)h) >> 10);
	return h;
}

static Node* createNode(void* key, int hash, void* value) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("createNode");
		return NULL;
	}
	node->key = key;
	node->value = value;
	node->hash = hash;
	return node;
}

static int equalsKey(void* key1, int hash1, void* key2, int hash2, EqualsFn equals) {
	if (key1 == NULL || key2 == NULL || equals == NULL)
		return 0;

	if (key1 == key2)	// �ּ� ���� ���ٸ� ���� Ű
		return 1;
	if (hash1 != hash2)	// �ּҰ� ���� ������ �ؽ� ������ ��
		return 0;
	return equals(key1, key2);
}

void* hashmapPut(Hashmap* map, void* key, void* value) {
	if (map == NULL || key == NULL || value == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);

	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL) {	// Ű�� ���� �����Ͱ� �������� �ʴ� ���
			Node* node = createNode(key, hash, value);
			if (node == NULL) {
				fprintf(stderr, "hashmapPut: createNode error\n");
				return NULL;
			}

			*ptr = node;
			map->count++;
			expandIfNessary(map);
			return NULL;
		}

		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) { // Ű�� ���� ���
			void* oldValue = cur->value;
			cur->value = value;
			return oldValue;
		}
		ptr = &(cur->next);
	}
}

void hashmapDisplay(const Hashmap* map, const char* (*toString)(void*)) {
	if (map == NULL || toString == NULL)
		return;
	system("cls");	// system("clear");

	size_t bucketSize = map->bucketSize;
	for (size_t i = 0; i < bucketSize; i++) {
		printf("bucket[%2d]", i);

		for (Node* p = map->buckets[i]; p != NULL; p = p->next)
			printf("->[%s]", toString(p->value));
		printf("\n");
	}
	getchar();
}

void* hashmapGet(const Hashmap* map, void* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "hashmapGet: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);
	Node* cur = map->buckets[index];	// Node* cur = head->next;
	while (cur != NULL) {
		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) {
			return cur->value;
		}
		cur = cur->next;
	}
	return NULL;
}

void* hashmapRemove(Hashmap* map, const void* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "hashmapRemove: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);

	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL)
			return NULL;

		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) {
			void* value = cur->value;
			*ptr = cur->next;
			free(cur);
			--map->count;
			return value;
		}
		ptr = &(cur->next);
	}
}

int hashmapForEach(const Hashmap* map, int(*callback)(void*, void*)) {
	if (map == NULL || callback == NULL) {
		fprintf(stderr, "hashmapForEach: argument is null\n");
		return -1;
	}

	for (size_t i = 0; i < map->bucketSize; i++) {
		Node* cur = map->buckets[i];
		for (; cur != NULL; cur = cur->next)
			if (callback(cur->key, cur->value) == 0)
				return 0;
	}
	return 0;
}

// �� �ڵ�� ���̺귯�� �����ڰ� �����ϴ� �ڵ��Դϴ�.
// ----------------------------------------------------------------------------------
// �Ʒ��� �ڵ�� ����ڰ� �����ϴ� �ڵ��Դϴ�.

typedef struct {
	char name[32];
	int age;
} Person;

int myHash(void* key) {
	return strlen((const char*)key);
}

int myEquals(void* key1, void* key2) {
	if (key1 == NULL || key2 == NULL)
		return 0;
	return strcmp((const char*)key1, (const char*)key2) == 0;
}

const char* myToString(void* p) {
	static char buf[1024];
	Person* person = p;
	sprintf(buf, "%s(%d)", person->name, person->age);
	return buf;
}

int increaseAge(void* key, void* value) {
	if (key == NULL || value == NULL)
		return 0;
	Person* p = value;
	++p->age;
	return 1;
}

int main() {
	Person people[4] = {
		{"daniel", 20}, {"susan", 30}, {"petty", 40}, {"eddy", 50}
	};
	Hashmap* map = hashmapCreate(myHash, myEquals);

	hashmapDisplay(map, myToString);
	for (int i = 0; i < 4; i++) {
		hashmapPut(map, people[i].name, &people[i]);
		hashmapDisplay(map, myToString);
	}

	hashmapDestroy(map);
	return 0;
}
