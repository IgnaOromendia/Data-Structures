#ifndef _FIB_H_
#define _FIB_H_

#include<limits>
#include<vector>
#include<cmath>

using namespace std;

const double INF = numeric_limits<double>::max();

template<typename T>
class fibonacci_heap {
public:
    class FH_handle;

    friend class FH_handle;

    fibonacci_heap();

    ~fibonacci_heap();

    FH_handle insert(const T& elem, const double& prio);

    FH_handle min() const;

    void extract_min();

    void decrease_key(FH_handle h, const double& prio);

    const bool empty() const;

    const int size() const;

    int basic_operations() const;

private:

    struct Node {
        T elem;
        double prio;
        int degree;
        bool mark;

        Node* parent;
        Node* first_child;
        Node* left;
        Node* right;

        Node(const T& e, const double& p) {
            elem = e;
            prio = p;
            degree = 0;
            mark = false;
            parent = nullptr;
            first_child = nullptr;
            right = this;
            left = this;
        }
    };

    int _size;
    Node* _min;
    int _basic_operations;

    // Consolidate all the sub-trees
    void consolidate();

    // Make y child of x
    void link(Node* x, Node* y);

    // Remove all the nodes
    void destroy(Node* n);

    // Cut x form y
    void cut(Node* x, Node* y);

    // Recursive cut
    void cascade_cut(Node* y);

    // Add a node to the root list
    void add_to_root_list(Node* x);

    // Add a new child to a node
    void add_to_child_list(Node* parent, Node* new_child);

    // Remove from root list
    void remove_from_root_list(Node* x);
    
    // Remove from child list
    void remove_from_child_list(Node* parent, Node* child);

    // Count the nodes in its level
    void count_nodes(Node* x, vector<Node*>& v);
};

template<typename T>
class fibonacci_heap<T>::FH_handle {
public:
    friend class fibonacci_heap<T>;

    FH_handle(): p(nullptr) {};

    FH_handle(fibonacci_heap<T>::Node* n): p(n) {};

    pair<T,double> operator*() const {
        if (p == nullptr) return make_pair(0,INF);
        return make_pair(p->elem, p->prio);
    }
private:
    typename fibonacci_heap<T>::Node* p;
};

#endif
