#include "../../algorithms/kruskal.h"

int main()
{
    kruskal kru;
    kruskal::node n1, n2, n3;
    n1.adjacency_list.push_back(pair<kruskal::node*, int>(&n2, 2));
    n2.adjacency_list.push_back(pair<kruskal::node*, int>(&n1, 2));

    n2.adjacency_list.push_back(pair<kruskal::node*, int>(&n3, 3));
    n3.adjacency_list.push_back(pair<kruskal::node*, int>(&n2, 3));

    n3.adjacency_list.push_back(pair<kruskal::node*, int>(&n1, 4));
    n1.adjacency_list.push_back(pair<kruskal::node*, int>(&n3, 4));
    kruskal::node* mst = kru.construct_mst(&n1);

    return 0;
}