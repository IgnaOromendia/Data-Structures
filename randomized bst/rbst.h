#ifndef _RBST_H_
#define _RBST_H_

#include<random>

using namespace std;

template<typename T>
class rbst {
public:
    rbst();

    ~rbst();

    bool contains(const T& elem) const;

    void insert(const T& elem);

    void remove(const T& elem);

    const int size() const;

private:
    struct Node {
        Node(const T& v): value(v), left(nullptr), right(nullptr), subtree_size(1) {}
        T value;
        Node* left;
        Node* right;
        int subtree_size;
    };

    Node* _root;
    int _size;

    void destroy(Node* n);
    Node* search(Node* n, const T& elem) const;
    double uniform_number(const int l);
    void insert_root(Node*& n,const T& elem);
    void insert_aux(Node*& n, const T& elem);
    pair<Node*, Node*> split(Node* n, const T& elem, Node* smaller, Node* greater);
    void update_subtree_size(Node*& n);
};

template <typename T>
using split_pair = pair<typename rbst<T>::Node*, typename rbst<T>::Node*>;

#endif