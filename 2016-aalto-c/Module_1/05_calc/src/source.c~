#include <stdio.h>
#include <math.h>
#include "source.h"

void simple_sum(void)
{
	int a;
	int b;

	scanf("%d", &a);
	scanf("%d", &b);

	int sum = a + b;

	printf("%d + %d = %d\n", a, b, sum);
}

void simple_math(void)
{
	float a;
	float b;
	char op;
	float result;

	int ret_a = scanf("%f", &a);
	int ret_b = scanf(" %c", &op);
	int ret_c = scanf("%f", &b);

	if (ret_a != 1 || ret_b != 1 || ret_c != 1) {
		printf("ret_a = %d, ret_b = %d, ret_c = %d", ret_a, ret_b,
		       ret_c);
	} else {
		switch (op) {
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		default:
			printf("ERR");
			return;
		}
		printf("%.1f", result);
	}
}
