#include "bst.h"

template<typename T>
bst<T>::bst(): _root(nullptr), _size(0) {}

template <typename T>
bst<T>::~bst() {
    destroy(_root);
}

template <typename T>
void bst<T>::insert(const T &elem) {
    if(!contains(elem)) {
        if (_root == nullptr) {
            _root = new Node(elem);
        } else {
            insert_aux(_root, elem);
        }
    } 
    _size++;
}

template <typename T>
bool bst<T>::contains(const T &elem) const {
    return search(_root, elem) != nullptr;
}

template <typename T>
void bst<T>::remove(const T &elem) {
    if (contains(elem)) {
        if (_size == 1) {
            delete _root;
            _root = nullptr;
            _size = 0;
        }  else {
            remove_aux(search(_root, elem), elem);
        }
    }
}

template <typename T>
const T& bst<T>::next(const T &elem) const {
    Node* n = search(_root, elem);
    if (n->right == nullptr) return search_father(_root, elem);
    n = n->right;
    while(n->left != nullptr) {
        n = n->left;
    }
    return n;
}

template <typename T>
const T& bst<T>::min() const {
    Node* it = _root;
    while(it->left != nullptr) it = it->left;
    return it->value;
}

template <typename T>
const T& bst<T>::max() const {
    Node* it = _root;
    while(it->right != nullptr) it = it->left;
    return it->value;
}

template <typename T>
const int bst<T>::size() const {
    return _size;
}

// AUXILIARS

template<class T>
void bst<T>::destroy(bst::Node* n) {
    if(n != nullptr) {
        destroy(n->right);
        destroy(n->left);
        delete n;
    }
}

template <typename T>
void bst<T>::insert_aux(Node *n, T& elem) {
    if (n->value < elem) {
        if (n->right == nullptr) {
            n->right = new Node(elem);
        } else {
            insert_aux(n->right,elem);
        }
    } else {
        if (n->left == nullptr) {
            n->left = new Node(elem);
        } else {
            insert_aux(n->left,elem);
        }
    }
}

template <typename T>
void bst<T>::remove_aux(Node *n, T &elem) {
    Node* father = search_father(_root, elem);
    Node* replacement = father->right == n ? father->right : father->left;

    if (isLeaf(n)) { // Case 1: Is a leaf
        replacement = nullptr;
        delete n;
        _size--;
    } else if (n->left == nullptr or n->right == nullptr) { // Case 2: Just one son 
        if (_root->value != elem) {
            replacement = n->izq == nullptr ? n->right : n->left;
        } else {
            _root = n->right == nullptr ? n->left : n->right;
        }
        delete n;
        _size--;
    } else { // Case 3: Two sons
        T replacement = next(elem);
        Node* to_remove = search(_root, replacement);
        remove_aux(n->value < reeplacement ? n->right : n->left, replacement);
        n->value = replacement;
    }
    
}

template <typename T>
bst<T>::Node* bst<T>::search(Node* n,T &elem){
    if (n == nullptr)     return nullptr;
    if (n->value == elem) return n;
    search(n->value < elem ? n->right : n->left, elem);
}

template <typename T>
bst<T>::Node *bst<T>::search_father(Node *n, T &elem) {
    if (n == _root) return nullptr;
    if (n->right != nullptr) if (n->right->valur == elem) return n;
    if (n->left != nullptr) if (n->left->valur == elem) return n;
    search_father(n->value < elem ? n->right : n->left, elem);
}

template <typename T>
bool bst<T>::isLeaf(Node *n) {
    return n->left == nullptr and n->right == nullptr;
}