#include "skip_list.h"

template <typename T>
skipList<T>::skipList(const double& p, const int& max_level): _p(p), _height(0), _size(0), _max_level(max_level) {
    _header = new Node(-1, max_level);
}

template <typename T>
skipList<T>::~skipList(){
    delete _header;
}
template <typename T>
bool skipList<T>::contains(const T &elem) const {
    Node* p = _header; int l = _height;

    while (l > 0) {
        if (p->next[l] == nullptr or elem <= p->next[l]->value) {
            l--;
        } else {
            p = p->next[l];
        }
    }

    return p->next[0] != nullptr and elem == p->next[0]->value;
}

template <typename T>
void skipList<T>::insert(const T &elem){
    Node* p = _header; int l = _height;
    Node** pred = new Node*[_max_level+1];
    for(int i = 0; i <= _max_level; i++) 
        pred[i] = _header;

    // Searching for place
    while (l > 0) {
        if(p->next[l] == nullptr or elem <= p->next[l]->value) {
            pred[l] = p;
            l--;
        } else {
            p = p->next[l];
        }
    }

    // Adding levels
    int h = 1;
    while(uniform_number() < _p and h < _max_level) h++;

    if(h > _height) _height = h;

    // Inserting
    Node* new_node = new Node(elem,h);

    for(int i = 0; i <= h; i++) {
        new_node->next[i] = pred[i]->next[i];
        pred[i]->next[i] = new_node;
    }

    _size++;
}

template <typename T>
void skipList<T>::remove(const T &elem) {
    // TODO
}

template <typename T>
int skipList<T>::height() const {
    return _height;
}

template <typename T>
bool skipList<T>::empty() const {
    return _size == 0;
}

template <typename T>
void skipList<T>::size() const {
    return _size;
}

template <typename T>
void skipList<T>::print(ostream &os) {
    for(int i = 0; i < _height; i++) {
        cout << "Lvl " << i << ": ";
        Node* node = _header->next[i]; 
        while(node != nullptr) {
            cout << node->value << " ";
            node = node->next[i];
        }
        cout << "\n";
    }
}

// AUXILIARS

template <typename T>
double skipList<T>::uniform_number() {
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(0,1);
    return distribution(generator);
};
