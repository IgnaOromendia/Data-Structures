#include "sortedList.h"
#include<cmath>

template <typename T>
sortedList<T>::Node::Node(const T& elem): value(elem), next(nullptr), prev(nullptr) {};

template <typename T>
sortedList<T>::sortedList(): _first(nullptr), _last(nullptr), _length(0) {};

template <typename T>
sortedList<T>::sortedList(const sortedList<T> &l){
    *this = l;
};

template <typename T>
sortedList<T>::~sortedList(){
    delete_all();
};

template <typename T>
sortedList<T>& sortedList<T>::operator=(const sortedList<T> &to_copy){
    this->_length = 0;
    for(int i = 0; i < to_copy.length(); i++) {
        T elem = to_copy[i];
        this->push_back(elem);
    }

    return *this;
}

template <typename T>
const T &sortedList<T>::operator[](int i) const{
    Node* it = _first;
    if (i < _length) {
        if (i > _length / 2) {
            it = _last;
            for(int j = _length - 1; j > i; j--) {
                it = it->prev;
            }
        } else {
            for(int j = 0; j < i; j++) {
                it = it->next;
            }
        }
    }
    return it->value;
};

template <typename T>
void sortedList<T>::insert(const T &elem){
    Node* new_node = new Node(elem);
    if (_length == 0) {
        _first = new_node;
        _last = new_node;
    } else if (elem <= _first->value) {
        new_node->next = _first;
        _first->prev = new_node;
        _first = new_node;
    } else if (elem >= _last->value) {
        new_node->prev = _last;
        _last->next = new_node;
        _last = new_node;
    } else {
        Node* it = _first->next;
        while(elem > it->value) it = it->next;
        it->prev->next = new_node;
        new_node->next = it;
        new_node->prev = it->prev;
        it->prev = new_node;
    }
    _length++;
};

template <typename T>
void sortedList<T>::remove(T elem){
    Node* it = _first;
    while(it->value != elem) it = it->next;
    // Try to improve this remove

    it->prev->next = it->next;
    it->next->prev = it->prev;
    _length--;
}

template <typename T>
int sortedList<T>::length() const {
    return _length;
}

template <typename T>
void sortedList<T>::merge(const sortedList<T>& l){
    for(int i = 0; i < l._length; i++) {
        push_back(l[i]);
    }
};

template <typename T>
void sortedList<T>::print(ostream &os) {
    Node* it = _first;
    os << "[";
    while (it != nullptr) {
        if (it != _last) {
            os << it->value << ", ";
        } else {
            os << it->value;
        }
        it = it->next;
    }
    os << "]";
}

// AUXILIARS

template <typename T>
void sortedList<T>::delete_all() {
    while(_first != nullptr) {
        Node* f = _first;
        _first->prev = nullptr;
        _first = _first->next;
        delete f;
    }
    _length = 0;
}
