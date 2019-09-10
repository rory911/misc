#include <stdio.h>

/*
 * Find an array index where the sum of elements at lower indices
 * are equal to the sum of elements at higher indices.  The first
 * pass calculates the total.  The second pass subtracts from the 
 * total at one end of the array toward the other, and compares it
 * with the remainder (excluding itself).
 */
int
equilibrium(int a[], int n) 
{ 
	int remainder, total; 

	for (int i = 0, total = 0; i < n; ++i)
		total += a[i];

	for (int i = 0, remainder = 0; i < n; ++i) {        
		total -= a[i];

		if (total == remainder)
			return (i);

		remainder += a[i];
	}
		      
	return (-1); 
} 

int main() 
{ 
	int a[] = { -7, 1, 5, 2, -4, 3, 0 }; 
	int size = sizeof(a) / sizeof(a[0]); 
	int eq;

	printf("For array: ");
	for (int i = 0; i < size; ++i)
		printf("%d ", a[i]);

	if ((eq = equilibrium(a, size)) == -1)
		printf("\nEquilibrium does not exist\n");
	else
		printf("\nEquilibrium: index=%d value=%d\n", eq+1, a[eq]); 

	return (eq); 
}
