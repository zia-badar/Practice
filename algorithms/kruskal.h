#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../algorithms/union_find.h"

using namespace std;

class kruskal
{

    public:
        // graph is represent by a single node as other nodes can be reached through exploration from this node
        class node
        {
            public:
                vector<pair<node*, int>> adjacency_list;    // undirected edge is represented by two directed edges
        };

        node* construct_mst(node* n)
        {
            vector<edge> edges;
            compute_edges(n, edges, NULL);
            sort(edges.begin(), edges.end());
            vector<node*> vertices = compute_vertices(n, NULL);
            unordered_map<node*, int> vertex_index;
            for(int i=0; i<vertices.size(); i++) vertex_index.insert({vertices[i], i});
            union_find uf(vertices.size());

            vector<edge> mst_edges;
            for(auto e: edges)
            {
                int n1_index = vertex_index.find(e.n1)->second;
                int n2_index = vertex_index.find(e.n2)->second;
                if(!uf.are_connected(n1_index, n2_index))
                {
                    uf.connect(n1_index, n2_index);
                    mst_edges.push_back(e);
                }
            }

            return graph_from_edges(mst_edges);
        }

    private:
        class edge  // undirected edge between two nodes
        {
            public:
                node* n1;
                node* n2;
                int cost;
                edge(): n1(NULL), n2(NULL), cost(-1) {}
                edge(node* n1_, node* n2_, int c): n1(n1_), n2(n2_), cost(c) {}
                friend bool operator<(const edge& e1, const edge& e2){ return e1.cost < e2.cost; }
        };

        // returns all edges from graph represented by node* n
        void compute_edges(node* n, vector<edge>& edges, unordered_set<node*>* explored)
        {
            bool first_call = explored == NULL;
            if(first_call) explored = new unordered_set<node*>();

            for(pair<node*, int> adjacent : n->adjacency_list)
                if(explored->find(adjacent.first) == explored->end())           // avoiding duplicate undirected edges
                    edges.push_back(edge(n, adjacent.first, adjacent.second));  // because undirected edges are
                                                                                // represented by two directed edges.
            explored->insert(n);

            for(pair<node*, int> adjacent : n->adjacency_list)
                if(explored->find(adjacent.first) == explored->end())      // exploring only unexplored nodes
                    compute_edges(adjacent.first, edges, explored);

            if(first_call) delete explored;
        }

        // returns all nodes from graph represented by node* n
        vector<node*> compute_vertices(node* n, unordered_set<node*>* explored)
        {
            bool first_call = explored == NULL;
            if(first_call) explored = new unordered_set<node*>();

            explored->insert(n);
            for(pair<node*, int> adjacent : n->adjacency_list)
                if(explored->find(adjacent.first) == explored->end())      // exploring only unexplored nodes
                    compute_vertices(adjacent.first, explored);

            if(first_call)
            {
                vector<node*> vertices;
                for(auto n : *explored) vertices.push_back(n);
                delete explored;
                return vertices;
            }

            return vector<node*>();
        }

        // creates a new graph from given edges
        node* graph_from_edges(vector<edge> edges)
        {
            unordered_map<node*, node*> old_to_new_node_map;
            for(edge e : edges)
            {
                if(old_to_new_node_map.find(e.n1) == old_to_new_node_map.end())
                    old_to_new_node_map[e.n1] = new node();
                if(old_to_new_node_map.find(e.n2) == old_to_new_node_map.end())
                    old_to_new_node_map[e.n2] = new node();

                node* new_n1 = old_to_new_node_map[e.n1];
                node* new_n2 = old_to_new_node_map[e.n2];
                int cost = -1;
                for(pair<node*, int> p : e.n1->adjacency_list)
                    if(p.first == e.n2)
                        cost = p.second;

                new_n1->adjacency_list.push_back(pair<node*, int>(new_n2, cost));   // undirected edge is represented by
                new_n2->adjacency_list.push_back(pair<node*, int>(new_n1, cost));   // two directed edges, because of
            }                                                                       // which connection is made two way.
            return (*old_to_new_node_map.begin()).second;
        }
};

#endif