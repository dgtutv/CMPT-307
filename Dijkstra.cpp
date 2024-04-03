#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class Node;

class Edge{
    vector<Node*> nodes;
};

class Node{
    vector<Edge*> edges;
    int numEdges;
    Node(int numEdges){
        this->numEdges = numEdges;
    }
};

class Graph{
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
        //Make a connected base graph of nodes
    }
};

void main(){

}
