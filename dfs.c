/*  Replaced by dfs+bfs.c, but retained as legacy code.  */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node {
	int vertex;
	struct node *next;
};

struct graph {
	int numVertices;
	bool *visited;
	struct node **adjLists;
};

typedef struct node Node;
typedef struct graph Graph;

static Graph	*createGraph(int vertices);
static void	addEdge(Graph *g, int src, int dst);
static Node	*addNode(int vertex);
static void	insertList(Graph *g, Node *newp, int vertex);
static void	printGraph(Graph *g);
static void	DFS(Graph *g, int vertex);

/*
 *  Build and output a graph, then visit the nodes using Depth First Search
 */
int main(void)
{
	Graph *g = createGraph(7);

	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 0, 3);
	addEdge(g, 0, 5);
	addEdge(g, 2, 1);
	addEdge(g, 2, 4);
	addEdge(g, 5, 6);
	addEdge(g, 4, 6);

	printGraph(g);
	DFS(g, 0);

	return 0;
}

static Graph *
createGraph(int vertices)
{
	Graph *g = malloc(sizeof(Graph));
	if (g == NULL)
		exit(EXIT_FAILURE);

	g->visited = malloc(vertices * sizeof(int));
	g->adjLists = malloc(vertices * sizeof(Node));
	if (g->visited == NULL || g->adjLists == NULL)
		exit(EXIT_FAILURE);
	g->numVertices = vertices;

	for(int i = 0; i < vertices; i++) {
		g->adjLists[i] = NULL;
		g->visited[i] = false;
	}

	return (g);
}

static void
addEdge(Graph *g, int src, int dst)
{
	Node *newp;

	newp = addNode(src);
	insertList(g, newp, dst);

	newp = addNode(dst);
	insertList(g, newp, src);
}

static Node *
addNode(int vertex)
{
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		exit(EXIT_FAILURE);

	newNode->vertex = vertex;
	newNode->next = NULL;
	return (newNode);
}

static void
insertList(Graph *g, Node *newp, int vertex)
{
	Node *prev, *curr;

	/* Insert at the start of the list */
	prev = curr = g->adjLists[vertex];
	if (curr == NULL || curr->vertex >= newp->vertex) {
		g->adjLists[vertex] = newp;
		newp->next = curr;
		return;
	}

	/* Otherwise, insert in the middle or end */
	while (curr != NULL) {
		if (curr->vertex > newp->vertex)
			break;

		prev = curr;
		curr = curr->next;
	}
	prev->next = newp;
	newp->next = curr;
}

static void
printGraph(Graph *g)
{
	for(int i = 0; i < g->numVertices; i++) {
		Node *np = g->adjLists[i];

		printf("Adjacent vertices for %d: ", i);
		while(np) {
			printf("%d, ", np->vertex);
			np = np->next;
		}
		printf("\b\b  \n");
	}
}

static void
DFS(Graph *g, int vertex)
{
	g->visited[vertex] = true;
	printf("Visited %d\n", vertex);

	for (Node *np = g->adjLists[vertex]; np != NULL; np = np->next) {
		int vtx = np->vertex;

		if(g->visited[vtx] == false)
			DFS(g, vtx);
	}
}
