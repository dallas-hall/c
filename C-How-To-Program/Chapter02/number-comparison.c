#include <stdio.h>

int main(void)
{
	int number1, number2;

	printf("Enter 2 integers separated by space:\n");
	scanf("%d%d", &number1, &number2);

	if (number1 == number2) {
		printf("%d is equal to %d\n", number1, number2);
	}

	if (number1 >= number2) {
		printf("%d is greater than or equal to %d\n", number1, number2);
	}

	if (number1 > number2) {
		printf("%d is greater than %d\n", number1, number2);
	}
	
	if (number1 <= number2) {
		printf("%d is less than or equal to %d\n", number1, number2);
	}
	
	if (number1 < number2) {
		printf("%d is less than %d\n", number1, number2);
	}

	if (number1 != number2) {
		printf("%d is not equal to %d\n", number1, number2);
	}
	
	return 0;
}
