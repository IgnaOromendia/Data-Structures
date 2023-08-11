#include"fibonacci_heap.h"

template <typename T>
fibonacci_heap<T>::fibonacci_heap(): _size(0), _min(nullptr), _basic_operations(0) {}

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
        add_to_root_list(node);
        if(node->prio < _min->prio) _min = node;
    }
    _basic_operations++;
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
            z->first_child = nullptr;
            // Adding the childs to the root list 
            Node* last_child = first_child->left;
            first_child->left = z->left;
            z->left->right = first_child;
            z->left = last_child;
            last_child->right = z; 
            _basic_operations += childs;
        }

       remove_from_root_list(z);
        _basic_operations++;

        if (_size == 1) {
            _min = nullptr;
        } else {
            consolidate();
        }
        _size--;
        delete z;
        z = nullptr;
    }
}

template <typename T>
void fibonacci_heap<T>::decrease_key(fibonacci_heap<T>::FH_handle h, const double &prio) {
    Node* node = h.p;
    Node* parent = node->parent;
    if (prio > node->prio) return;
    node->prio = prio;
    if (parent != nullptr and node->prio < parent->prio) {
        cut(node, parent);
        cascade_cut(parent);
    }
    if (node->prio < _min->prio) _min = node;
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
    vector<Node*> root_nodes;

    count_nodes(_min, root_nodes);

    // Union by degree
    for(int i = 0; i < root_nodes.size(); i++) {
        Node* x = root_nodes[i];
        int d = x->degree;
        while(A[d] != nullptr) {
            Node* y = A[d];
            if (x->prio > y->prio) {
                link(y,x); // x become child of y
                x = y;
            } else {
                link(x,y); // y become child of x
            }
            _basic_operations++;
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }
    
    _min = nullptr;

    // Joining degrees
    for(int i = 0; i < rank; i++) {
        if(A[i] != nullptr) {
            _basic_operations++;
            if (_min == nullptr) {
                _min = A[i];
                _min->right = _min;
                _min->left = _min;
            } else {
                // Adding A[i] into the root list
                add_to_root_list(A[i]);
                if(A[i]->prio < _min->prio) _min = A[i];
            }
        }
    }
}

template <typename T>
void fibonacci_heap<T>::link(Node* x, Node* y) {
    y->mark = false;
    x->degree++;

    // Removing from root list
    remove_from_root_list(y);

    // Adding y as a child of x
    add_to_child_list(x,y);
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
    remove_from_child_list(y,x);
    x->mark = false;

    // Adding x to the root list
    add_to_root_list(x);
    _basic_operations += 2;
}

template <typename T>
void fibonacci_heap<T>::cascade_cut(Node* y) {
    Node* z = y->parent;
    if (z != nullptr) {
        if (not y->mark) {
            y->mark = true;
        } else {
            cut(y,z);
            cascade_cut(z);
        }
    }
}

template <typename T>
void fibonacci_heap<T>::add_to_root_list(Node* x) {
    x->right = _min;
    x->left = _min->left;
    _min->left->right = x;
    _min->left = x;
}

template <typename T>
void fibonacci_heap<T>::add_to_child_list(Node *parent, Node *new_child) {
    if (parent->first_child != nullptr) {
        new_child->right = parent->first_child;
        new_child->left = parent->first_child->left;
        parent->first_child->left->right = new_child;
        parent->first_child->left = new_child;
    } else {
        new_child->right = new_child;
        new_child->left = new_child;
    }
    parent->first_child = new_child;
    new_child->parent = parent;
}

template <typename T>
void fibonacci_heap<T>::remove_from_root_list(Node *x) {
    if (x == _min) _min = x->right;
    x->right->left = x->left;
    x->left->right = x->right;
}

template <typename T>
void fibonacci_heap<T>::remove_from_child_list(Node *parent, Node* child) {
    if (child == child->right) {
        parent->first_child = nullptr;
        parent->degree = 0;
    } else if (parent->first_child == child){
        parent->first_child = child->right;
    }

    child->left->right = child->right;
    child->right->left = child->left;
    child->parent = nullptr;

    if (parent->first_child != nullptr) {
        Node* it = parent->first_child;
        int max_degree = 0;
        do {
            if (it->degree > max_degree) max_degree = it->degree;
            it = it->right;
        } while(it != parent->first_child);
        parent->degree = max_degree + 1;
    }
}

template <typename T>
void fibonacci_heap<T>::count_nodes(Node *n, vector<Node*>& v) {
    Node* it = n;
    do {
        v.push_back(it);
        it = it->right;
    } while(it != n);
}
