#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct Edge Edge;
typedef struct Graph Graph;
typedef struct listNode listNode;

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

struct listNode{
    int index;
    listNode* next;
    int weight;
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

int** convertToMatrix(Graph* G){
    //Allocate memory for an array of int pointers
    int** outputMatrix = (int**)malloc(G->numNodes * sizeof(int*));
    for(int i=0; i<G->numNodes; i++){
        //Allocate memory for an array of ints for each node
        outputMatrix[i] = (int*)malloc(G->numNodes * sizeof(int));
        for(int j=0; j<G->numNodes; j++){
            //Initialize each cell to 0
            outputMatrix[i][j] = 0;
        }
    }

    for(int i=0; i<G->numNodes; i++){
        for(int j=0; j<G->numNodes; j++){
            //Look for edges between i and j         
            for(int k = 0; k < G->numEdges; k++){
                if(G->edges[k].first.index == i && G->edges[k].second.index == j){
                    outputMatrix[i][j] = G->edges[k].weight;
                    break; 
                }
                else if(G->edges[k].first.index == j && G->edges[k].second.index == i){
                    outputMatrix[i][j] = G->edges[k].weight;
                    break; 
                }
            }
        }
    }
    return outputMatrix;
}

listNode** convertToList(Graph* G){
    listNode** outputLists = (listNode**)malloc(sizeof(listNode*) * G->numNodes);   //Allocate memory for the list of lists
    for(int i=0; i<G->numNodes; i++){
        outputLists[i] = NULL;
    }

    for(int i=0; i<G->numNodes; i++){
        //Initialize the head node for the current list
        listNode* head = NULL;
        listNode* currentNode = NULL;

        for(int j=0; j<G->nodes[i].numEdges; j++){
            Edge currentEdge = G->nodes[i].edges[j];

            listNode* newNode = (listNode*)malloc(sizeof(listNode));
            //Find if the connected node is the first or second node of the current edge
            if(currentEdge.first.index == i){
                newNode->index = currentEdge.second.index;
            } else {
                newNode->index = currentEdge.first.index;
            }
            newNode->weight = currentEdge.weight;
            newNode->next = NULL;

            if(head == NULL){
                head = newNode; //Set the first node as head
            }
            else{
                currentNode->next = newNode; 
            }
            currentNode = newNode;
        }
        outputLists[i] = head; //Assign the head to the output array
    }

    return outputLists;
}

/*Prim's algorithm for arrays, largely followed by geek4geeks*/

//Used to find the vertex with the minimum key value, from the set of verices not yet in the MST
int minKey(int key[], bool mstSet[], int numVertices){
    int min = INT_MAX, minIndex = -1; //Initialize minIndex to -1
    for(int v=0; v<numVertices; v++){
        if(!mstSet[v] && key[v] < min){
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMSTArray(int parent[], int numVertices, int** graphArray){
    printf("Edge \tWeight\n");
    for(int i=1; i<numVertices; i++){
        if(parent[i] != -1){
            printf("%d - %d \t%d \n", parent[i], i, graphArray[i][parent[i]]);
        }
    }
}

void primArray(int numVertices, int** graph, bool print){
    int parent[numVertices];    //Array to store constructed MST
    int key[numVertices];   //Key values used to pick minimum weight edge in cut
    bool mstSet[numVertices];   //To represent the set of vertices included in MST

    //Initialize all keys to infinite
    for(int i = 0; i < numVertices; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    //Include the first vertex in MST
    key[0] = 0;     //Make key 0 so that this vertex is picked as the first vertex
    parent[0] = -1; //First node is always root of MST

    for(int count = 0; count < numVertices - 1; count++){
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = true;

        for(int v = 0; v < numVertices; v++){
            if(graph[u][v] && graph[u][v] != INT_MAX && !mstSet[v] && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    if(print){
        printMSTArray(parent, numVertices, graph);
    }
}

/*My adaptation of Geeks4Geek's Prim's Algorithm to list based graphs instead of adjacency matrices*/
void printMSTList(int parent[], int numVertices, listNode** graph){
    printf("Edge \tWeight\n");
    for(int i=1; i<numVertices; i++){
        if(parent[i] != -1){
            //Find the weight of the associated edge
            int currWeight = -1;
            listNode* curr = graph[parent[i]];
            while(curr != NULL){
                if(curr->index == i){
                    currWeight = curr->weight;
                }
                curr = curr->next;
            }

            printf("%d - %d \t%d \n", parent[i], i, currWeight);
        }
    }
}

//Returns weight of edge if elgible to be added to MST, returns -1 upon failure
int primEdgeCheck(listNode** graph, int u, int v, int key[], bool mstSet[]){
    listNode* curr = graph[u];
    while(curr != NULL){
        if(curr->index == v && curr->weight != INT_MAX && !mstSet[v] && curr->weight < key[v]){
            return curr->weight;
        }
        curr = curr->next;
    }
    return -1;
}

void primList(int numVertices, listNode** graph, bool print){
    int parent[numVertices];    //Array to store constructed MST
    int key[numVertices];   //Key values used to pick minimum weight edge in cut
    bool mstSet[numVertices];   //To represent the set of vertices included in MST

    //Initialize all keys to infinite
    for(int i = 0; i < numVertices; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    //Include the first vertex in MST
    key[0] = 0;     //Make key 0 so that this vertex is picked as the first vertex
    parent[0] = -1; //First node is always root of MST

    for(int count = 0; count < numVertices - 1; count++){
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = true;

        for(int v = 0; v < numVertices; v++){
            //If there is an edge between u & v AND the edge's weight is not infinity AND the vertex hasnt been set 
            //AND the edge's weight is less than the smallest edge for that given key
            int weightChecked = primEdgeCheck(graph, u, v, key, mstSet);
            if(weightChecked != -1){
                parent[v] = u;
                key[v] = weightChecked;
            }
        }
    }
    if(print){
        printMSTList(parent, numVertices, graph);
    }
}

int main(){
    //Create our timing variables
    clock_t start, end;
    double fig1Times[5][2]; //Table of runtimes
    
    //Initialize all of our runtimes to -1
    for(int i=0; i<5; i++){
        for(int j=0; j<2; j++){
            fig1Times[i][j] = -1;
        }
    }

    //Generate the graph in figure 1, a-i = 0-8
    Graph* fig1 = (Graph*)malloc(sizeof(Graph));
    fig1->numNodes = 9;
    fig1->numEdges = 14;
    fig1->nodes = (Node*)malloc(sizeof(Node)*9);
    fig1->edges = (Edge*)malloc(sizeof(Edge)*14);
    for(int i=0; i<fig1->numNodes; i++){    //Initialize our nodes
        fig1->nodes[i].index = i;
    }   
    fig1->nodes[0].numEdges = 2;
    fig1->edges[0].weight = 4;
    fig1->edges[0].first = fig1->nodes[0];
    fig1->edges[0].second = fig1->nodes[1];
    fig1->nodes[0].edges = (Edge*)malloc(sizeof(Edge)*2);
    fig1->nodes[0].edges[0] = fig1->edges[0];
    fig1->edges[1].weight = 8;
    fig1->edges[1].first = fig1->nodes[0];
    fig1->edges[1].second = fig1->nodes[7];
    fig1->nodes[0].edges[1] = fig1->edges[1];
    fig1->nodes[1].numEdges = 3;
    fig1->nodes[1].edges = (Edge*)malloc(sizeof(Edge)*3);
    fig1->nodes[1].edges[0] = fig1->edges[0];
    fig1->edges[2].weight = 8;
    fig1->edges[2].first = fig1->nodes[1];
    fig1->edges[2].second = fig1->nodes[2];
    fig1->nodes[1].edges[1] = fig1->edges[2];
    fig1->edges[3].weight = 11;
    fig1->edges[3].first = fig1->nodes[1];
    fig1->edges[3].second = fig1->nodes[7];
    fig1->nodes[1].edges[2] = fig1->edges[3];
    fig1->nodes[7].numEdges = 4;
    fig1->nodes[7].edges = (Edge*)malloc(sizeof(Edge)*4);
    fig1->nodes[7].edges[0] = fig1->edges[1];
    fig1->nodes[7].edges[1] = fig1->edges[3];
    fig1->edges[4].weight = 7;
    fig1->edges[4].first = fig1->nodes[7];
    fig1->edges[4].second = fig1->nodes[8];
    fig1->nodes[7].edges[2] = fig1->edges[4];
    fig1->edges[5].weight = 1;
    fig1->edges[5].first = fig1->nodes[7];
    fig1->edges[5].second = fig1->nodes[6];
    fig1->nodes[7].edges[3] = fig1->edges[5];
    fig1->nodes[8].numEdges = 3;
    fig1->nodes[8].edges = (Edge*)malloc(sizeof(Edge)*3);
    fig1->nodes[8].edges[0] = fig1->edges[4];
    fig1->edges[6].weight = 2;
    fig1->edges[6].first = fig1->nodes[8];
    fig1->edges[6].second = fig1->nodes[2];
    fig1->nodes[8].edges[1] = fig1->edges[6];
    fig1->edges[7].weight = 6;
    fig1->edges[7].first = fig1->nodes[8];
    fig1->edges[7].second = fig1->nodes[6];
    fig1->nodes[8].edges[2] = fig1->edges[7];
    fig1->nodes[2].numEdges = 4;
    fig1->nodes[2].edges = (Edge*)malloc(sizeof(Edge)*4);
    fig1->nodes[2].edges[0] = fig1->edges[2];
    fig1->nodes[2].edges[1] = fig1->edges[6];
    fig1->edges[8].weight = 7;
    fig1->edges[8].first = fig1->nodes[2];
    fig1->edges[8].second = fig1->nodes[3];
    fig1->nodes[2].edges[2] = fig1->edges[8];
    fig1->edges[9].weight = 4;
    fig1->edges[9].first = fig1->nodes[2];
    fig1->edges[9].second = fig1->nodes[5];
    fig1->nodes[2].edges[3] = fig1->edges[9];
    fig1->nodes[6].numEdges = 3;
    fig1->nodes[6].edges = (Edge*)malloc(sizeof(Edge)*3);
    fig1->nodes[6].edges[0] = fig1->edges[5];
    fig1->nodes[6].edges[1] = fig1->edges[7];
    fig1->edges[10].weight = 2;
    fig1->edges[10].first = fig1->nodes[6];
    fig1->edges[10].second = fig1->nodes[5];
    fig1->nodes[6].edges[2] = fig1->edges[10];
    fig1->nodes[3].numEdges = 3;
    fig1->nodes[3].edges = (Edge*)malloc(sizeof(Edge)*3);
    fig1->nodes[3].edges[0] = fig1->edges[8];
    fig1->edges[11].weight = 9;
    fig1->edges[11].first = fig1->nodes[3];
    fig1->edges[11].second = fig1->nodes[4];
    fig1->nodes[3].edges[1] = fig1->edges[11];
    fig1->edges[12].weight = 14;
    fig1->edges[12].first = fig1->nodes[3];
    fig1->edges[12].second = fig1->nodes[5];
    fig1->nodes[3].edges[2] = fig1->edges[12];
    fig1->nodes[4].numEdges = 2;
    fig1->nodes[4].edges = (Edge*)malloc(sizeof(Edge)*2);
    fig1->nodes[4].edges[0] = fig1->edges[11];
    fig1->edges[13].weight = 10;
    fig1->edges[13].first = fig1->nodes[4];
    fig1->edges[13].second = fig1->nodes[5];
    fig1->nodes[4].edges[1] = fig1->edges[13];
    fig1->nodes[5].numEdges = 4;
    fig1->nodes[5].edges = (Edge*)malloc(sizeof(Edge)*4);
    fig1->nodes[5].edges[0] = fig1->edges[10];
    fig1->nodes[5].edges[1] = fig1->edges[9];
    fig1->nodes[5].edges[2] = fig1->edges[12];
    fig1->nodes[5].edges[3] = fig1->edges[13];

    //Convert fig1 into an adjacency matrix and print
    int** fig1Matrix = convertToMatrix(fig1);

    printf("\nAdjacency Matrix for fig 1:\n");
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%3d", fig1Matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    //Calculate MST for fig1 in adjacency matrix form and print
    printf("\nMST for fig1 using adjacency matrix form:\n");
    start = clock();
    primArray(fig1->numNodes, fig1Matrix, true);
    end = clock();
    fig1Times[0][0] = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    //Free allocated memory for adjacency matrix
    for(int i = 0; i < fig1->numNodes; i++) {
        free(fig1Matrix[i]);
    }
    free(fig1Matrix);

    //Convert fig1 into an adjacency list
    listNode** fig1List = convertToList(fig1);
    printf("\nAdjacency list for fig 1:\n");
    listNode* curr;
    for(int i=0; i<9; i++){
        curr = fig1List[i];
        printf("%d.  ", i);
        while(curr!=NULL){
            if(curr->next != NULL){
                printf("%d(%d) ---> ", curr->index, curr->weight);
            }
            else{
                printf("%d(%d).", curr->index, curr->weight);
            }
            curr = curr->next;
        }
        printf("\n");
    }

    //Calculate MST for fig1 in adjacency list form
    printf("\nMST for fig1 using adjacency list form:\n");
    start = clock();
    primList(fig1->numNodes, fig1List, true);
    printf("\n");
    end = clock();
    fig1Times[0][1] = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    //Print our table of times for figure 1
    printf("Runtime Table in milliseconds for figure 1:\n");
    printf("\t\tMatrix \t\tList\nFigure 1: \t%f \t%f \n", fig1Times[0][0], fig1Times[0][1]);

    //Generate all the runtimes for each n and m provided
    double times[4][6];
    int i=0;
    for(int n=100; n<1000; n=n*2){
        for(int j=0; j<3; j++){     //j determines m via switch case
            Graph* currentGraph = generateGraph(n, j);
            int** currentMatrix = convertToMatrix(currentGraph);

            start = clock();
            primArray(currentGraph->numNodes, currentMatrix, false);
            end = clock();
            times[i][j] = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

            listNode** currentList = convertToList(currentGraph);
            start = clock();
            primList(currentGraph->numNodes, currentList, false);
            end = clock();
            times[i][j+2] = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        }
        i++;
    }

    //Print our table of times for n and m specified
    printf("Runtime Table in milliseconds for specified n and m:\n");
    printf("\t\t\t\t Matrix \t\t\t\t List\n");
    printf("\t\tm=3n\tm=n^1.5\tm=n(n-1)/2\tm=3n\tm=n^1.5\tm=n(n-1)/2");
    i=0;
    for(int n=100; n<1000; n=n*2){
        printf("n=%d\t%f\t%f\t%f\t%f\t%f\t%f\n", n, times[i][0], times[i][1], times[i][2], times[i][3], times[i][4], times[i][5]);
        i++;
    }
    return 0;
}