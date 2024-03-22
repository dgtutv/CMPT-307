#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Node Node;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Node{
    int index;
    Edge* edges;
    int numEdges;
};

struct Edge{
    int weight;
    Node first;
    Node second;
};

struct Graph{
    int numNodes;
    int numEdges;
    Edge* edges;
    Node* nodes;
};

Graph* generateGraph(int n, int graphDensity){
    int m;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = (Node*)malloc(sizeof(Node)*n);
    graph->numNodes = n;

    //Initialize our random number generator
    time_t t;
    srand((unsigned) time(&t));

    //Define our number of edges
    switch(graphDensity){
        case 0:
            m = 3*n;
            break;
        case 1:
            m = floor(pow(n, 1.5));
            break;
        case 2:
            m = floor((n*(n-1))/2);
    }
    graph->numEdges = m;
    graph->edges = (Edge*)malloc(sizeof(Edge)*m);

    //Initialize our nodes
    for(int i=0; i<n; i++){
        graph->nodes[i].edges = (Edge*)malloc(sizeof(Edge)*2);
        graph->nodes[i].numEdges = 0;
        graph->nodes[i].index = i;
    }

    //Make a connected graph (link all nodes in a cycle)
    int j=1;
    for(int i=0; j<n; i++){
        graph->edges[i].weight = rand()%30+1;
        graph->edges[i].first = graph->nodes[i];
        graph->edges[i].second = graph->nodes[j];
        j++;
    }
    //Link the first and last nodes
    graph->edges[n-1].weight = rand()%30+1;
    graph->edges[n-1].first = graph->nodes[n-1];
    graph->edges[n-1].second = graph->nodes[0];

    //Add any remaining edges
    for(int i=0; i<m-n; i++){
        graph->edges[n+i].weight = rand()%30+1;
        graph->edges[n+i].first = graph->nodes[rand()%n];
        graph->edges[n+i].second = graph->nodes[rand()%n];
    }

    return graph;
}

int main(){
    Graph* graph1 = generateGraph(20, 2);
    printf("n: ");
    printf("%d\n", graph1->numNodes);
    printf("m: ");
    printf("%d\n", graph1->numEdges);
    printf("Nodes: ");
    for(int i=0; i<graph1->numNodes; i++){
        printf("%d ", graph1->nodes[i].index);
    }
    printf("\nEdges: ");
    for(int i=0; i<graph1->numEdges; i++){
        printf("(%d, %d)", graph1->edges[i].first.index, graph1->edges[i].second.index);
    }
    printf("\n");
    return 0;
}