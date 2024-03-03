// Bonus 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

//zad4 Bonus
//4.1
const int MAX_NODE_SIZE = 11;
struct Node {
    char value[MAX_NODE_SIZE];
};

struct Edge {
    Node start;
    Node end;
};

//4.2
struct Graph
{
    unsigned countOfNodes;
    unsigned countOfEdges;
    Edge* edgeArr;
    Node* nodeArr;
};

void myStrCpy(char* destination, const char* source) {
    if (!destination || !source) {
        return;
    }
    while (*source) {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

bool isAddedNode(const char* node, Graph& graph, const unsigned idx) {
    for (int i = 0; i < idx; i++) {
        if (strcmp(node, graph.nodeArr[i].value) == 0) {
            return true;
        }
    }
    return false;
}

Graph initializeGraph(const unsigned n, const unsigned m) {
    Graph newGraph;
    newGraph.countOfNodes = n;
    newGraph.countOfEdges = m;
    newGraph.edgeArr = new Edge[m];
    newGraph.nodeArr = new Node[n];

    for (size_t i = 0; i < m; i++) {
        char startNode[MAX_NODE_SIZE];
        cout << "Enter start node: " << endl;
        cin.getline(startNode, MAX_NODE_SIZE, ' ');
        myStrCpy(newGraph.edgeArr[i].start.value, startNode);

        char endNode[MAX_NODE_SIZE];
        cout << "Enter end node: " << endl;
        cin.getline(endNode, MAX_NODE_SIZE, ' ');
        myStrCpy(newGraph.edgeArr[i].end.value, endNode);

        unsigned idx = 0;
        if (!isAddedNode(startNode, newGraph, idx)) {
            myStrCpy(newGraph.nodeArr[idx].value, startNode);
            idx++;
        }
        if (!isAddedNode(endNode, newGraph, idx)) {
            myStrCpy(newGraph.nodeArr[idx].value, endNode);
            idx++;
        }
    }
    return newGraph;
}


void deleteGraph(Graph& graph) {
    graph.countOfEdges = 0;
    graph.countOfNodes = 0;
    delete[] graph.edgeArr;
    delete[] graph.nodeArr;
}

//4.3
bool isAddedEdge(const Node& startNode, const Node& endNode, Edge edgeArr[], const unsigned m) {
    for (int i = 0; i < m; i++) {
        if ((strcmp(edgeArr[i].start.value, startNode.value) == 0)
            && (strcmp(edgeArr[i].end.value, endNode.value) == 0)) {
            return true;
        }
    }
    return false;
}

Graph& addEdgeIntoEdgeArr(const Node& startNode, const Node& endNode, Graph& graph, unsigned& m, unsigned& n) {
    Edge* newEdgeArr = new Edge[m + 1];
    for (size_t i = 0; i < m - 1; i++) {
        myStrCpy(newEdgeArr[i].start.value, graph.edgeArr[i].start.value);
        myStrCpy(newEdgeArr[i].end.value, graph.edgeArr[i].end.value);
    }
    myStrCpy(newEdgeArr[m].start.value, startNode.value);
    myStrCpy(newEdgeArr[m].end.value, endNode.value);
    delete[] graph.edgeArr;
    graph.edgeArr = newEdgeArr;
    return graph;
}

void addNodeIntoNodeArr(const char* node, Graph& graph, const unsigned n) {
    Node* newNodeArr = new Node[n + 1];
    for (size_t i = 0; i < n - 1; i++) {
        myStrCpy(newNodeArr[i].value, graph.nodeArr[i].value);
    }
    myStrCpy(newNodeArr[n].value, node);
    delete[] graph.nodeArr;
    graph.nodeArr = newNodeArr;
}

Graph& addEdge(const Node& startNode, const Node& endNode, Graph& graph, unsigned& m, unsigned& n) {
    if (!isAddedEdge(startNode, endNode, graph.edgeArr, m)) {
        if (!isAddedNode(startNode.value, graph, n)) {
            n++;
            addNodeIntoNodeArr(startNode.value, graph, n);
        }
        if (!isAddedNode(endNode.value, graph, n)) {
            n++;
            addNodeIntoNodeArr(endNode.value, graph, n);
        }
        graph.countOfNodes = n;
        m++;
        addEdgeIntoEdgeArr(startNode, endNode, graph, m, n);
    }
    return graph;
}


//4.4
Graph createGraph(const unsigned m) {
    Graph newGraph;
    unsigned edgeCount = 0;
    unsigned nodeCount = 0;
    for (size_t i = 0; i < m; i++) {
        Node startNode;
        cout << "Enter start node: " << endl;
        cin.getline(startNode.value, MAX_NODE_SIZE, ' ');

        Node endNode;
        cout << "Enter end node: " << endl;
        cin.getline(endNode.value, MAX_NODE_SIZE, ' ');
        addEdge(startNode, endNode, newGraph, edgeCount, nodeCount);
    }
    return newGraph;
}

//4.5
unsigned findPowerOfNode(const Node& node, const Graph& graph) {
    unsigned power = 0;
    for (size_t i = 0; i < graph.countOfEdges; i++) {
        if (strcmp(graph.edgeArr[i].start.value, node.value) == 0) {
            power++;
        }
    }
    return power;
}

//4.6
bool isGraphTotal(const Graph& graph) {
    for (size_t i = 0; i < graph.countOfNodes; i++) {
        if (findPowerOfNode(graph.nodeArr[i], graph) != (graph.countOfNodes - 1)) {
            return false;
        }
    }
    return true;
}

//4.7
void deleteEdgeFromGraph(Graph& graph, const Edge& edge, size_t i) {
    Edge* newEdgeArr = new Edge[graph.countOfEdges - 1];
    graph.countOfEdges--;
    for (size_t j = 0; j < i; j++) {
        myStrCpy(newEdgeArr[j].start.value, graph.edgeArr[j].start.value);
        myStrCpy(newEdgeArr[j].end.value, graph.edgeArr[j].end.value);
    }
    //from position i we shift the elements one position to the left
    for (size_t j = i; j < graph.countOfEdges; j++) {
        myStrCpy(newEdgeArr[j].start.value, graph.edgeArr[j + 1].start.value);
        myStrCpy(newEdgeArr[j].end.value, graph.edgeArr[j + 1].end.value);
    }
}

Graph& deleteEdge(Graph& graph, const Edge& edge) {
    if (!isAddedEdge(edge.start, edge.end, graph.edgeArr, graph.countOfEdges)) {
        cout << "The edge you are trying to delete does not exist.";
        return graph;
    }

    for (size_t i = 0; i < graph.countOfEdges; i++) {
        if ((strcmp(graph.edgeArr[i].start.value, edge.start.value) == 0) && (strcmp(graph.edgeArr[i].end.value, edge.end.value) == 0)) {
            deleteEdgeFromGraph(graph, edge, i);
            return graph;
        }
    }
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
