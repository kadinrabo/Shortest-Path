//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Kadin Rabo
// ASU ID: 1220320764
// Description: This file defines the min priority queue functions. It is maintained as a min heap. Nodes are
// represented by City objects.
//********************************************************************

//include necessary header file here
#include "ArrivalCityList.h"

using namespace std;

//City represent a vertex of the graph which is a departure City
struct City
{
    string cityName;
    double d;
    struct City* pi; string p; string fp;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains City objects.
//The key of each City is its d value. Note: for min-heap, the underline
//data structure is a one dimensional array of City objects.
class MinPriorityQueue
{
    private:
        struct City* cityArr;	//a City array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        City* getCityArr();
        int getSize();
        int getCapacity();
        int isFound(string cityName);
        bool decreaseKey(int index, City* oneCityWithNewD);
        bool insert(City* oneCity);
        void heapify(int index);
        City* getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();

        //add any auxiliary functions here in case you need them
        void iSS(string src); void setFP(string src); MinPriorityQueue* fixFP();
        string recursive(string n, string src, string t);
};

//According to above class definition, define all functions accordingly

//Constructor to dynamically allocate memory for a min heap with the specified capacity
MinPriorityQueue::MinPriorityQueue(int capacity) {this->cityArr = new City[capacity];this->size=0;this->capacity=capacity;}

//Destructor
//Before termination, destructor is called to free the associated memory occupied by the min heap.
MinPriorityQueue::~MinPriorityQueue() {delete[] this->cityArr;}

//getCityArr
//This is the accessor for the instance variable cityArr
City *MinPriorityQueue::getCityArr() {return this->cityArr;}

//getSize
//This is the accessor for the instance variable size
int MinPriorityQueue::getSize() {return this->size;}

//getCapacity
//This is the accessor for the instance variable capacity
int MinPriorityQueue::getCapacity() {return this->capacity;}

//isFound
//Given a city name, this method returns the City object index inside the cityArr if it finds a City with the
//specific name; otherwise it returns -1
int MinPriorityQueue::isFound(string cityName) {for(int k=0;k<this->size;k++){if(this->cityArr[k].cityName==cityName)return k;}return -1;}

//decreaseKey
//Given an index and a City object called oneCityWithNewD, this function decreases the City object at index's
//d value as inside the oneCityWithNewD. The function returns true if the operation is successful and false otherwise.
bool MinPriorityQueue::decreaseKey(int index, City* oneCityWithNewD)
{
    //Update the d value
    this->cityArr[index] = *(oneCityWithNewD);

    struct City t;
    while (index != 0 && this->cityArr[this->parent(index)].d > this->cityArr[index].d)
    {
        //Swap this->cityArr[index] and this->cityArr[this->parent(k)]
        t = this->cityArr[index];
        this->cityArr[index] = this->cityArr[this->parent(index)];
        this->cityArr[this->parent(index)] = t;
        index = this->parent(index);
    }
    return true;
}

//insert
//Given the information of a City object, this function create a new City object and inserts it inside the heap. If
//successful, it should update the size and return true; otherwise, return false;
bool MinPriorityQueue::insert(City* oneCity)
{
    //Define dm and insert with new data
    struct City* dm;
    this->size++;
    dm = new City();dm->d = 30000.00;
    this->cityArr[this->size-1] = *dm;
    this->decreaseKey(this->size-1,oneCity);
    return true;
}

//heapify
//As we learned in class, before we call this heapify() function, we assume that the binary tree rooted at l and r
//child of the node at index are already min heaps, but node at index might be smaller than its children, thus violating
//the min-heap property. heapify() lets the node at index "float down" in the min-heap so that the subtree rooted at
//index obeys the min-heap property.
void MinPriorityQueue::heapify(int index)
{
    // Starter variables
    struct City t;
    int l = leftChild(index);
    int r = rightChild(index);
    int s = index;

    // Check what to swap and perform swap
    if (l < this->size && this->cityArr[index].d-this->cityArr[l].d>0) s = l;
    if (r < this->size && this->cityArr[s].d-this->cityArr[r].d>0) s = r;
    if (s != index)
    {
        //Swap this->cityArr[index] and this->cityArr[s];
        t = this->cityArr[index];
        this->cityArr[index] = this->cityArr[s];
        this->cityArr[s] = t;
        heapify(s);
    }
}

//getHeapMin
//This is the accessor for the root of the heap, it returns the s City object (also root) of the min-heap
//This function only gets the root information, it does not remove it.
City* MinPriorityQueue::getHeapMin() {return &(this->cityArr[0]);}

//extractHeapMin
//This function extracts the root of the heap. Basically we replace the root by the p node of the heap, then call
//heapify to float down the newly added root, we then decrease the size of the heap by 1.
void MinPriorityQueue::extractHeapMin()
{
    // Implement pseudocode
    this->cityArr[0] = this->cityArr[this->size-1];
    heapify(0);
    this->size--;
}

//leftChild
//Given a parent node's index, this function returns its l child's index inside the 1D array
int MinPriorityQueue::leftChild(int parentIndex) {return (2*(parentIndex)+1);}

//rightChild
//Given a parent node's index, this function returns its r child's index inside the 1D array.
int MinPriorityQueue::rightChild(int parentIndex) {return 2*(parentIndex)+2;}

//parent
//Given a node's index, this function returns its parent node's index inside the 1D array.
int MinPriorityQueue::parent(int childIndex) {return (childIndex-1)/2;}

//printHeap
//This function uses the breadth-first traversal to print out the contents of the heap. If the heap is empty, it should
//print the following message on screen:
void MinPriorityQueue::printHeap()
{
    // Print the heap before the algorithm
    for (int k=0;k<this->size;k++)
    {
        cout << left;
        cout << setw(15) << this->cityArr[k].cityName
        << setw(12) << fixed << setprecision(2) << this->cityArr[k].d
        << setw(15) << "No Parent";
        this->cityArr[k].arrCityList->printArrCityList();
        cout << endl;
    }
}

//initializeSource
//Implement pseudocode for initialize single source
void MinPriorityQueue::iSS(string src)
{
    // Implement pseudocode
    for (int k=0;k<this->size;k++)
    {
        this->cityArr[k].pi = NULL;
        this->cityArr[k].d = 30000.00;
        if (this->cityArr[k].cityName == src) { this->cityArr[k].d = 0.0; this->cityArr[k].p=src; }
    }

    // Build min heap for order fix
    for (int k=((this->size/2)-1); k>=0; k--)
        this->heapify(k);
}

//setFP
// Sets the fp value for the quickest route for printing
void MinPriorityQueue::setFP(string src)
{
    //Iterate through each city
    for (int k=0;k<this->size;k++)  // For each city
    {
        // 1 Path
        if (this->cityArr[k].cityName == src) this->cityArr[k].fp = src;
        // 2 Path
        else if (this->cityArr[k].p == src) this->cityArr[k].fp = src+"->"+this->cityArr[k].cityName;
        // >= 3 Path
        else
        {
            string t;
            string n = this->cityArr[k].p;
            t = this->recursive(n,src,t);
            t.insert(t.length(),this->cityArr[k].cityName);
            this->cityArr[k].fp = t;
        }
    }
}

//recursive
//Recurs down to the source and returns part of the shortest fp
string MinPriorityQueue::recursive(string n, string src, string t)
{
    // Base case: At source city, stop building path
    if (n == src) { t.insert(0,n+"->"); return t; }
    else { t.insert(0,n+"->"); return this->recursive(this->cityArr[this->isFound(n)].p,src,t); }
}

//fixFP
//Remedy any order issues
MinPriorityQueue* MinPriorityQueue::fixFP()
{
    int s = this->size;
    MinPriorityQueue* t = new MinPriorityQueue(s);
    for (int k=0;k<s;k++)  // Iterate through all cities
    {
        t->insert(this->getHeapMin());
        this->extractHeapMin();
    }
    return t;
}
