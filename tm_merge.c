#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int cmpa(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/*
 * Minimum file merge of a list of files represented by the number of file records
 * in each file. Assume it takes 1 unit of time to merge every record. For example,
 * with three files with 3 records each, the first merge takes 6 units, the next
 * merge takes 9 units for a total time to merge of 15 units of time.
 */
int
minFileMerge(int *a, int n)
{
	int	i, prev, curr, total;

	if (n < 2)
		return (0);

	qsort(a, n, sizeof(int), cmpa);

	curr = total = a[0] + a[1];
	for (i=2; i<n; ++i) {
		prev = total;
		curr += a[i];
		total = prev + curr;
	}

	return (total);
}

int
main()
{
	int a[5] = {7, 2, 5, 6, 3}, b[5] = {6, 36, 21, 27, 9};

	printf ("File records: %2d %2d %2d %2d %2d   time to merge=%d\n\n",
	    a[0], a[1], a[2], a[3], a[4], minFileMerge(a, 5));

	printf ("File records: %2d %2d %2d %2d %2d   time to merge=%d\n\n",
	    b[0], b[1], b[2], b[3], b[4], minFileMerge(b, 5));
}
