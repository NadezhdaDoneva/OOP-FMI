// Exercise 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

const double epsilon = 0.0001;
const int MAX_SIZE = 9;



//SEMINAR
struct Rational {
    int num;
    int denom;
};

bool isValid(const Rational& ratNum) {
    return ratNum.denom != 0;
}

void printRatNumber(const Rational& ratNum) {
    cout << ratNum.num << "/" << ratNum.denom << endl;
}

unsigned findGcd(unsigned a, unsigned b) {
    if (b > a)
    {
        std::swap(a, b);
    }

    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

void reduceFraction(Rational& ratNum) {
    if (isValid(ratNum))
    {
        int gcdFraction = findGcd(ratNum.num, ratNum.denom);
        ratNum.num /= gcdFraction;
        ratNum.denom /= gcdFraction;
    }
}

//pravim q da vrushta referenciq za da moje da se wika sama w sebe si a/b += c/d += e/f
Rational& addRational(Rational& lhs, const Rational& rhs) {
    lhs.num *= rhs.denom;
    lhs.num += rhs.num * lhs.denom;
    lhs.denom *= rhs.denom;
    reduceFraction(lhs);
    return lhs;
}

Rational addTwoFractions(const Rational& lhs, const Rational& rhs) {
    //mojem da priswoqqwame taka samo ako vsichki poleta sa v statichnata pamet, ako sa dinamich ni ne stava
    Rational sumTwo = lhs; 
    addRational(sumTwo, rhs);
    return sumTwo;
}

//PRAKTIKUM

//zad1
struct Vector {
    int x;
    int y;
    int z;
};

Vector& addTwoVectors(const Vector& v1, const Vector& v2) {
    Vector sumVector;
    sumVector.x = v1.x + v2.x;
    sumVector.y = v1.y + v2.y;
    sumVector.z = v1.z + v2.z;

    return sumVector;
}

void printVector(const Vector& v) {
    cout << v.x << ', ' << v.y << ', ' << v.z;
}

void printCoordinates(const Vector& v) {
    cout << "x = " << v.x;
    cout << "y = " << v.y;
    cout << "z = " << v.z;
    cout << "\n";
}

bool areLinearDependant(const Vector& v1, const Vector& v2) {
    double division = (double)v1.x / v2.x;
    return ((abs(double(v1.y) / v2.y - division) <= epsilon) && (abs(double(v1.z) / v2.z - division) <= epsilon));
}


//zad2
enum class Degree {
    Bachelor,
    Master,
    Doctor
};

struct Teacher {
    unsigned ID;
    Degree degree;
    unsigned failedStudents;
};

void printTeacher(const Teacher& t, const char* deg) {
    cout << t.ID;
    cout << deg;
    cout << t.failedStudents;
}

void initializeTeacher(unsigned ID, const char* deg, unsigned failedStudents) {
    if (ID >= 10000 && ID <= 99999)
    {
        Teacher t;
        t.ID = ID;
        t.failedStudents = failedStudents;
        if ((strcmp(deg, "Bachelor") == 0))
        {
        t.degree = Degree::Bachelor;
        }
        else if ((strcmp(deg, "Master") == 0))
        {
        t.degree = Degree::Master;
        }
        else if ((strcmp(deg, "Doctor") == 0))
        {
        t.degree = Degree::Doctor;
        } 
        else {
            cout << "Invalid input" << "\n";
            return;
        }
        printTeacher(t, deg);
    }
    else {
        cout << "Invalid input" << "\n";
    }
}


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
    Edge* newEdgeArr = new Edge[m+1];
    for (size_t i = 0; i < m-1; i++) {
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
    Node* newNodeArr = new Node[n+1];
    for (size_t i = 0; i < n-1; i++) {
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
        m ++;
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
    //SEMINAR
    Rational f1 = { 3,4 };

    //PRAKTIKUM
    //zad1
    Vector v1 = { 1, 2, 3 };
    Vector v2 = { 4, 4, 4 };
    Vector v4 = { 2, 4, 6 };

    Vector v3 = addTwoVectors(v1, v2);
    printCoordinates(v3);

    cout << areLinearDependant(v1, v4) << "\n";

    //zad2
    /*int id;
    char degree[MAX_SIZE];
    int failedStudents;

    cin >> id;
    cin.getline(degree, MAX_SIZE);
    cin >> failedStudents;*/

    //zad4 Bonus
    //initialize graph 4.2
    unsigned n;
    cout << "Enter number of nodes: " << "\n";
    cin >> n;
    unsigned m;
    cout << "Enter number of edges: " << "\n";
    cin >> m;
    initializeGraph(n,m);
}
