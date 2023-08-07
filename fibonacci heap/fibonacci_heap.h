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

        Node(Node* n) {
            elem = n->elem;
            prio = n->prio;
            degree = n->degree;
            mark = n->mark;
            parent = n->parent;
            first_child = n->first_child;
            right = this;
            left = this;
        }
    };

    int _size;
    int _size_root;
    Node* _min;
    int _basic_operations;

    void consolidate();
    void link(Node* x, Node* y);
    void destroy(Node* n);
    void cut(Node* x, Node* y);
    void cascade_cut(Node* y);
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
