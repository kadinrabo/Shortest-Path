//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Kadin Rabo
// ASU ID: 1220320764
// Description: This is the driver. It gets input by line, creates a min priority queue, initializes a graph, and
// runs Dijkstra's shortest path algorithm.
//********************************************************************

//include necessary header file here
#include "Graph.h"

using namespace std;

int main()
{
    //Input data
    string line,src,city,city2,cmd;
    string delim = ",";string delim2 = "(";string delim3 = ")";
    int count, pos;
    int ctr=0;
    double distance;

    //Get number of cities
    cin >> count;
    cin.ignore(20, '\n');

    //Initialize MinPriorityQueue
    MinPriorityQueue* m = new MinPriorityQueue(count);

    //Add the cities to MinPriorityQueue
    while (ctr < count)
    {
        //Create new city
        struct City x;
        ArrivalCityList* a = new ArrivalCityList();

        //Set city name
        getline(cin,line);
        pos = line.find(delim);
        src = line.substr(0, pos);
        x.cityName = src;
        line.erase(0, pos + delim.length());

        while (line.length() != 0)
        {
            //If no departing cities from the city, break
            if (line == ",") break;

            //Put one city into ArrivalCityList
            pos = line.find(delim);
            cmd = line.substr(0, pos);
            city2 = cmd;
            line.erase(0, pos + delim.length());

            //Get city of arrCity
            pos = city2.find(delim2);
            cmd = city2.substr(0, pos);
            city = cmd;
            city2.erase(0, pos + delim2.length());

            //Get distance of arrCity
            pos = city2.find(delim3);
            cmd = city2.substr(0, pos);
            distance = stod(cmd);
            city2.erase(0, pos + delim3.length());

            //Add the city
            a->addArrCity(city,distance);
        }
        //Set retrieved information and insert into MinPriorityQueue
        x.arrCityList = a;
        x.d = 30000.00;
        m->insert(&x);
        ctr++;
    }

    //Create graph
    Graph* g = new Graph(count,m);

    //Get src city
    getline(cin,line);
    pos = line.find(delim);
    src = line.substr(0, pos);
    line.erase(0, pos + delim.length());

    //Run Dijkstra
    g->printDijkstraPath(src);

    return 0;
}
