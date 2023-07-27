#ifndef BST_h
#define BST_h

#include<iostream>

using namespace std;

template<typename T>
class bst {
public:
    bst();

    ~bst();

    void insert(const T& elem);

    bool contains(const T& elem) const;

    void remove(const T& elem);

    const T& next(const T& elem) const;

    const T& min() const;

    const T& max() const;

    const int size() const;

private:

    struct Node {
        Node(const T& v): value(v), left(nullptr), right(nullptr) {}
        T value;
        Node* left;
        Node* right;
    };

    Node* _root;
    int _size;

    void destroy(Node* n); 
    void insert_aux(Node* n, const T& elem);
    void remove_aux(Node* n, const T& elem);
    Node* search(Node* n, const T& elem) const;
    Node* search_father(Node* n, const T& elem) const;
    bool isLeaf(Node* n);
};

#endif