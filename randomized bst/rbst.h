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

    // Destroy all the nodes
    void destroy(Node* n);

    // Search and return a node
    Node* search(Node* n, const T& elem) const;

    // A random number with uniform distribution between 0 and l
    int uniform_number(const int l);

    // Recursive insertion
    void insert_aux(Node*& n, const T& elem);

    // Insert the node in the root
    void insert_root(Node*& n,const T& elem);

    // Split the tree
    pair<Node*, Node*> split(Node* n, const T& elem, Node* smaller, Node* greater);

    // Update the subtree size of n
    void update_subtree_size(Node*& n);

    // Recursive deletion
    Node* remove_aux(Node* n, const T& elem);

    // Remove root
    Node* remove_root(Node*& n);

    // Joint two trees
    Node* join(Node*& n1, Node*& n2);

    // A real random number between 0 and 1
    double real_random();
};

template <typename T>
using split_pair = pair<typename rbst<T>::Node*, typename rbst<T>::Node*>;

#endif