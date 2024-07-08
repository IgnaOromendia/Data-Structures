#include"rbst.h"

template<typename T>
rbst<T>::rbst(): _root(nullptr), _size(0) {}

template <typename T>
rbst<T>::~rbst(){
    destroy(_root);
}

template <typename T>
bool rbst<T>::contains(const T &elem) const {
    return search(_root, elem) != nullptr;
}

template <typename T>
void rbst<T>::insert(const T &elem) {
    if (!contains(elem)) {
        if (_root == nullptr) {
            _root = new Node(elem);
        } else {
            insert_aux(_root, elem);
        }
        _size++;
    }
}

template <typename T>
void rbst<T>::remove(const T &elem) {
    if (contains(elem)) {
        if (_size == 1) {
            delete _root;
            _root = nullptr;
            _size = 0;
        }  else {
            if (elem == _root->value) {
                _root = remove_aux(_root, elem);
            } else {
                remove_aux(_root, elem);
            }
            _size--;
        }
    }
}

template <typename T>
const int rbst<T>::size() const {
    return _size;
}

template <typename T>
const bool rbst<T>::empty() const{
    return _size == 0;
}

template <typename T>
const T& rbst<T>::min() const {
    Node* it = _root;
    while(it->left != nullptr) it = it->left;
    return it->value;
}

template <typename T>
const T& rbst<T>::max() const {
    Node* it = _root;
    while(it->right != nullptr) it = it->right;
    return it->value;
}

// AUXILIARS

template <typename T>
void rbst<T>::destroy(Node* n){
    if (n != nullptr) {
        destroy(n->right);
        destroy(n->left);
        delete n;
    }
}

template<typename T>
typename rbst<T>::Node* rbst<T>::search(rbst::Node* n, const T& elem) const {
    if (n == nullptr)     return nullptr;
    if (n->value == elem) return n;
    return search(n->value < elem ? n->right : n->left, elem);
}

template <typename T>
int rbst<T>::uniform_number(const int l) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, l);
    return distribution(generator);
}

template <typename T>
void rbst<T>::insert_aux(rbst::Node*& n, const T &elem) {
    int N = n->subtree_size;
    if (uniform_number(N) == N) return insert_root(n, elem);
    if (elem < n->value) {
        if (n->left == nullptr) {
            n->left = new Node(elem);
            n->subtree_size++;
        } else {
            insert_aux(n->left, elem);
            update_subtree_size(n);
        }
    } else {
        if (n->right == nullptr) {
            n->right = new Node(elem);
            n->subtree_size++;
        } else {
            insert_aux(n->right, elem);
            update_subtree_size(n);
        }
    }
}

template <typename T>
void rbst<T>::insert_root(Node*& n, const T &elem) {
    Node* new_node = new Node(elem);
    Node* S;
    Node* G;

    split(n, elem, S, G);

    n = new_node;
    new_node->left  = S;
    new_node->right = G;
    update_subtree_size(new_node);
}

template <typename T>
void rbst<T>::split(Node *n, const T &elem, Node*& smaller, Node*& greater) {
    if (n == nullptr) {
        smaller = nullptr;
        greater = nullptr;
        return;
    }
    if (elem < n->value) {
        greater = n;
        split(n->left, elem, smaller, greater->left);
        update_subtree_size(n);
    } else {
        smaller = n;
        split(n->right, elem, smaller->right, greater);
        update_subtree_size(n);
    }
}

template <typename T>
void rbst<T>::update_subtree_size(Node *&n) {
    if (n != nullptr) {
        int subt_s = 1;
        if (n->left != nullptr) subt_s += n->left->subtree_size;
        if (n->right != nullptr) subt_s += n->right->subtree_size;
        n->subtree_size = subt_s;
    }
}

template <typename T>
typename rbst<T>::Node* rbst<T>::remove_aux(Node *n, const T &elem) {
    if (n == nullptr) return nullptr;
    if (n->value == elem) {
        n = join(n->left, n->right);
        update_subtree_size(n);
        return n;
    }
    if (elem < n->value) {
        n->left = remove_aux(n->left, elem);
    } else {
        n->right = remove_aux(n->right, elem);
    }
    update_subtree_size(n);
    return n;
}


template <typename T>
typename rbst<T>::Node* rbst<T>::join(Node *&n1, Node *&n2) {
    if (n1 == nullptr and n2 == nullptr) return nullptr;
    if (n1 == nullptr) return n2;
    if (n2 == nullptr) return n1;

    int m = n2->subtree_size;
    int n = n1->subtree_size;
    double x = uniform_number(n + m);

    if (x < m) {    // p = m / (n + m)
        n1->right = join(n1->right, n2);
        update_subtree_size(n1);
        return n1;
    } else {        // p = n / (n + m)
        n2->left = join(n1, n2->left);
        update_subtree_size(n2);
        return n2;
    }
}
