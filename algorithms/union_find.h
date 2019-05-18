#ifndef UNION_FIND_H
#define UNION_FIND_H

class union_find
{
    private:
        int* parent;    // it will be the responsiblity of the calling code to ensure each entity is represented by a
        int* size;      // unique int. so that array can be used for constant time access
        int find(int e)
        {
            if(parent[e] == -1) return e;
            else return (parent[e] = find(parent[e]));  // using path compression
        }

    public:
        union_find(int s)
        {
            parent = new int[s];
            size = new int[s];
            for(int i=0; i<s; i++)
            {
                parent[i] = -1;
                size[i] = 0;
            }
        }

        // creating connection between entity e1, e2
        void connect(int e1, int e2)
        {
            int p1 = find(e1);
            int p2 = find(e2);
            if(size[p1] > size[p2])         // using rank to decide which entity should be child of which
            {
                parent[p2] = p1;
                size[p1] += size[p2];
            }
            else
            {
                parent[p1] = p2;
                size[p2] += size[p1];
            }
        }

        bool are_connected(int e1, int e2){ return find(e1) != -1 && find(e1) == find(e2); }

};

#endif


