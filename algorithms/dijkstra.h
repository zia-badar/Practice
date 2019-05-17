#ifndef DIJKSTRA_H_
#define DIJKSTRA_H

#include <vector>
#include "../datastructures/dynamic_heap.h"

class dijkstra
{
    public:
        class node
        {
            public:
                string identifier;
                int distance;
                vector<pair<node*, int>> adjacency_list;
                bool is_explored;
                node(string id="#", int d=0, bool explore=false):identifier(id), distance(d), is_explored(explore){};
                friend bool operator<(const node& n1, const node& n2) { return n1.distance < n2.distance; }
                friend bool operator>(const node& n1, const node& n2) { return n1.distance > n2.distance; }
                node& operator-=(const node& n){ this->distance -= n.distance; return *this; }
                friend ostream& operator<<(ostream &out, node &n)
                {
                    out << n.identifier << " " << n.distance;
                    return out;
                }
        };

        // e*Log(v)
        void solve(node* src)
        {
            dynamic_heap<dijkstra::node> heap;
            src->distance = 0;
            heap.add(*src);

            node* n;
            while(!heap.is_empty())
            {
//                cout << heap;
                n = &heap.remove();
                n->is_explored = true;

                for(auto iter=n->adjacency_list.begin(); iter != n->adjacency_list.end(); iter++)
                    if(!(*iter).first->is_explored)
                    {
                        node *adj = (*iter).first;
                        int n_to_adj_distance = (*iter).second;

                        if(!heap.contains(*adj))
                        {
                            adj->distance = n->distance + n_to_adj_distance;
                            heap.add(*adj);
                        }
                        else if(adj->distance >= n->distance + n_to_adj_distance)
                            heap.decrease_entry(*adj, node("#", adj->distance - (n->distance + n_to_adj_distance)));
                    }
            }
        }
};

#endif

