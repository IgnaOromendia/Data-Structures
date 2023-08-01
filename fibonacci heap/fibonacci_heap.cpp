#include"fibonacci_heap.h"

template <typename T>
fibonacci_heap<T>::fibonacci_heap(): _size(0), _min(nullptr) {}

template <typename T>
fibonacci_heap<T>::FH_handle fibonacci_heap<T>::insert(const T &elem, const double &prio) {
    Node* node = new Node(elem, prio);
    if (_min == nullptr) {
        _min = node;
    } else {
        // Adding node into the root list
        // _min->left = last item in root list
        node->right = _min;
        node->left = _min->left;
        _min->left->rigth = node;
        _min->left = node;
        if(node->prio < _min->prio) _min = node;
    }
    _size++;
    return node;
}

template <typename T>
fibonacci_heap<T>::FH_handle fibonacci_heap<T>::min() const {
    return _min;
}

template <typename T>
void fibonacci_heap<T>::extract_min() {
    if (_min != nullptr) {
        // Removing from parent
        if (_min->first_child != nullptr) {
            Node* first_child = _min->first_child;
            while (first_child->parent != nullptr) {
                first_child->parent = nullptr;
                first_child = first_child->right;
            }
            // Adding the childs to the root list 
            Node* last_child = first_child->left;
            first_child->left = _min->left;
            _min->left->right = first_child;
            _min->left = last_child;
            last_child->right = _min; 
        }

        _min = _min->right;

        // Removing _min from root list
        _min->right->left = _min->left;
        _min->left->rigth = _min->right;

        if (_size == 1) {
            _min = nullptr;
        } else {
            consolidate();
        }
        _size--;
    }
}

template <typename T>
void fibonacci_heap<T>::decrease_key(FH_handle h, const double &prio) {
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
    
    while (x->right != nullptr) {
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
    }

    _min = nullptr;

    for(int i = 0; i < rank; i++) {
        if(A[i] != nullptr) {
            if (_min == nullptr) {
                _min = A[i];
                _min->right = _min;
                _min->left = _min;
            } else {
                // Adding A[i] into the root list
                A[i]->right = _min;
                A[i]->left = _min->left;
                _min->left->rigth = A[i];
                _min->left = A[i];
                if(A[i]->prio < _min->prio) _min = A[i];
            }
        }
    }
    

}

template <typename T>
void fibonacci_heap<T>::swap(Node *&x, Node *&y) {
    Node* temp = x;
    x->elem = y->elem;
    x->prio = y->prio;
    y->elem = temp->elem;
    y->prio = temp->prio;
}

template <typename T>
void fibonacci_heap<T>::link(Node *&x, Node *&y) {
    y->mark = false;
    x->degree++;

    // Removing from root list
    y->left->rigth = y->right; 
    y->right->left = y->left;

    // Adding y as a child of x
    if (x->first_child != nullptr) {
        y->right = x->first_child;
        y->left = x->first_child->left;
        x->first_child->left->right = y;
        x->first_child->left = y;
    }
    x->first_child = y;
    y->parent = x;
}
