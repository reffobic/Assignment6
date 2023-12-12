//Done by Mohamed El Refai 900222334

#include <iostream>
#include "Graphs.h"

using namespace std;

int main() {

    Graphs x;

    x.getGraph("CitiesG.txt");

    cout << "----------------------" << endl;
    cout << "Number of Vertices: " << x.No_of_Verices() << endl ;
    cout << "Number of Edges: " << x.No_of_Edges() << endl;
    cout << "----------------------" << endl;

    x.dispGraph();
    cout << "----------------------" << endl;
    x.dispEdges();
    cout << "----------------------" << endl;

    x.shPath(0);



}