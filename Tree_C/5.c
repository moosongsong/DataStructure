
// 8���� LED(0~7)�� ���Ͽ� ���� ������ �����ϴ� �ڵ带 ������ ���ô�.
#include <stdio.h>
#include <stdlib.h>
enum { LED_OFF, LED_ON };

int main() {
	//int leds[8] = { 0, };	// ��� ���� ����
	//char leds[8] = { 0, };	// ��� ���� ����
	char leds = 0;	// ��� ���� ����

	// 0�� LED�� ���� ���
	leds[0] = LED_ON;

	// 3�� LED�� ���� ���
	leds[3] = LED_ON;

	// LED �˻�
	for (int i = 0; i < 8; i++) {
		if (leds[i] == LED_ON)
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	// 3�� LED�� ���� ���
	leds[3] = LED_OFF;

	// LED �˻�
	for (int i = 0; i < 8; i++) {
		if (leds[i] == LED_ON)
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}