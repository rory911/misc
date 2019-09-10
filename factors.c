#include <stdio.h>

/* Print all position factors of a positive integer N */
static void 
factors(int N)
{
	for(int i = 1; i <= N; ++i) {
		if (N%i == 0) {
			printf("%d, ",i);
		}
	}
	printf("\b\b \n");
}

int
main()
{
	int num;

	printf("Enter a positive integer: ");
	scanf("%d", &num);

	printf("Factors of %d are:  ", num);
	factors(num);
}
