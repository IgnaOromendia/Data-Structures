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
        _size++;
    } 
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
    if (n->right == nullptr) return search_father(_root, elem)->value;
    n = n->right;
    while(n->left != nullptr) {
        n = n->left;
    }
    return n->value;
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
    while(it->right != nullptr) {it = it->right;}
    return it->value;
}

template <typename T>
const int bst<T>::size() const {
    return _size;
}

template <typename T>
const bool bst<T>::empty() const {
    return _size == 0;
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
void bst<T>::insert_aux(Node *n, const T& elem) {
    if (n->value < elem) {
        if (n->right == nullptr) {
            Node* node = new Node(elem);
            n->right = node;
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
void bst<T>::remove_aux(Node *n, const T &elem) {
    Node* father = search_father(_root, elem);

    if (isLeaf(n)) { // Case 1: Is a leaf
        if (father->right == n) {
            father->right = nullptr;
        } else {
            father->left = nullptr;
        }
        delete n;
        _size--;
    } else if (n->left == nullptr or n->right == nullptr) { // Case 2: Just one son 
        if (_root->value != elem) {
            if (father->right == n) {
                if (n->left == nullptr) {
                    father->right = n->right;
                } else {
                    father->right = n->left;
                }
            } else {
                if (n->left == nullptr) {
                    father->left = n->right;
                } else {
                    father->left = n->left;
                }
            }
        } else {
            if (n->right == nullptr) {
                _root = n->left;
            } else {
                _root = n->right;
            }
        }
        delete n;
        _size--;
    } else { // Case 3: Two sons
        T replacement = next(elem);
        Node* to_remove = search(n, replacement);
        remove_aux(to_remove, replacement);
        n->value = replacement;
    }
    
}

template <typename T>
typename bst<T>::Node* bst<T>::search(bst::Node* n, const T &elem) const {
    if (n == nullptr)     return nullptr;
    if (n->value == elem) return n;
    return search(n->value < elem ? n->right : n->left, elem);
}

template <typename T>
typename bst<T>::Node *bst<T>::search_father(Node *n, const T &elem) const {
    if (elem == _root->value) return nullptr;
    if (n->right != nullptr) if (n->right->value == elem) return n;
    if (n->left != nullptr) if (n->left->value == elem) return n;
    return search_father(n->value < elem ? n->right : n->left, elem);
}

template <typename T>
bool bst<T>::isLeaf(Node *n) {
    return n->left == nullptr and n->right == nullptr;
}