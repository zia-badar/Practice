#include <iostream>
#include <sstream>

using namespace std;

template<typename result_type, typename data_type>
class segmented_tree
{
    private:
        class node
        {
            private:
                string to_string(string tab)
                {
                    ostringstream oss(ostringstream::ate);
                    oss << tab << "|--> data: " << *result << "\n";
                    tab += "\t";
                    if(left != NULL) oss << left->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    if(right != NULL) oss << right->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    return oss.str();
                }

            public:
                result_type *result;        // for leaf this field will be same as data
                data_type *data;            // only leafs have this field set
                node *left;
                node *right;
                int from;
                int to;

                // non leaf node constructor
                node(result_type *res, node *l, node *r, int i, int j): result(res), data(NULL), left(l), right(r), from(i), to(j){};
                // leaf node constructor
                node(data_type *d, result_type (*map)(data_type), int i, int j): result(new result_type(map(*d))), data(d), left(NULL), right(NULL), from(i), to(j){};

                friend ostream& operator<<(ostream &out, node &n)
                {
                    out << n.to_string("");
                    return out;
                }

                ~node()
                {
                    delete left;
                    delete right;
                    delete result;
                }
        };

        node* build(data_type *arr, int l, int r, result_type (*combine)(result_type, result_type), result_type (*map)(data_type))
        {
            if(l == r) return new node(&arr[l], map, l, l);

            node *ln = build(arr, l, (l+r)/2, combine, map);
            node *rn = build(arr, (l+r)/2 + 1, r, combine, map);
            return new node(new result_type(combine(*(ln->result), *(rn->result))), ln, rn, l, r);
        }

        result_type query(node *n, int f, int t, result_type (*combine)(result_type, result_type), result_type empty)
        {
            if(n == NULL || n->from > t || n->to < f) return empty;         // completely out of range case
            if(n->from >= f && n->to <= t) return *n->result;               // completely inside of range case
            return combine(query(n->left, f, t, combine, empty), query(n->right, f, t, combine, empty));    // partially inside of range
        }

    public:
        node *root;

        segmented_tree(): root(NULL) {}

        void build(data_type *arr, int s, result_type (*combine)(result_type, result_type), result_type (*map)(data_type))
        {
            root = build(arr, 0, s-1, combine, map);
        }

        result_type query(int f, int t, result_type (*combine)(result_type, result_type), result_type empty)
        {
            return query(root, f, t, combine, empty);
        }

        friend ostream& operator<<(ostream &out, segmented_tree &t)
        {
            out << *t.root;
            return out;
        }

        ~segmented_tree()
        {
            delete root;
        }
};


// range sum functions, empty value is 0
int combine_function1(int s1, int s2) { return s1 + s2; }
int map_function1(int i){ return i; }

// range string functions, empty value is ""
string combine_function2(string s1, string s2) { return s1 + s2; }
string map_function2(int i){ return "-"+to_string(i)+"-"; }

int main()
{
    int size = 10;
    int arr[size];
    for(int i=0; i<size; i++)
        arr[i] = i;

    segmented_tree<int, int> tree;
    tree.build(arr, size, combine_function1, map_function1);
    cout << "sum from 1 to 9: " << tree.query(1, 9,  combine_function1, 0) << endl;
    cout << "sum from 3 to 8: " << tree.query(3, 8,  combine_function1, 0) << endl;
    cout << "sum from 7 to 7: " << tree.query(7, 7,  combine_function1, 0) << endl;

    segmented_tree<string, int> *t2 = new segmented_tree<string, int>();
    t2->build(arr, size, combine_function2, map_function2);
    cout << "range string from 3 to 8 is: " << t2->query(3, 8, combine_function2, "") << endl;
    delete t2;


    return 0;
}