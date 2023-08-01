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
    friend class FH_handle;

    class FH_handle {
        friend class fibonacci_heap;
    public:
        FH_handle(): _p(nullptr) {};

        pair<T,double> operator*() const {
            if (p == nullptr) return make_pair(0,INF);
            return make_pair(p->elem, p->prio);
        }
    private:
        Node* p;
    };

    fibonacci_heap();

    ~fibonacci_heap();

    FH_handle insert(const T& elem, const double& prio);

    FH_handle min() const;

    void extract_min();

    void decrease_key(FH_handle h, const double& prio);

    bool empty() const;

    int size() const;

private:

    struct Node {
        T elem;
        double prio;
        int degree;
        bool mark;

        Node* parent;
        Node* first_child;
        Node* right;
        Node* left;

        Node(const T& e, const double& p,) {
            elem = e;
            prio = p;
            degree = 0;
            mark = false;
            parent = nullptr;
            first_child = nullptr;
            rigth = this;
            left = this;
        }
    };

    int _size;
    Node* _min;

    void consolidate();
    void swap(Node*& x, Node*& y);
    void link(Node*& x, Node*& y);
};

#endif
