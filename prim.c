#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node Node;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Node{
    int index;
    struct Edge** edges;
    int numEdges;
};

struct Edge{
    int weight;
    Node* first;
    Node* second;
};

struct Graph{
    int numNodes;
    int numEdges
    Edge* edges;
    Node* nodes;
};

Graph* generateGraph(int n, int graphDensity){
    int m;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->edges = (Edge*)malloc(sizeof(Edge)*m);
    graph->nodes = (Node*)malloc(sizeof(Node)*n);
    graph->numNodes = n;

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

    //Make a complete graph (link all nodes), as we initialize the nodes
    for(int i=0; i<n; i++){
        graph->nodes[i].index = i;
        graph->nodes[i].numEdges = 0;
        graph->nodes[i].edges = NULL;
        if(i>1){
            graph->edges[i-1].first = graph->nodes[i-1];
            graph->edges[i-1].second = graph->nodes[i];
            graph->edges[i-1].weight = rand() % 30;
            
            //Update the edges list and edge count for each node
            if(graph->nodes[i-1].edges){
                Edge* newEdges = (Edge*)malloc(sizeof(Edge)*(graph->nodes[i-1].numEdges + 1));
                Edge* oldEdges = graph->nodes
                for(int i=0; i)
            }
            else{

            }
            if(graph->nodes[i].edges){

            }
            else{

            }
        }        
    }

    //Add any remaining edges
    for()
}

int main(argc, argv[]){

}