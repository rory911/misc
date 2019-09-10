#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define VERBOSE	1
#define DEBUG	0

typedef int vidx_t;

typedef struct Edge {
	vidx_t src;
	vidx_t dst;
	int weight;
	bool selected;
} Edge_t;

typedef struct Vertex {
	vidx_t id;
	bool visited;
	Edge_t *e;
	vidx_t *linked;
} Vertex_t;

typedef struct Graph { 
	int numVertex;
	int numEdge;
	Vertex_t *v;
} Graph_t;


/* Useful for debugging the graph */
void
printDBG(Graph_t *g)
{
	Edge_t	*e;
	vidx_t	*l;

	for (int i = 0; i < g->numVertex; ++i) {
		printf("vertex: id=%d\nvisited=%s\n  edge: ", g->v[i].id,
		    (g->v[i].visited) ? "true" : "false");
		e = g->v[i].e;
		for (int j=0; j < g->numEdge; ++j) {
			if (e[j].weight == -1)
				continue;
			printf("%d->%d(%d)", e[j].src, e[j].dst, e[j].weight);
			printf("%s ", (e[j].selected) ? "selected" : "");
		}
		printf("\n  linked: ");
		l = g->v[i].linked;
		for (int k=0; k<g->numVertex; ++k) {
			if (l[k] == -1)
				continue;
			printf("%d, ", l[k]);
		}
		printf("\b\b  \n");
	}
}

/* Create a graph */
Graph_t *
newGraph(int V, int E) 
{ 
	int	i, j, sizeMst;
	Graph_t	*g;
	Edge_t	*ep;
	vidx_t	*lp;

	g = calloc(1, sizeof(Graph_t));
	g->numVertex = V; 
	g->numEdge = E; 
	g->v = calloc(V, sizeof(Vertex_t));
	for (i = 0; i < V; ++i) {
		g->v[i].id = i;
		g->v[i].visited = false;
		ep = g->v[i].e = calloc(E, sizeof(Edge_t));
		for (j = 0; j < E; ++j) {
			ep[j].src = -1;
			ep[j].dst = -1;
			ep[j].weight = -1;
			ep[j].selected = false;
		}
		lp = g->v[i].linked = calloc(V, sizeof(vidx_t));
		for (j = 0; j < V; ++j) {
			lp[j] = -1;
		}
	}

	return (g); 
}

/* Destroy a graph */
void
freeGraph(Graph_t *g)
{
	if (g == NULL)
		return;

	if (g->v && g->v->e)
		free(g->v->e);
	if (g->v && g->v->linked)
		free(g->v->linked);
	if (g->v)
		free(g->v);

	free(g);
}

/* Add an edge between vertices in a graph */
void
addEdge(Graph_t *g, int src, int dst, int weight)
{
	int	i;
	Edge_t	*ep;
	vidx_t	*lp;

	/* Update src edges and vertex connections */
	ep = g->v[src].e;
	for (i = 0; i < g->numEdge; ++i) {
		if (ep[i].src == -1) {
			ep[i].src = src;
			ep[i].dst = dst;
			ep[i].weight = weight;
			break;
		}
	}
	lp = g->v[src].linked;
	for (i = 0; i < g->numVertex; ++i) {
		if (lp[i] == dst)
			break;
		if (lp[i] == -1) {
			lp[i] = dst;
			break;
		}
	}

	/* Update dst edges and vertex connections */
	ep = g->v[dst].e;
	for (i = 0; i < g->numEdge; ++i) {
		if (ep[i].src == -1) {
			ep[i].src = src;
			ep[i].dst = dst;
			ep[i].weight = weight;
			break;
		}
	}
	lp = g->v[dst].linked;
	for (i = 0; i < g->numVertex; ++i) {
		if (lp[i] == dst)
			break;;
		if (lp[i] == -1) {
			lp[i] = src;
			break;
		}
	}
}

/* Mark it on both the src and the dst */
void
edgeSelected(Graph_t *g, Edge_t *e)
{
	int	i, j;

	for (int i = 0; i < g->numVertex; ++i) {
		for (int j = 0; j < g->numEdge; ++j) {
			if (g->v[i].e[j].src == e->src &&
			    g->v[i].e[j].dst == e->dst) {
				g->v[i].e[j].selected = true;
			}
		}
	}
}

/* Next minimum edge of the graph that is active and unselected */
Edge_t *
minEdge(Graph_t *g)
{
	int	i, j, k;
	Edge_t	*edge, *min = NULL;

	for (i = 0; i < g->numVertex; ++i) {
		/* For each vertex, find an active edge */
		edge = g->v[i].e;
		for (j = 0; j < g->numEdge; ++j) {
			if (edge[j].weight == -1)
				continue;
			if (edge[j].selected) {
				continue;
			}
			/* Ignore duplicates */
			if (min && min->src == edge[j].src &&
			    min->dst == edge[j].dst) {
				continue;
			}
			break;
		}
		if (j == g->numEdge)
			continue;

		/* Initial candidate */
		if (min == NULL)
			min = &edge[j];

		/* Compare with other edges of the vertex */
		for (k = j; k < g->numEdge; ++k) {
			if (edge[k].weight == -1)
				continue;
			if (edge[k].selected)
				continue;
			if (edge[k].weight < min->weight) 
				 min = &edge[k];
		}
	}

	if (min == NULL)
		return (NULL);

	edgeSelected(g, min);
	return (min);
}

/* Output the Minimum Spanning Tree (MST) */
void
printMst(Graph_t *m)
{
	int	i, idx;
	Edge_t	*min; 

	printf("\nMinimum Spanning Tree:\n\n");
	for (i = 0, idx = 0; i < m->numEdge; ++i) {
		if ((min = minEdge(m)) == NULL)
			break;
		printf("   (%d)->(%d)  %d\n", min->src, min->dst, min->weight);
		if (++idx == m->numVertex)
			break;
	}
	printf("\n");
}

/* Recursively descend looking for graph cycles */
bool
dfsSearch(Graph_t *m, Vertex_t *v, Edge_t *e, int dup)
{
	int i, vid;


	/* Available or already examined */
	if (v->e->weight == -1 || v->visited)
		return (false);

	for (i = 0; v->linked[i] > -1; ++i) {
		vid = v->linked[i];
		if (vid == -1)
			return (false);
		if (vid == dup) {
		    if (VERBOSE) {
			printf("cycle: v->id=%d link[%d]=%d dup=%d e->src=%d "
			    "e->dst=%d e->weight=%d\n", v->id, i, vid, dup,
			    e->src, e->dst, e->weight);
		    }
		    return (true);
		}

		v->visited = true;			// avoid infite loops

		if (dfsSearch(m, &m->v[vid], e, dup))	// descend
			return (true);
	}

	return (false);
}

/* Can the next minimum edge be added to the MST */
bool
findCycle(Graph_t *m, Edge_t *next)
{
	int	i;

	/* Initialize the graph for searching */
	for (i = 0; i < m->numVertex; ++i)
		m->v->visited = false;

	/* An edge has two vertices */
	if (dfsSearch(m, &m->v[next->src], next, next->dst))
		return (true);
	if (dfsSearch(m, &m->v[next->dst], next, next->src))
		return (true);

	return (false);
}

/* Contrust the MST one edge at a time unless a cycle is found */
bool
updateMst(Graph_t *m, Edge_t *e)
{
	if (findCycle(m, e))
		return (false);

	addEdge(m, e->src, e->dst, e->weight);
	return (true);
}

/*
 * Gerenate and output an MST using edges of increasing weight
 */
void
Kruskal(Graph_t *g)
{
	int	i, idx, sizeMst;
	Edge_t	*next; 
	Graph_t	*mst;
       
	sizeMst = g->numVertex - 1;
	mst = newGraph(g->numVertex, sizeMst);

	for (i = 0, idx = 0; i < g->numEdge; ++i) {
		/* For 7 edges, just seach instead of sort */
		if ((next = minEdge(g)) == NULL)
			break;
		/* Build the MST if there are no cycles */
		if (updateMst(mst, next) == false)
			continue;
		if (++idx == sizeMst)
			break;
	}

	printMst(mst);
	freeGraph(mst);
}

/*
 * Intentionally excessive graph manipulation using Kruskal's
 * weight edge to solve the minimum spanning tree problem.
 */
int main() 
{ 
	Graph_t	*g;

	/*
	 *  Construct a graph of weighted edges:
	 *
	 *                (0)
	 *                / \
	 *               2   1
	 *              /     \
	 *           (1)-- 3 --(3)
	 *            |  \      |
	 *            4    5    8
	 *            |      \  |
	 *           (2)-- 7 --(4)
	 *
	 *  1->3 will create a cycle in order to
	 *  test the cycle detection code.
	 */
	g = newGraph(5, 7);	// 5 Vertices, 7 edges
	addEdge(g, 0, 1, 2);	// 0->1: weight=2
	addEdge(g, 0, 3, 1);	// 0->3: weight=1
	addEdge(g, 1, 2, 4);	// 1->2: weight=4
	addEdge(g, 1, 3, 3);	// 1->3: weight=3
	addEdge(g, 1, 4, 5);	// 1->4: weight=5
	addEdge(g, 2, 4, 7);	// 2->4: weight=7
	addEdge(g, 3, 4, 8);	// 3->4: weight=8
	
	if (DEBUG)
		printDBG(g);

	printf("\nFor the weighted graph:\n\n");
	printf("        (0)\n");
	printf("        / \\\n");
	printf("       2   1\n");
	printf("      /     \\\n");
	printf("   (1)-- 3*--(3)\n");
	printf("    |  \\      |\n");
	printf("    4    5    8\n");
	printf("    |      \\  |\n");
	printf("   (2)-- 7 --(4)\n");

	if (VERBOSE)
		printf("\n(1)->(3) will create a cycle\n");

	Kruskal(g);
	freeGraph(g);
	return (0);
}
