
// 8���� LED(0~7)�� ���Ͽ� ���� ������ �����ϴ� �ڵ带 ������ ���ô�.
#include <stdio.h>
#include <stdlib.h>
enum { LED_OFF, LED_ON };

int main() {
	// �Ʒ��� �ڵ尡 ���۵ǵ��� �ڵ带 ������ ������ :D
	// char leds = 0;	// 0000 0000
	unsigned int leds = 0;

	// 0000 0001
	// 0000 1000
	// --------- | -> �� ������
	// 0000 1001

	// leds = leds | (1 << 0); // 0�� LED�� ���� ���
	leds |= (1 << 0);
	leds |= (1 << 3);

	// 0000 1001 leds
	// 0000 1000 
	// --------- & -> �� ������
	// 0000 1000
	for (int i = 0; i < 32; i++) {
		if ((leds & (1 << i)))	// if (leds[i] == LED_ON))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	// 0000 1001 leds
	// 1111 0111
	// --------- &
	// 0000 0001

	// leds = leds & ~(1 << 3);	// leds[3] = LED_OFF;
	leds &= ~(1 << 3);
	for (int i = 0; i < 32; i++) {
		if ((leds & (1 << i)))	// if (leds[i] == LED_ON))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}