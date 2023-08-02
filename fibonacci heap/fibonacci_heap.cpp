#include"fibonacci_heap.h"

template <typename T>
fibonacci_heap<T>::fibonacci_heap(): _size(0), _min(nullptr), _size_root(0) {}

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
        }

        _min = _min->right;

        // Removing min from root list
        z->right->left = z->left;
        z->left->right = z->right;
        _size_root--;

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
}

template <typename T>
bool fibonacci_heap<T>::empty() const {
    return _size == 0;
}

template <typename T>
int fibonacci_heap<T>::size() const {
    return _size;
}

// AUXILIARS

template <typename T>
void fibonacci_heap<T>::consolidate() {
    int rank = (1.44 * log2(_size)) + 1;
    vector<Node*> A(rank, nullptr);
    Node* x = _min; // x is going to be my node iterator
    int j = 0;
    int size = _size_root;
    
    while (j < size) {
        int d = x->degree;
        while(A[d] != nullptr) {
            Node* y = A[d];
            if (x->prio > y->prio) swap(x,y);
            link(x,y);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        x = x->right;
        j++;
    }
    
    _min = nullptr;
    _size_root = 0;

    for(int i = 0; i < rank; i++) {
        if(A[i] != nullptr) {
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
void fibonacci_heap<T>::swap(Node *&x, Node *&y) {
    T elem_temp = x->elem;
    double prio_temp = x->prio;
    Node* temp = x->first_child; 
    x->elem = y->elem;
    x->prio = y->prio;
    x->first_child = y->first_child;
    y->elem = elem_temp;
    y->prio = prio_temp;
    y->first_child = temp;
}

template <typename T>
void fibonacci_heap<T>::link(Node *&x, Node *&y) {
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
        if(n != n->right and n != _min) destroy(n->right);
        if(n->first_child != nullptr) destroy(n->first_child);
        delete n;
        n = nullptr;
    }
}
