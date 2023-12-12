// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

#include <fstream>		// For reading file from disk
#include <iostream>
#include <sstream>
#include <string>		// For file name
#include <iomanip>	// Deinition of an Edge
#include <vector>
#include <cctype>
#include <algorithm>
#include "Graphs.h"
#include <limits>

using namespace std;

// Constructor
Graphs::Graphs()
{
    E = V = order = 0;
}

// Destructor
Graphs::~Graphs()
{
}


// Map vertex number
char Graphs::Vname(const int s) const
{
    return char(s+65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname) {
    int i = 0;                 // Index for edges array
    int rows = 0;              // Row index for the adjacency matrix
    int columns = 0;           // Column index for the adjacency matrix
    int wordcounter = 0;        // Counter for words in the file

    ifstream source1(fname);    // First pass to count the number of vertices (V)

    string line1;
    while (getline(source1, line1)) {
        if (!line1.empty() && line1.find_first_not_of(" \t") != string::npos) {
            V++;
        }
    }

    V = V - 1; // Adjust V (excluding the header "City" from the count)
    ifstream source(fname);

    if (!source.is_open()) {
        cerr << "Error opening file: " << fname << endl;
        return;
    }

    string line;
    while (getline(source, line)) {
        if (!line.empty() && line.find_first_not_of(" \t") != string::npos) {
            istringstream wordStream(line);
            string city;
            while (wordStream >> city) {
                if (city != "City" && !any_of(city.begin(), city.end(), ::isupper)) {
                    wordcounter++;
                    if (wordcounter % (V - 1) == 0) { // Check for the end of a row
                        rows++;
                        columns = 0;
                    }
                    columns++;
                    if (rows >= 1 && columns >= 1) {
                        // Fill the adjacency matrix
                        AdjMatrix[rows - 1][columns - 1] = stoi(city);

                        // Check if the edge has not been visited
                        if (stoi(city) != 0 && visitededges[stoi(city)] == false) {
                            visitededges[stoi(city)] = true;

                            // Save the edge in the edges array
                            edges[i].u = rows - 1;
                            edges[i].v = columns - 1;
                            edges[i].w = stoi(city);
                            i++;
                            E++;
                        }
                    }
                }
            }
        }
    }

    source.close();
}




// Display Adjacency Matrix
void Graphs::dispGraph() const {
    int i, j;

    // Display header
    cout << "Adjacency Matrix\n";

    // Iterate through each row of the adjacency matrix
    for (i = 0; i < V; i++) {
        // Iterate through each column of the adjacency matrix
        for (j = 0; j < V; j++)
            // Display the value at position (i, j) with setw(3) for formatting
            cout << setw(3) << AdjMatrix[i][j] << " ";

        // Move to the next line for the next row
        cout << endl;
    }
}


// Get Non-Zero edges from adjacency matrix
// and store them in array edges[].
void Graphs::getEdges() {
    int r, c;
    int i = 0;
    weightType weight;

    // Iterate through the upper triangle of the adjacency matrix
    // Only consider weights above the main diagonal to avoid duplicate edges
    for (r = 0; r <= V - 2; r++)
        for (c = r + 1; c <= V - 1; c++) {
            weight = AdjMatrix[r][c];

            // If the weight is positive (non-zero), save the edge (r, c, weight) in edges[i]
            if (weight > 0) {
                edges[i].u = r;
                edges[i].v = c;
                edges[i].w = weight;
                i++;
            }
        }

    E = i; // Number of non-zero edges
}


// Get number of vertices (V)
int Graphs::No_of_Verices() const
{
    return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const
{
    return E;
}

// Output an edge (e): Vertex names and weight
void Graphs::printEdge(Edge e) const
{
    cout << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Graphs::dispEdges() const
{
    cout<<"Graph Edges\n";
    for (int i = 0; i < E; i++)
        printEdge(edges[i]);
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
// Shortest paths from node s
// uses Dijkstra's Algorithm
void Graphs::shPath(int s) {
    // Initialize vectors to store distance, previous vertex, and processed status for each vertex
    vector<int> distance(V, numeric_limits<int>::max());
    vector<int> via(V, -1);
    vector<bool> processed(V, false);

    // Set the distance from the source vertex to itself as 0
    distance[s] = 0;

    // Helper function to find the closest unprocessed node
    auto findClosestUnprocessedNode = [&]() {
        int minDistance = numeric_limits<int>::max();
        int closestNode = -1;

        for (int i = 0; i < V; ++i) {
            if (!processed[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                closestNode = i;
            }
        }

        return closestNode;
    };

    // Main loop to process all vertices
    while (true) {
        int j = findClosestUnprocessedNode();

        if (j == -1) {
            // All vertices processed
            break;
        }

        processed[j] = true;

        // Update distance values and previous vertices for adjacent unprocessed nodes
        for (int i = 0; i < V; ++i) {
            if (!processed[i] && AdjMatrix[j][i] != 0) {
                int newDistance = distance[j] + AdjMatrix[j][i];

                if (newDistance < distance[i]) {
                    distance[i] = newDistance;
                    via[i] = j;
                }
            }
        }
    }

    // Output the results with paths
    cout << "Shortest Paths from Node " << Vname(s) << ":" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "To Node " << Vname(i) << ": ";

        if (distance[i] == numeric_limits<int>::max()) {
            cout << "No path";
        } else {
            // Display the path
            int currentNode = i;
            vector<int> path;
            while (currentNode != s) {
                path.push_back(currentNode);
                currentNode = via[currentNode];
            }
            path.push_back(s);

            // Output the path in reverse order
            for (int j = path.size() - 1; j >= 0; --j) {
                cout << Vname(path[j]);
                if (j > 0) {
                    cout << " -> ";
                }
            }
        }

        cout << " (Distance: " << distance[i] << ")" << endl;
    }
}

void Graphs::visit(int k) {
    // Mark the current node as visited and print its value
    val[k] = ++order;
    cout << k << " "; // print visited node

    // Visit adjacent nodes that are not yet visited
    for (int t = 0; t < V; ++t) {
        // Check if there is an edge (non-zero weight) between nodes k and t
        // and if node t has not been visited yet (val[t] == -1)
        if (AdjMatrix[k][t] != 0 && val[t] == -1) {
            // Recursively visit node t
            visit(t);
        }
    }
}

// Depth First Search Traversal
void Graphs::DFS() {
    // Initialize the val array to mark all vertices as unseen (-1)
    for (int k = 0; k < V; ++k) {
        val[k] = -1; // Assuming unseen is represented by -1
    }

    // Traverse the graph in depth starting from all unvisited vertices
    for (int k = 0; k < V; ++k) {
        // If the current vertex is unseen, start DFS from this vertex
        if (val[k] == -1) {
            visit(k);
        }
    }
}
