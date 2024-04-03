#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class Node;

class Edge{
    public:
    vector<Node*> nodes;
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
            nodes[i]->numEdges = 2;
            nodes[i]->edges.push_back(currentEdge);
            if(i < numNodes-1){
                currentEdge->nodes.push_back(nodes[i+1]);
                nodes[i+1]->edges.push_back(currentEdge);
            }
            else{   //If the last edge in making our connected graph, link to the first node
                currentEdge->nodes.push_back(nodes[0]);
                nodes[0]->edges.push_back(currentEdge);
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
            node2->numEdges++;
            node1->edges.push_back(currentEdge);
            node2->edges.push_back(currentEdge);
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
                    else if(edges[k]->nodes[0]->index == j && edges[k]->nodes[1]->index == i){
                        outputMatrix[i][j] = edges[k]->weight;
                        break;
                    }
                }
            }
        }
        return outputMatrix;
    }
};

int main(){
    //Initialize our random number generator
    srand((unsigned)time(NULL));
    

    //Create a graph representing Figure 1
    Graph* figure1 = new Graph()

    return 0;
}
