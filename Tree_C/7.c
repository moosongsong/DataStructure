
#include <stdio.h>
#include <stdlib.h>
// ������ �ڵ�� ����ϱⰡ ��ƴٴ� ������ �ֽ��ϴ�. �̸� �ذ��ϱ� ����
// ������ �߻�ȭ�մϴ�. �� �Լ��� �����մϴ�.
#define BIT_SET(set, idx)	((set) |= (1 << (idx)))
#define BIT_ISSET(set, idx) ((set) & (1 << (idx)))
#define BIT_CLR(set, idx)	((set) &= ~(1 << (idx)))

int main() {
	//unsigned int leds = 0;
	unsigned int leds[4] = 0;
	BIT_SET(leds, 0);	// leds |= (1 << 0);
	BIT_SET(leds, 31);	// leds |= (1 << 3);

	for (int i = 0; i < 32; i++) {
		if (BIT_ISSET(leds, i))	// if ((leds & (1 << i)))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	BIT_CLR(leds, 31);	// leds &= ~(1 << 3);
	for (int i = 0; i < 32; i++) {
		if (BIT_ISSET(leds, i))	// if ((leds & (1 << i)))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}