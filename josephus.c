#include <stdio.h> 
#include <stdlib.h>
  
/* There's an activation record for each one */
#define	LIMIT 100000	

/*
 * The Josephus Problem is a counting-out game and the goal is to avoid
 * selection.  Players are placed in circle and each receives a number
 * from 1 to N. Then a constant K is used as a selection key to remove
 * players from the circle. Adjust the answer by 1, since counting begins
 * with postion 1.
 */
static int
ijosephus(int N, int K)
{
	int position = 0;

	for (int i = 1; i <= N; ++i)
		position = (position + K) % i;

	return (position + 1);
}

static int
rjosephus(int N, int K) 
{ 
	return ((N == 1) ? 1 : ((rjosephus(N - 1, K) + K - 1) % N + 1));
} 
  
int
main() 
{ 
	int N = 14; 
	int K = 2; 

	printf("Enter number of players[2-%d] and a selection key[1-%d]: ", LIMIT, LIMIT - 1);
	scanf("%d %d", &N, &K);
	if (N < 2 || K < 1 || N > LIMIT || K > LIMIT - 1) {
		printf("Out of bounds\n");
		exit (1);
	}

	printf("Iteration: N=%d, K=%d, the safest position is %d\n", N, K, ijosephus(N, K)); 
	printf("Recursion: N=%d, K=%d, the safest position is %d\n", N, K, rjosephus(N, K)); 
	exit (0);
} 
