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

    //Make a connected graph (link all nodes in a cycle), as we initialize the nodes
    int i;
    for(i=0; i<n; i++){
        //Node initialization
        graph->nodes[i].index = i;
        graph->nodes[i].numEdges = 0;
        graph->nodes[i].edges = (Edge*)malloc(sizeof(Edge)*2);   //All nodes in a connected graph have 2 edges

        //Edge work
        if(i>1){
            graph->edges[i-1].first = graph->nodes[i-1];
            graph->edges[i-1].second = graph->nodes[i];
            graph->edges[i-1].weight = rand() % 30+1;
            
            //Update the edges list and edge count for each node
            graph->nodes[i-1].edges[graph->nodes[i-1].numEdges-1] = graph->edges[i-1];
            graph->nodes[i].edges[graph->nodes[i].numEdges-1] = graph->edges[i-1];
            graph->nodes[i-1].numEdges++;
            graph->nodes[i].numEdges++;
        }        
    }
    //Link the first and last edges
    graph->edges[i].first = graph->nodes[0];
    graph->edges[i].second = graph->nodes[i];
    graph->edges[i].weight = rand() % 30+1;
    graph->nodes[0].edges[1] = graph->edges[i];
    graph->nodes[i-1].edges[1] = graph->edges[i];
    graph->nodes[0].numEdges++;
    graph->nodes[i].numEdges++;

    //Add any remaining edges (later)
    return graph;
}

int main(){
    Graph* graph1 = generateGraph(10, 0);
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