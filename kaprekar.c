#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define	KAPREKAR	6174

static int
cmpa(const void *a, const void *b)
{
	   return ( *(int*)a - *(int*)b );
}

static int
cmpd(const void *a, const void *b)
{
	   return ( *(int*)b - *(int*)a );
}

void
KaprekarsConstant(int num)
{ 
	int a, d, i, j;
	int digits[4];
	int prev, curr, iter;

	prev = 0;
	curr = num;
	for (iter = 0; prev != curr; ++iter) {
		prev = curr;

		for (i=0; i<4; ++i) { 
			digits[i] = curr%10; 
			curr = curr/10; 
		}

		// Ascending
		qsort(digits, 4, sizeof(int), cmpa);
		a = 0;
		for (i=0; i<4; ++i) 
			a = a*10 + digits[i];

		// Descending
		qsort(digits, 4, sizeof(int), cmpd);
		d = 0;
		for (i=0; i<4; ++i) 
			d = d*10 + digits[i];

		if ((curr = abs(d-a)) != prev)
			printf("|%04d - %04d| = %04d\n", d, a, curr);
	}

	if (curr == 0) {
		printf("Monodigits(%04d) do not converge\n", num);
	} else {
		assert (curr == KAPREKAR);
		printf("%d iterations to reach Kaprekar's constant\n", iter - 1);
	}
}

int
main(void)
{
	int num;
	char vstr[4];
	
	printf("Enter a four-digit integer [0000-9999]: ");
	fgets(vstr, 5, stdin);
	num = atoi(vstr);
	KaprekarsConstant(num);
	return (0);
}
