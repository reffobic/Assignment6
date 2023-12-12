This application processes graphs using various algorithms such as Dijkstra's Algorithm and Depth-First Search (DFS). It reads graph data from a text file and performs operations based on user commands.

## Getting Started

### Prerequisites

- C++ compiler
- Make sure to have the necessary input files (e.g., graph data file)

### Building and Running

1. Clone the repository:

   ```bash
   git clone <repository_url>
   cd <repository_directory>
Build the project:
bash
Copy code
make
Run the application:
bash
Copy code
./graph_processing_app <input_file>
Replace <input_file> with the path to your graph data file.
Usage

The application supports commands for displaying the adjacency matrix, graph edges, performing DFS traversal, and finding shortest paths from a specified node.
cpp
Copy code
// Example Usage
#include <iostream>
#include "Graphs.h"

int main() {
    Graphs x;

    // Read graph data from a file
    x.getGraph("graph_data.txt");

    // Display graph information
    x.dispGraph();
    x.dispEdges();

    // Perform DFS traversal
    std::cout << "DFS TRAVERSAL:" << std::endl;
    x.DFS();

    // Find shortest paths from Node 0 (A)
    x.shPath(0);

    return 0;
}
File Structure

Graphs.h: Header file containing the class definition.
Graphs.cpp: Implementation file for the Graphs class.
main.cpp: Main program file demonstrating the usage of the Graphs class.
