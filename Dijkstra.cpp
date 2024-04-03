#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class Node;

class Edge{
    public:
    vector<Node*> nodes;
    int index;
    int numNodes;
    Edge(int index){
        this->index = index;
        this->numNodes = 0;
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
            default: this->numEdges = 3 * numNodes;
        }
    }

    void generate(){
        //Initialize all of our nodes
        for(int i=0; i<numNodes; i++){
            Node* currentNode = new Node(i);
            nodes.push_back(currentNode);
        }

        //Make a connected base graph of nodes
        for(int i=0; i<numEdges; i++){
            Edge* currentEdge = new Edge(i);
            edges.push_back(currentEdge);
            currentEdge->numNodes = 2;
            currentEdge->nodes.push_back(nodes[i]);
            nodes[i]->numEdges = 2;
            nodes[i]->edges.push_back(currentEdge);
            if(i < numEdges-1){
                currentEdge->nodes.push_back(nodes[i+1]);
                nodes[i+1]->edges.push_back(currentEdge);
            }
            else{   //If the last edge in making our connected graph, link to the first node
                currentEdge->nodes.push_back(nodes[0]);
                nodes[0]->edges.push_back(currentEdge);
                edges[0]->nodes.push_back(nodes[i]);
            }
            
        }
    }

    void print(){
        cout << "numNodes: " << numNodes << endl;
        cout << "numEdges: " << numEdges << endl;

        //Print all of the nodes, with what edges are connected 
        cout << "Nodes:" << endl;
        for(Node* currentNode : nodes){
            cout << "\tindex: " << currentNode->index << endl;
            cout << "\tnumEdges: " << currentNode->numEdges << endl;
            cout << "\tEdges: " << endl;
            for(Edge* currentEdge : currentNode->edges){
                cout << "\t\tindex: " << currentEdge->index << endl;
            }
        }

        //Print all edges, with all the nodes that are connected

    }
};

void main(){
    //Testing Graph.generate for the base graph
}
