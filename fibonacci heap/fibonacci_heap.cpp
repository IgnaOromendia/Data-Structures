#include"fibonacci_heap.h"

template <typename T>
fibonacci_heap<T>::fibonacci_heap(): _size(0), _min(nullptr), _size_root(0), _basic_operations(0) {}

template <typename T>
fibonacci_heap<T>::~fibonacci_heap() {
    destroy(_min);
}

template <typename T>
typename fibonacci_heap<T>::FH_handle fibonacci_heap<T>::insert(const T &elem, const double &prio) {
    Node* node = new Node(elem, prio);
    if (_min == nullptr) {
        _min = node;
    } else {
        // Adding node into the root list
        // _min->left = last item in root list
        node->right = _min;
        node->left = _min->left;
        _min->left->right = node;
        _min->left = node;
        if(node->prio < _min->prio) _min = node;
    }
    _basic_operations++;
    _size_root++;
    _size++;
    return FH_handle(node);
}

template <typename T>
typename fibonacci_heap<T>::FH_handle fibonacci_heap<T>::min() const {
    return FH_handle(_min);
}

template <typename T>
void fibonacci_heap<T>::extract_min() {
    Node* z = _min;
    if (z != nullptr) {
        // Removing from parent
        if (z->first_child != nullptr) {
            int childs = 0;
            Node* first_child = z->first_child;
            while (first_child->parent != nullptr) {
                first_child->parent = nullptr;
                first_child = first_child->right;
                childs++;
            }
            // Adding the childs to the root list 
            Node* last_child = first_child->left;
            first_child->left = z->left;
            z->left->right = first_child;
            z->left = last_child;
            last_child->right = z; 
            _size_root += childs;
            _basic_operations += childs;
        }

        _min = _min->right;

        // Removing min from root list
        z->right->left = z->left;
        z->left->right = z->right;
        _size_root--;
        _basic_operations++;

        if (_size == 1) {
            _min = nullptr;
        } else {
            consolidate();
        }
        _size--;
        delete z;
    }
}

template <typename T>
void fibonacci_heap<T>::decrease_key(fibonacci_heap<T>::FH_handle h, const double &prio) {
    Node* node = h.p;
    Node* parent = node->parent;
    if (prio > node->prio) {return;}
    node->prio = prio;
    if (parent != nullptr and node->prio < parent->prio) {
        cut(node, parent);
        cascade_cut(parent);
    }
    if (prio < _min->prio) _min = node;
}

template <typename T>
const bool fibonacci_heap<T>::empty() const {
    return _size == 0;
}

template <typename T>
const int fibonacci_heap<T>::size() const {
    return _size;
}

template <typename T>
int fibonacci_heap<T>::basic_operations() const {
    return _basic_operations;
}

// AUXILIARS

template <typename T>
void fibonacci_heap<T>::consolidate() {
    int rank = (1.44 * log2(_size)) + 1;
    vector<Node*> A(rank, nullptr);
    Node* x = _min; // x is going to be my iterator node
    int j = 0;
    int size = _size_root;
    
    // Joining by degree
    while (j < size) {
        int d = x->degree;
        while(A[d] != nullptr) {
            Node* y = A[d];
            if (x->prio > y->prio) {
                link(y,x);
                x = y;
            } else {
                link(x,y);
            }
            _basic_operations++;
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        x = x->right;
        j++;
    }
    
    _min = nullptr;
    _size_root = 0;

    // Joining degrees
    for(int i = 0; i < rank; i++) {
        if(A[i] != nullptr) {
            _basic_operations++;
            if (_min == nullptr) {
                _size_root = 1;
                _min = A[i];
                _min->right = _min;
                _min->left = _min;
            } else {
                // Adding A[i] into the root list
                A[i]->right = _min;
                A[i]->left = _min->left;
                _min->left->right = A[i];
                _min->left = A[i];
                if(A[i]->prio < _min->prio) _min = A[i];
                _size_root++;
            }
        }
    }
}

template <typename T>
void fibonacci_heap<T>::link(Node* x, Node* y) {
    y->mark = false;
    x->degree++;
    _size_root--;

    // Removing from root list
    y->left->right = y->right; 
    y->right->left = y->left;

    // Adding y as a child of x
    if (x->first_child != nullptr) {
        y->right = x->first_child;
        y->left = x->first_child->left;
        x->first_child->left->right = y;
        x->first_child->left = y;
    } else {
        y->right = y;
        y->left = y;
    }
    x->first_child = y;
    y->parent = x;
}

template <typename T>
void fibonacci_heap<T>::destroy(Node *n) {
    while(n != nullptr) {
        if(n != n->right and n->right != _min) destroy(n->right);
        if(n->first_child != nullptr) destroy(n->first_child);
        delete n;
        n = nullptr;
    }
}

template <typename T>
void fibonacci_heap<T>::cut(Node* x, Node* y) {
    // removing x from y's childs
    if (x != x->right) {
        if (y->first_child == x) y->first_child = x->right;
        x->right->left = x->left;
        x->left->right = x->right;
    } else {
        y->first_child = nullptr;
        y->degree--;
    }
    x->parent = nullptr;
    x->mark = false;

    // Adding x to the root list
    x->right = _min;
    x->left = _min->left;
    _min->left->right = x;
    _min->left = x;
    _size_root++;
    _basic_operations += 2;
}

template <typename T>
void fibonacci_heap<T>::cascade_cut(Node* y) {
    Node* z = y->parent;
    if (z != nullptr) {
        Node* it = y;
        int maxD = 0;

        do {
            if (it->degree > maxD) maxD = it->degree;
            it = it->right;
        } while(it != y);

        z->degree = maxD + 1;

        if (not y->mark) {
            y->mark = true;
        } else {
            cut(y,z);
            cascade_cut(z);
        }
    }
}
