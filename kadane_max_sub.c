#include <stdio.h>

void
printMaxSubArray(int a[], int size) 
{ 
	int i, max_sum = 0, max_curr = 0, next = 0, start =0, stop = 0; 

	for (i = 0; i < size; ++i) { 
		max_curr += a[i]; 
		if (max_sum < max_curr) {
			max_sum = max_curr; 
			start = next; 
			stop = i;
	       	} 
		if (max_curr < 0) {
			max_curr = 0; 
			next = i + 1; 
		} 
	} 

	printf("\nMaximum subarray: ");
	for (i = start; i <= stop; ++i)
		printf("%d ", a[i]);
	printf("\nMaximum continuous sum: %d\n", max_sum);
} 

int
main()
{
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
	int size = sizeof(a)/sizeof(int);

	printf("Full array: ");
	for (int i = 0; i < size; ++i)
		printf("%d ", a[i]);

	printMaxSubArray(a, size);
	return (0);
}
