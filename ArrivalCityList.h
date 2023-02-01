//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Kadin Rabo
// ASU ID: 1220320764
// Description: This file defines the arrival city list. It is basically a linked list of ArrCity objects.
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//distance from a specific departure city
struct ArrCity
{
    string arrCityName;
    double distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;
        int s;
    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, double distance);
        void printArrCityList();
};

//According to above class definition, define all functions accordingly

//Constructor, initialize s too
ArrivalCityList::ArrivalCityList()
{
    this->head = 0;
    this->s = 0;
}

//Destructor no print statement
ArrivalCityList::~ArrivalCityList()
{
    ArrCity* t = this->head;
    while (t->next != 0)
    {
        ArrCity* next = t->next;
        delete t;
        t = next;
    }
}

//Return head of linked list
ArrCity *ArrivalCityList::getHead() { return this->head; }

//Find a city and return it, NULL else
ArrCity *ArrivalCityList::findArrCity(string oneCity)
{
    ArrCity* t = this->head;
    while (t != 0)
    {
        if (t->arrCityName == oneCity) return t;
        else t = t->next;
    }
    return NULL;
}

//Add a city alphabetically and return status of the insertion
bool ArrivalCityList::addArrCity(string oneCity, double distance)
{
    // Create new arrcity
    ArrCity* n = new ArrCity(); n->arrCityName = oneCity; n->distance = distance;
    
    // Insert alphabetical if head null
    if (this->head == 0 || this->head->arrCityName.compare(oneCity)>0)
        { n->next = this->head; this->head = n;this->s++; return true; }

    // Insert alphabetical
    ArrCity* t = this->head;
    while (t->next != 0 && t->next->arrCityName.compare(oneCity)<0) t = t->next;
    n->next = t->next;
    t->next = n;
    this->s++;
    
    return true;
}


//Print contents of the linked list with correct format
void ArrivalCityList::printArrCityList()
{
    // Basic traversal of linked list
    if (this->head == 0) { cout << "Arrival city list is empty";return; }
    ArrCity* t = this->head;
    while (t != 0)
    {cout << t->arrCityName << "(" << fixed << setprecision(2) << t->distance << "),";t=t->next;}
}
