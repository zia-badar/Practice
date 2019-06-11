#include<iostream>
#include "../../algorithms/dijkstra.h"

using namespace std;

int main()
{
    dijkstra dij;
    dijkstra::node* a = new dijkstra::node();
    a->identifier = "a";
    dijkstra::node* b = new dijkstra::node();
    b->identifier = "b";
    dijkstra::node* c = new dijkstra::node();
    c->identifier = "c";
    dijkstra::node* d = new dijkstra::node();
    d->identifier = "d";
    a->adjacency_list.push_back(pair<dijkstra::node*, int>(b, 1));
    a->adjacency_list.push_back(pair<dijkstra::node*, int>(c, 2));
    b->adjacency_list.push_back(pair<dijkstra::node*, int>(d, 4));
    c->adjacency_list.push_back(pair<dijkstra::node*, int>(d, 1));
    d->adjacency_list.push_back(pair<dijkstra::node*, int>(a, 1));

    dij.solve(a);

    cout << "distance from a to b " << b->distance << endl;
    cout << "distance from a to c " << c->distance << endl;
    cout << "distance from a to d " << d->distance << endl;

    return 0;
}
