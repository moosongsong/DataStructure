
#include <stdio.h>
#include <stdlib.h>
#define BIT_SET(set, idx)	((set)[(idx)/32] |= (1 << ((idx)%32)))
#define BIT_ISSET(set, idx) ((set)[(idx)/32] & (1 << ((idx)%32)))
#define BIT_CLR(set, idx)	((set)[(idx)/32] &= ~(1 << ((idx)%32)))
#define BIT_ZERO(set)	\
	do { for (int i = 0; i <4; i++) (set)[i] = 0; } while(0)

// ���� �ڷᱸ���� Ÿ���� �߻�ȭ�Ǿ� ���� �ʴٴ� ������ �ֽ��ϴ�. �̸� �ذ��ϱ� ����
// Ÿ���� �߻�ȭ�մϴ�.
typedef unsigned int bitset[4];

// ���� �ʱ�ȭ�� ���� ��ũ�� �ɺ��� �����մϴ�.
#define BITSET_INITIALIZER	{0,}

int main() {
	//bitset leds = { 0, };	// unsigned int leds[4] = { 0, };
	bitset leds = BITSET_INITIALIZER; //bitset leds = 0;
	BIT_SET(leds, 100);

	for (int i = 0; i < 128; i++) {
		if (BIT_ISSET(leds, i))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	BIT_CLR(leds, 100);
	for (int i = 0; i < 128; i++) {
		if (BIT_ISSET(leds, i))	
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}

	//leds = BITSET_INITIALIZER;
	BIT_ZERO(leds);
}