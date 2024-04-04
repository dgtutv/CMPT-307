#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
class Node;

class Edge{
    public:
    vector<Node*> nodes;    //Directed1: nodes[0] --weight--> nodes[1]
    int index;
    int weight;
    Edge(int index){
        this->index = index;
        this->weight = rand() % 50;
    }
};

class Node{
    public:
    vector<Edge*> edges;
    int numEdges;
    int index;
    Node(int index){
        this->index = index;
        this->numEdges = 0;
    }
};

class listNode{
    public:
    int index;
    listNode* next;
    int weight;
    listNode(int index, int weight){
        this->index = index;
        this->weight = weight;
    }
};

class Graph{
    public:
    int numNodes;
    int numEdges;
    vector<Node*> nodes;
    vector<Edge*> edges;
    Graph(int numNodes, int density){
        this->numNodes = numNodes;
        switch(density){
            case 0: this->numEdges = 3 * numNodes; break;
            case 1: this->numEdges = (int)floor(pow(numNodes, 1.5)); break;
            case 2: this->numEdges = (int)floor((numNodes*(numNodes-1))/2); break;
            default: this->numEdges = density;
        }
    }

    void generate(){
        //Initialize all of our nodes
        for(int i=0; i<numNodes; i++){
            Node* currentNode = new Node(i);
            nodes.push_back(currentNode);
        }

        //Make a connected base graph of nodes
        for(int i=0; i<numNodes; i++){
            Edge* currentEdge = new Edge(i);
            edges.push_back(currentEdge);
            currentEdge->nodes.push_back(nodes[i]);
            nodes[i]->numEdges = 1;
            nodes[i]->edges.push_back(currentEdge); //Only add the edge to the node in which the edge points from 
            if(i < numNodes-1){
                currentEdge->nodes.push_back(nodes[i+1]);
            }
            else{   //If the last edge in making our connected graph, link to the first node
                currentEdge->nodes.push_back(nodes[0]);
            }
        }

        //Connect the rest of the edges, with nodes randomly selected from the base graph
        for(int i=numNodes; i<numEdges; i++){
            Edge* currentEdge = new Edge(i);
            edges.push_back(currentEdge);

            //Randomly select two nodes to connect to our edge
            int node1Index = rand() % numNodes;
            int node2Index = rand() % numNodes;
            while(node2Index == node1Index){
                node2Index = rand() % numNodes;     //Ensure we don't link a node to itself
            }

            //Add our two nodes to our edge and vice versa
            Node* node1 = nodes[node1Index];
            Node* node2 = nodes[node2Index];
            currentEdge->nodes.push_back(node1);
            currentEdge->nodes.push_back(node2);
            node1->numEdges++;
            node1->edges.push_back(currentEdge);    //Only add the edge to the node in which the edge is pointing from
        }
    }

    void print(){
        cout << "numNodes: " << numNodes << endl;
        cout << "numEdges: " << numEdges << endl;

        //Print all of the nodes, with what edges are connected 
        cout << "Nodes:" << endl;
        for(Node* currentNode : nodes){
            cout << " index: " << currentNode->index << endl;
            cout << " numEdges: " << currentNode->numEdges << endl;
            cout << " Edges: " << endl;
            for(Edge* currentEdge : currentNode->edges){
                cout << "  index: " << currentEdge->index << endl;
            }
            cout << endl;
        }

        //Print all edges, with all the nodes that are connected
        cout << endl << "Edges:" << endl;
        for(Edge* currentEdge : edges){
            cout << " index: " << currentEdge->index << endl;
            cout << " weight: " << currentEdge->weight << endl;
            cout << " Nodes: " << endl;
            for(Node* currentNode : currentEdge->nodes){
                cout << "  index: " << currentNode->index << endl;
            }
            cout << endl;
        }
    }

    //From chatGPT to visualize the graph easier
    void printDotFormat(){
        cout << "digraph G {" << endl;
        for(Edge* currentEdge : edges){
            cout << "    " << currentEdge->nodes[0]->index << " -> " << currentEdge->nodes[1]->index;
            cout << " [label=" << currentEdge->weight << "];" << endl;
        }
        cout << "}" << endl;
    }   

    //Gives the adjacency matrix representation for the graph
    int** getMatrixRepresentation(){
        //Allocate memory for our matrix
        int** outputMatrix = (int**)malloc(numNodes*sizeof(int*));
        for(int i=0; i<numNodes; i++){
            outputMatrix[i] = (int*)malloc(numNodes*sizeof(int));
            //Initialize each cell to 0
            for(int j=0; j<numNodes; j++){
                outputMatrix[i][j] = 0;
            }
        }

        //Iterate over our matrix
        for(int i=0; i<numNodes; i++){
            for(int j=0; j<numNodes; j++){
                //Look for edges between i and j
                for(int k=0; k<numEdges; k++){
                    if(edges[k]->nodes[0]->index == i && edges[k]->nodes[1]->index == j){
                        outputMatrix[i][j] = edges[k]->weight;
                        break;
                    }
                }
            }
        }
        return outputMatrix;
    }

    //Gives the adjacency list representation for the graph
    listNode** getListRepresentation(){
        //Allocate memory for the adjacency lists
        listNode** adjacencyList = (listNode**)malloc(sizeof(listNode*) * numNodes);

        //Iterate over each adjacency list, adding edges from the graph as needed
        for(int i=0; i<numNodes; i++){
            listNode* head = NULL;
            listNode* priorNode = NULL;

            //Iterate over the in our node, and adding them to our list
            for(int j=0; j<nodes[i]->numEdges; j++){
                Edge* currentEdge = nodes[i]->edges[j];
                listNode* newNode = new listNode(currentEdge->nodes[0]->index, currentEdge->weight);

                if(head == NULL){
                    head = newNode;
                    priorNode = head;
                }

                else{
                    priorNode->next = newNode;
                    priorNode = newNode;
                }
                
            }

            //Assign the head of this list to the adjacencyList
            adjacencyList[i] = head;
        }
        return adjacencyList;
    }

};

//Prints a matrix in a neat, tabular format
void printMatrix(int** matrix, int length, int width){
    for(int i=0; i<length; i++){
        for(int j=0; j<width; j++){
            cout << setw(2) << matrix[i][j] << " ";     //The width of each column is 2
        }
        cout << endl;
    }
}

//Prints an adjacency list
void printList(listNode** list, int numLists){
    cout << "list#: [index:weight]-->[...]" << endl;
    for(int i=0; i<numLists; i++){
        listNode* curr = list[i];
        while(curr != NULL){
            cout << "[" << curr->index << ":" << curr->weight << "]";
            if(i < numLists-1){
                cout << "-->";
            }
            else{
                cout << endl;
            }
            curr = curr->next;
        }          
    }
}

int main(){
    //Initialize our random number generator
    srand((unsigned)time(NULL));
    

    //----------------Create a graph representing Figure 1-----------
    Graph* figure1 = new Graph(5, 10);

    //Initialize our nodes
    for(int i=0; i<figure1->numNodes; i++){ 
        Node* currentNode = new Node(i);
        figure1->nodes.push_back(currentNode);
    }

    //Initialize our edges
    for(int i=0; i<figure1->numEdges; i++){
        Edge* currentEdge = new Edge(i);
        figure1->edges.push_back(currentEdge);
    }

    //Label our nodes according to figure 1
    Node* s = figure1->nodes[0];
    Node* t = figure1->nodes[1];
    Node* x = figure1->nodes[2];
    Node* y = figure1->nodes[3];
    Node* z = figure1->nodes[4];

    //Edges for s
    s->numEdges = 2;
    figure1->edges[0]->weight = 10;
    figure1->edges[0]->nodes.push_back(s);
    figure1->edges[0]->nodes.push_back(t);
    s->edges.push_back(figure1->edges[0]);

    figure1->edges[1]->weight = 5;
    figure1->edges[1]->nodes.push_back(s);
    figure1->edges[1]->nodes.push_back(y);
    s->edges.push_back(figure1->edges[1]);

    //Edges for t
    t->numEdges = 2;
    figure1->edges[2]->weight = 2;
    figure1->edges[2]->nodes.push_back(t);
    figure1->edges[2]->nodes.push_back(y);
    t->edges.push_back(figure1->edges[2]);

    figure1->edges[3]->weight = 1;
    figure1->edges[3]->nodes.push_back(t);
    figure1->edges[3]->nodes.push_back(x);
    t->edges.push_back(figure1->edges[3]);

    //Edges for y
    y->numEdges = 3;
    figure1->edges[4]->weight = 3;
    figure1->edges[4]->nodes.push_back(y);
    figure1->edges[4]->nodes.push_back(t);
    y->edges.push_back(figure1->edges[4]);

    figure1->edges[5]->weight = 9;
    figure1->edges[5]->nodes.push_back(y);
    figure1->edges[5]->nodes.push_back(x);
    y->edges.push_back(figure1->edges[5]);

    figure1->edges[6]->weight = 2;
    figure1->edges[6]->nodes.push_back(y);
    figure1->edges[6]->nodes.push_back(z);
    y->edges.push_back(figure1->edges[6]);

    //Edges for x
    x->numEdges = 1;
    figure1->edges[7]->weight = 4;
    figure1->edges[7]->nodes.push_back(x);
    figure1->edges[7]->nodes.push_back(z);
    x->edges.push_back(figure1->edges[7]);

    //Edges for z
    z->numEdges = 2;
    figure1->edges[8]->weight = 6;
    figure1->edges[8]->nodes.push_back(z);
    figure1->edges[8]->nodes.push_back(x);
    z->edges.push_back(figure1->edges[8]);

    figure1->edges[9]->weight = 7;
    figure1->edges[9]->nodes.push_back(z);
    figure1->edges[9]->nodes.push_back(s);
    z->edges.push_back(figure1->edges[9]);

    figure1->printDotFormat();
    cout << endl;
    int** fig1Matrix = figure1->getMatrixRepresentation();
    cout << "Figure 1 Adjacency Matrix: " << endl;
    printMatrix(fig1Matrix, figure1->numNodes, figure1->numNodes);   
    listNode** fig1List = figure1->getListRepresentation();
    printList(fig1List, figure1->numEdges);
    return 0;
}
