#include <iostream>
#include <sstream>

using namespace std;

template<typename type>
class avl
{
    #define get_height(n) (n == NULL ? 0 : n->height)
    #define update_height(n) (n->height = 1 + max(get_height(n->left), get_height(n->right)))

    private:
        class node
        {
            private:
                string to_string(string tab)
                {
                    ostringstream oss(ostringstream::ate);
                    oss << tab << "|--> (data: " << data << ", height: " << height << ")\n";
                    tab += "\t";
                    if(left != NULL) oss << left->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    if(right != NULL) oss << right->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    return oss.str();
                }

            public:
                type& data;
                node *left;
                node *right;
                int height;

                node(type &d): data(d), left(NULL), right(NULL), height(1) {}
                node(type &d, node *l, node *r): data(d), left(l), right(r), height(1) {}

                friend ostream& operator<<(ostream &out, node &n)
                {
                    out << n.to_string("");
                    return out;
                }
        };
        node* head;

        node* add(node *n, type &d)
        {
            if(n == NULL) return new node(d);

            if(d < n->data) n->left = add(n->left, d);
            else if(d > n->data) n->right = add(n->right, d);
            else return n;

            int lh = get_height(n->left);
            int rh = get_height(n->right);

            if(abs(lh - rh) > 1)
                n = balance(n);

            update_height(n);
            return n;
        }

        node* balance(node *n)
        {
            int lh = get_height(n->left);
            int rh = get_height(n->right);

            node *t;
            if(lh > rh)
            {
                t = n->left;
                lh = get_height(t->left);
                rh = get_height(t->right);
                if(lh > rh)                     // left left case
                    n = right_rotate(n);
                else if(rh > lh)                // left right case
                {
                    n->left = left_rotate(t);
                    n = right_rotate(n);
                }
            }
            else if(rh > lh)
            {
                t = n->right;
                lh = get_height(t->left);
                rh = get_height(t->right);
                if(rh > lh)                     // right right case
                    n = left_rotate(n);
                else if(lh > rh)                // right left case
                {
                    n->right = right_rotate(t);
                    n = left_rotate(n);
                }
            }
            return n;
        }

        node* left_rotate(node *n)
        {
            node *ret = n->right;
            if(ret == NULL) return n;
            node *t = ret->left;
            ret->left = n;
            n->right = t;
            n->height = update_height(n);
            ret->height = update_height(ret);
            return ret;
        }

        node* right_rotate(node *n)
        {
            node *ret = n->left;
            if(ret == NULL) return n;
            node *t = ret->right;
            ret->right = n;
            n->left = t;
            n->height = update_height(n);
            ret->height = update_height(ret);
            return ret;
        }

        friend ostream& operator<<(ostream &out, avl &t)
        {
            out << "------------------------------------------------\n";
            out << *t.head;
            out << "------------------------------------------------\n";
            return out;
        }
    public:
        avl(): head(NULL) {}

        void add(type &d)
        {
            head = add(head, d);
        }

};

int main()
{
    avl<int> t;
    int size = 1023;        // 2^n-1 elements creates n height avl tree
    int arr[size];


    for (int i = 0; i < size; i++)
        t.add(arr[i] = i+1);

    cout << t;

    return 0;
}