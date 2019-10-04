#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	N		6		// Vertices A through F
#define	INFINITY	1<<N		// Suspend the disbelief
#define	ITOV(x)		((x) + 'A')	// Integer index to UTF vertex

/*
 * Output the shortest paths for the specified 'src'
 */
void
printShortestPaths(int cost[], int path[], int src)
{
	printf("\nVertex\tCost\tPath\n");
	for (int i = 0; i < N; i++) {
		printf("(%c)\t",  ITOV(i));
		if (cost[i] == INFINITY) {
			printf("-\t-\n");
			continue;
		}
		printf("%d\t(%c)<-", cost[i], ITOV(i));
		for (int j = i; j != src; j = path[j])
			printf("(%c)<-", ITOV(path[j]));
		printf("\b\b  \n");
	}
}

/*
 * Dijkstra's shortest path algorithm using a directed graph
 */
void
dijkstra(int digraph[][N], int src)
{
	bool	visited[N] = { false };
	int	path[N], cost[N];

	/* Initialise data structs as prescribed */
	for (int i = 0; i < N; ++i) {
		cost[i] = INFINITY;
		path[i] = src;
	}

	/* Visit each vertex and generate shortest paths */
	cost[src] = 0;
	for (int i = 0; i < N; i++) {
		/* Next vertex with the lowest cost */
		int vertex;
		for (int j = 0, min = INFINITY; j < N; j++) {
			if (!visited[j] && cost[j] < min) {
				min = cost[j];
				vertex = j;
			}
		}

		/* Build the path and total cost per 'vertex' */
		visited[vertex] = true;
		for (int j = 0; j < N; j++) {
			/* Already done or unreachable */
			if (visited[j] || digraph[vertex][j] == 0)
			       continue;
			/* Looking for a lower cost */
			if (cost[vertex] + digraph[vertex][j] < cost[j]) {
				cost[j] = cost[vertex] + digraph[vertex][j];
				path[j] = vertex;
			}
		}
	}

	printShortestPaths(cost, path, src);
}

int
main()
{
	/*
 	 *	(A)--2-->(B)<--5--(C)<--+
 	 *	 |      / | \      |    |
 	 *	 |     /  |  \     |    |
 	 *	 3    2   1   3    7    6
 	 *	 |   /    |    \   |    |
 	 *	 v <-     v     -> v    |
	 *	(F)--4-->(E)      (D)   |
	 *		   \            |
	 *		    +-----------+
	 */
	int	digraph[][N] = { {0,2,0,0,0,3},
				 {0,0,0,3,1,2},
				 {0,5,0,7,0,0},
				 {0,0,0,0,0,0},
				 {0,0,6,0,0,0},
 				 {0,0,0,0,4,0} };

	for (int i = 0; i < N; ++i)
		dijkstra(digraph, i);
	printf("\n");
}
