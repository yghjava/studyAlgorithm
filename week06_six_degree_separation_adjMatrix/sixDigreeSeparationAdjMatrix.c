/*
 * sixDigreeSeparation.c
 *
 *  Created on: 2017年5月9日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Algorithm thought:
 * We easily know this question is BFS.
 * we  access the first level nodes, then access second level nodes
 * until we reach the sixth level.
 * We let every node to BFS until it reach the sixth level,then we record the total nodes M
 * it can reach, calculate the M/N(The total point the test data gives) .
 */

#define MAX_VERTEX_NUM 10001 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/

typedef int vertex; /*define the data type of the vertex*/
typedef int weightType; /*define the data type of the weight*/
typedef char dataType; /*define the data type of the vertex value*/

/*define the data structure of the Edge*/
typedef struct eNode *ptrToENode;
typedef struct eNode {
	vertex v1, v2; /*two vertex between the edge <v1,v2>*/
	weightType weight; /*the value of the edge's weigth */
};
typedef ptrToENode edge;

/*define the data structure of the graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode {
	int vertex_number; /*the number of the vertex*/
	int edge_nunber; /*the number of the edge*/
	weightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*define the adjacent matrix of graph*/
	dataType data[MAX_VERTEX_NUM]; /*define the dataType array to store the value of vertex*/
};
typedef ptrToGNode adjacentMatrixGraph; /*a graph show by adjacent matrix*/

/*
 create a graph given the vertex number.
 @param vertexNum The verter number of the graph
 @return a graph with vertex but no any egdgs
 */
adjacentMatrixGraph createGraph(int vertexNum) {
	vertex v, w;
	adjacentMatrixGraph graph;
	graph = (adjacentMatrixGraph) malloc(sizeof(struct gNode));
	graph->vertex_number = vertexNum;
	graph->edge_nunber = 0;
	/*initialize the adjacent matrix*/
	for (v = 1; v <= graph->vertex_number; v++) {
		for (w = 1; w <= graph->vertex_number; w++) {
			graph->g[v][w] = 0;
		}
	}

	return graph;
}

/*
 insert a edge to graph.We will distinct oriented graph and undirected graph
 @param graph The graph you want to insert edge
 @param e The edge you want to insert the graph
 @param isOriented Whether the graph is oriented graph.If the graph is oriented
 we will set adjacent matrix [n][m]=[m][n]=edge's weight,else we only set
 the adjacent matrix [n][m]=edge's weight
 */
void inserEdge(adjacentMatrixGraph graph, edge e, int isOriented) {
	graph->g[e->v1][e->v2] = e->weight;
	if (!isOriented) {
		graph->g[e->v2][e->v1] = e->weight;
	}
}

/*
 construct a graph according user's input

 @return a graph has been filled good
 */
adjacentMatrixGraph buildGraph() {
	adjacentMatrixGraph graph;
	edge e;
	int vertex_num, i;
	scanf("%d", &vertex_num);
	graph = createGraph(vertex_num);
	scanf("%d", &(graph->edge_nunber));
	if (graph->edge_nunber) {
		e = (edge) malloc(sizeof(struct eNode));
		for (i = 0; i < graph->edge_nunber; i++) {
			scanf("%d %d", &e->v1, &e->v2);
			e->weight = 1;
			inserEdge(graph, e, 0);
		}
	}

	return graph;

}

/*=====================define a queue used BFS================================*/
/*
 * The elementType is element which the following list store.
 */
typedef int elementType;

/*
 * Define a list to store the queue elements
 */
typedef struct node1 *pList;
typedef struct node1 {
	elementType element;
	struct node1 *next;
};

/*
 * Define a queue used to BFS
 */
typedef struct node2 *pQueue;
typedef struct node2 {
	pList font;
	pList rear;
};

/*
 * Create a empty list
 */
pList createEmptyList() {
	pList list = (pList) malloc(sizeof(struct node1));
	list->next = NULL;
	return list;
}

/*
 * Create a empty queue
 */
pQueue createEmptyQueue() {
	pQueue queue = (pQueue) malloc(sizeof(struct node2));
	queue->font = queue->rear = NULL;
	return queue;
}

/*
 * Whether the queue is empty
 */
int isQueueEmpty(pQueue queue) {
	return (queue->font == NULL);
}

/*
 * Insert a element to a queue
 */
void insertQueue(pQueue queue, elementType element) {

	if (isQueueEmpty(queue)) {
		pList list = createEmptyList();
		list->element = element;
		queue->font = queue->rear = list;
	} else {
		pList newNode = (pList) malloc(sizeof(struct node1));
		newNode->element = element;
		//newNode->next = queue->rear->next;
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

elementType deleteElementQueue(pQueue queue) {
	if (isQueueEmpty(queue)) {
		return -1;
	} else {
		if (queue->font == queue->rear) {
			pList temp = queue->font;
			elementType elememt = temp->element;
			free(temp);
			queue->font = queue->rear = NULL;
			return elememt;
		} else {
			pList temp = queue->font;
			elementType elememt = temp->element;
			free(temp);
			queue->font = queue->font->next;
			return elememt;
		}

	}

}

/*
 *Breath first search a graph which store in form of adjacent matrix
 *@param graph The graph stored with adjacent matrix
 *@param startPoint The start point we start search
 *@param visited A array to tag whether element has been accessed
 */
int BFS(adjacentMatrixGraph graph, vertex startPoint, int *visited) {
	vertex v, w;
	/*
	 * count:to record the total nodes the start point can access
	 * level:to record the level the current node accessed
	 * tail:to record the every node's index, every access it will be flush
	 * last:to record last lever latest accessed node,we can use it to
	 * 		let level add.
	 */
	int count = 0;
	int level = 0, last = startPoint;
	int tail = last;
	pQueue queue = createEmptyQueue();
	count++;
	visited[startPoint] = 1;
	insertQueue(queue, startPoint);
	while (!isQueueEmpty(queue)) {
		w = deleteElementQueue(queue);
		for (v = 1; v <= graph->vertex_number; v++) {
			if (graph->g[w][v] != 0 && visited[v] == 0) {
				visited[v] = 1;
				insertQueue(queue, v);
				tail = v;
				count++;
			}
		}
		if (w == last) {
			level++;
			last = tail;
		}

		if (level == 6) {
			return count;
		}
	}
	return count;

}

/*
 * Initialize a visited array that make them all to zero
 */
void initVisited(adjacentMatrixGraph graph, int *visited) {
	int i;
	for (i = 1; i <= graph->vertex_number; i++) {
		visited[i] = 0;
	}
}

/*
 *Prove the six degree of separation
 *@param graph A graph prepared
 */
void SDS(adjacentMatrixGraph graph) {
	int visited[graph->vertex_number + 1];
	vertex v;
	int count;
	float result;
	for (v = 1; v <= graph->vertex_number; v++) {
		initVisited(graph, visited);
		count = BFS(graph, v, visited);
		result = (float) ((float) count / graph->vertex_number * 100);
		printf("%d: %0.2f", v, result);
		printf("%%");
		printf("\n");
	}
}

int main() {
	adjacentMatrixGraph graph = buildGraph();
	SDS(graph);
	return 0;
}

