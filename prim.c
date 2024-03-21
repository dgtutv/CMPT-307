#include <stdio.h>
#include <stdlib.h>

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

Node* generateGraph(int n){
    
}

int main(argc, argv[]){

}