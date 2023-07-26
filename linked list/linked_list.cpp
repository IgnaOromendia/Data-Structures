#include "linked_list.h"

template <typename T>
List<T>::Node::Node(const T& elem): value(elem), next(nullptr), prev(nullptr) {};

template <typename T>
List<T>::List(): _first(nullptr), _last(nullptr), _length(0) {};

template <typename T>
List<T>::List(const List<T> &l){
    *this = l;
};

template <typename T>
List<T>::~List(){
    delete_all();
};

template <typename T>
List<T>& List<T>::operator=(const List<T> &to_copy){
    this->_length = 0;
    for(int i = 0; i < to_copy.length(); i++) {
        T elem = to_copy[i];
        this->push_back(elem);
    }

    return *this;
}

template <typename T>
const T &List<T>::operator[](int i) const{
    Node* it = _first;
    if (i < _length) {
        for(int j = 0; j < i; j++) {
            it = it->next;
        }
    }
    return it->value;
};

template <typename T>
void List<T>::push_front(const T& elem){
    Node* new_node = new Node(elem);
    new_node->next = _first;
    if(_length > 0) {
        _first->prev = new_node;
    } else {
        _last = new_node;
    }
    _first = new_node;
    _length++;
}

template <typename T>
void List<T>::push_back(const T &elem){
    Node* new_node = new Node(elem);
    if (_length == 1) {
        _last = new_node;
        _last->prev = _first;
        _first->next = _last;
    } else if(_length > 1) {
        _last->next = new_node;
        new_node->prev = _last;
        _last = new_node;
    } else {
        _first = new_node;
        _last = new_node;
    }
    _length++;
};

template <typename T>
void List<T>::remove_at(int i){
    Node* it = _first;
    if (i < _length) {
        for(int j = 0; j < i; j++) {
            it = it->next;
        }

        if(it == _first) {
            if (_length == 1) {
                _first = nullptr;
                _last = nullptr;
            } else {
                _first = it->next;
            }
        } else if (it == _last) {
            _last = it->prev;
            it->prev->next = nullptr;
        } else {
            it->prev->next = it->next;
            it->next->prev = it->prev;
        }

        delete it;
        _length--;
    }
}

template <typename T>
void List<T>::remove(T elem){
    Node* it = _first;
    for (int i = 0; i < _length; i++) {
        if(it->value != elem) continue;
        this->remove_at(i);
    }
}

template <typename T>
int List<T>::length() const {
    return _length;
};

template <typename T>
void List<T>::print(ostream &os) {
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
void List<T>::delete_all() {
    while(_first != nullptr) {
        Node* f = _first;
        _first->prev = nullptr;
        _first = _first->next;
        delete f;
    }
    _length = 0;
}
