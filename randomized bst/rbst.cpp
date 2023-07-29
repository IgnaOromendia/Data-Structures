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
    
}

template <typename T>
const int rbst<T>::size() const {
    return _size;
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
double rbst<T>::uniform_number(const int l) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, l);
    return distribution(generator);
}

template <typename T>
void rbst<T>::insert_root(Node*& n, const T &elem) {
    Node* new_node = new Node(elem);

    split_pair<T> pair = split(n, elem, n->left, n->right);

    n = new_node;
    new_node->left  = pair.first;
    new_node->right = pair.second;
}

template <typename T>
void rbst<T>::insert_aux(rbst::Node*& n, const T &elem) {
    if (uniform_number(_size) == 0) return insert_root(n, elem);
    if (elem < n->value) {
        if (n->left == nullptr) {
            n->left = new Node(elem);
            //n->subtree_size++;
        } else {
            insert_aux(n->left, elem);
        }
    } else {
        if (n->right == nullptr) {
            n->right = new Node(elem);
            //n->subtree_size++;
        } else {
            insert_aux(n->right, elem);
        }
    }
}

// TODO: Devolver smaller and greater
template <typename T>
split_pair<T> rbst<T>::split(Node *n, const T &elem, Node *smaller, Node *greater) {
    if (n == nullptr) return make_pair(nullptr, nullptr);
    if (elem < n->value) {
        if (smaller != nullptr) {
            split_pair<T> pair = split(n->left, elem, smaller->left, smaller->right);
            n->left = pair.second;
            // Update size
            return make_pair(pair.first, n);
        } else {
            return make_pair(nullptr, n);
        }
    } else {
        if (greater != nullptr) {
            split_pair<T> pair = split(n->right, elem, greater->left, greater->right);
            n->right = pair.first;
            // Update size
            return make_pair(n, pair.second);
        } else {
            return make_pair(n, nullptr);
        }
    }
}
