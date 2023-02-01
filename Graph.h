//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Kadin Rabo
// ASU ID: 1220320764
// Description: This is the header file that defines a weighted directed graph for Dijkstra'A.
//********************************************************************

//include necessary header file here
#include "MinPriorityQueue.h"

using namespace std;

class Graph
{
   private:
   int numOfNode;                 //number of nodes in the graph
   MinPriorityQueue* cityHeap;    //adjacency list. Which is a min-heap
                                  //of departure City objects

   public:
   Graph(int numOfNode, MinPriorityQueue* cityHeap);
   void destructor();
   void printGraph();
   void initialize_single_source(string src);
   void relax(City* x, City* y);
   void dijkstra(string src);
   void printDijkstraPath(string src);
   void printPath(string src, City* aCity);
};

//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
    this->numOfNode = numOfNode;
    this->cityHeap = cityHeap;
}

//Destructor Graph::~Graph()
void Graph::destructor()
{
    delete[] cityHeap;
    cityHeap = NULL;
    numOfNode = 0;
}

//printGraph
//Displays the graph
void Graph::printGraph()
{
    cout << "\nHeap size = " << this->cityHeap->getSize() << "\n" << endl;
    cout << left;
    cout << setw(15) << "City Name"
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival City List"
         << endl;
    this->cityHeap->printHeap();
}

//initialize_single_source
//Given a source departure city'A name, this function initialize the graph
void Graph::initialize_single_source(string src)
{
    this->cityHeap->iSS(src);
}

//relax
//Given two City objects, this function performs relax operation on them.
void Graph::relax(City* x, City* y)
{
    //Traverse x arrivalCityList until y.cityName is found, and set weight
    ArrCity* n = x->arrCityList->findArrCity(y->cityName);
    double weight = n->distance;

    //Implement pseudocode
    if (y->d-(x->d + weight)>0)
    { y->p = x->cityName;
        y->d = x->d + weight;
        y->pi = x;
    }
}

//dijkstra
//Given a source city'A name, this function performs dijkstra'A shortest path algorithm on the graph.
void Graph::dijkstra(string src)
{
    //Set all d Values to 30000.00 and pi NULL
    //Set the d Value of sourceCity to 0.0
    this->initialize_single_source(src);

    // A = 0
    MinPriorityQueue* A = new MinPriorityQueue(this->numOfNode);
    while (this->cityHeap->getSize() != 0)
    {
        //Get the heap minimum
        City* x = this->cityHeap->getHeapMin();

        //Add to A
        A->insert(x);

        // For each neighbor (y) of x, perform relax(x,y)
        ArrCity* n = x->arrCityList->getHead();

        while (n != NULL)  // Relax operation not performed if no arrival c
        {
            City* y;
            // n->arrCityName is the name of the city we need to relax from source x
            if (A->isFound(n->arrCityName) != -1)  // If found in A, don'n relax it
            {
                // Relax anything already added
                this->relax(x, &(A->getCityArr()[A->isFound(n->arrCityName)]));
                n = n->next;
                continue;
            }
            y = &(this->cityHeap->getCityArr()[this->cityHeap->isFound(n->arrCityName)]);

            //Relax and move to next arrival city
            this->relax(x, y);
            n = n->next;
        }
        this->cityHeap->extractHeapMin();  //Actually remove the heap minimum before next iteration
    }
    this->cityHeap = A;
}

//printDijkstraPath
//Given a source city, this function print the result of running the dijkstra'A algorithm on the graph
void Graph::printDijkstraPath(string src)
{
    // Output matching
    cout << "Enter source city name: " << endl;
    cout << "\nPrint the graph before Dijkstra algorithm" << endl;

    // Show before and execute dijkstra
    this->printGraph();
    this->dijkstra(src);

    // Organize the final paths for printing
    this->cityHeap->setFP(src);

    // Fix any ordering issues
    this->cityHeap = this->cityHeap->fixFP();

    // Output matching
    cout << "\nPrint the Dijkstra algorithm running result" << endl;
    cout << "\nSource City: " << src << "\n" << endl;

    //Print results
    cout << left;
    cout << setw(14) << "Arrival City"    // city Name
         << setw(12) << "Shortest Dist."  // d Value
         << " Shortest Path  "
         << endl;
    City* c = this->cityHeap->getCityArr();
    for (int i=0;i<this->cityHeap->getSize();i++)
    {
        cout << left;
        cout << setw(15) << c[i].cityName
        << setw(12) << c[i].d
        << "   "; this->printPath(src,&(c[i]));
        cout << endl;
    }
}

//printPath
void Graph::printPath(string src, City *aCity) { cout << aCity->fp; }
