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

    void print(ostream& os) const;

    friend ostream& operator<<(ostream& os, bst<T>& b) {
        b.print(os);
        return os;
    }

private:

    struct Node {
        Node(const T& value): value(v), left(nullptr), right(nullptr) {}
        T value;
        Node* left;
        Node* right;
    }

    Node* _root;
    int _length;
};

#endif