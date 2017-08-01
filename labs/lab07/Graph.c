// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013
//group partners are Hai Long Bi and Jingcheng Li
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w, int weight)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w,weight}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	Graph g = malloc(sizeof(struct GraphRep));
	g->nV = nV;
	g->edges = calloc(nV, sizeof(int*));
	int i = 0;
	for(i = 0; i < nV; i++) {
		g->edges[i] = calloc(nV, sizeof(int));
	}
	g->nE = 0;
	return g;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	int i = 0;
	for(i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	assert(g != NULL);
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL && validV(g,src) && validV(g,dest));
    // q = to visit
	Queue q = newQueue();
	Vertex *visited = calloc(g->nV,sizeof(int));
	QueueJoin(q, src);
    Vertex *_path = malloc(g->nV * sizeof(Vertex));
    int isFound = 0;
    while (!QueueIsEmpty(q) && !isFound) {
        Vertex y, x = QueueLeave(q);
        if(x == dest) {
            isFound = 1;
            break;
        }
        for (y = 0; y < g->nV; y++) {
            if (!(g->edges[x][y] > 0 && g->edges[x][y] <= max)) {
                continue;
            }
            if (!visited[y]) {
                _path[y] = x; QueueJoin(q,y); visited[y] = 1;
            }
        }
    }
    Vertex *reverse_path = malloc(g->nV * sizeof(Vertex));
    int points = 0;
    if (isFound) {
        Vertex v;
        for (v = dest; v != src; v = _path[v]) {
            reverse_path[points] = v;
            points++;
        }
        reverse_path[points] = src;
        points++;

    }

    int j = 0;
    for(j = 0; j < points; j++) {
        path[points-(j+1)] = reverse_path[j];
    }
    free(visited);
    free(_path);
    free(reverse_path);
	dropQueue(q);
	if(points == 0) {
        return -1; // aka failed
	}
	return points;
}

// checks if the vertex is within the visited vertex array
/*int isVisited(Vertex *visited, Vertex v, int visited_length) {
	int i = 0;
	for(i = 0; i < visited_length; i++) {
		if(visited[i] == 1 && v == i) {
			return 1;
		}
	}
	return 0;
}

// puts all of the available neighbours which are
// > not visited
// > within range criteria
// > not 0 (null path)
int findNeighbours(Graph g, Vertex v, int max, Queue toJoin, Vertex *visited, Vertex *previous) {
	int i = 0;
	int foundNeighbour = 0;
	for(i = 0; i < g->nV; i++) {
		if(g->edges[v][i] > 0 && g->edges[v][i] <= max && isVisited(visited, v, g->nV) == 0) {
			QueueJoin(toJoin, i);
			foundNeighbour = 1;
			visited[i] = 1; // true
			previous[i] = v; // the previous is the node in which neighbours are being projected from
		}
	}

	if(foundNeighbour == 1) {
		return 1;
	} else {
		return 0;
	}
}*/


