#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	N		6			// Vertices A through F
#define	ITOV(x)		((x) + 'A')		// Integer index to UTF vertex
#define	fini_search()	printf("\b\b  \n")

/*
 *      (A)--2-->(B)<--5--(C)<--+
 *       |      / | \      |    |
 *       |     /  |  \     |    |
 *       3    2   1   3    7    6
 *       |   /    |    \   |    |
 *       v <-     v     -> v    |
 *      (F)--4-->(E)      (D)   |
 *                 \            |
 *                  +-----------+
 */
int	digraph[][N] = {{0,2,0,0,0,3},
			{0,0,0,3,1,2},
			{0,5,0,7,0,0},
			{0,0,0,0,0,0},
			{0,0,6,0,0,0},
			{0,0,0,0,4,0}};
bool	visited[N];
int	level;

static void
init_search(void)
{
	for (int i = 0; i < N; ++i)
		visited[i] = false;
	level = 0;
	printf("   ");
}

static void
visit(int vertex)
{
	if (visited[vertex] == false) {
		printf("(%c)->", ITOV(vertex));
		visited[vertex] = true;
	}
}

static void
dfs(int vertex)
{
	visit(vertex);
	for (int next_vertex = 0; next_vertex < N; ++next_vertex) {
		if (visited[next_vertex] || digraph[vertex][next_vertex] == 0)
			continue;
		dfs(next_vertex);
        }
}

static void
bfs(int vertex)
{
	if (level == N - 1)
		return;

	visit(vertex);
	for (int next_vertex = 0; next_vertex < N; ++next_vertex) {
		if (visited[next_vertex] || digraph[vertex][next_vertex] == 0)
			continue;
		visit(next_vertex);
        }

	++level;
	for (int next_vertex = 0; next_vertex < N; ++next_vertex) {
		if (next_vertex == vertex || digraph[vertex][next_vertex] == 0)
			continue;
		bfs(next_vertex);
	}
}

int
main()
{
	/* Depth first search A through F */
	printf("Depth First Search:\n");
	for (int i = 0; i < N; ++i) {
		init_search();
		dfs(i);
		fini_search();
	}

	/* Breadth first search A through F */
	printf("\nBreadth First Search:\n");
	for (int i = 0; i < N; ++i) {
		init_search();
		bfs(i);
		fini_search();
	}
	return(0);
}
