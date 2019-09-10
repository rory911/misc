#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Greatest common divisor (GCD) of two integers */
static int
gcd(int a, int b) 
{ 
	if (b == 0) 
		return a; 

	return (gcd(b, a%b)); 
} 

/* Find GCD of an array of integers using reduction */
int
find_gcd(int *a, int n)
{
	int	i;
	int	limit = a[0];	

	for (i=1; i<n; ++i)
		limit = gcd(a[i], limit);

	return (limit);
}

int
main()
{
	int a[5] = {2, 7, 5, 3, 6}, b[5] = {72, 18, 54, 9, 81};

	printf ("%d %d %d %d %d\ngcd=%d\n\n", a[0], a[1], a[2], a[3], a[4], find_gcd(a, 5));
	printf ("%d %d %d %d %d\ngcd=%d\n", b[0], b[1], b[2], b[3], b[4], find_gcd(b, 5));
}
