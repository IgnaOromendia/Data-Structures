#include"trie.h"

template <typename T>
trie<T>::trie(): _root(new Node()), _size(0) {}

template <typename T>
trie<T>::trie(const trie<T> &to_copy) {
    *this = to_copy;
}

template <typename T>
trie<T>& trie<T>::operator=(const trie<T>& r) {
    destroy(_root);
    delete _root;
    _size = r.size();
    _root = new Node();
    if (r._root->childs > 0) {
        copy(r._root, _root);
    }
    return *this;
}

template <typename T>
trie<T>::~trie() {
    destroy(_root);
    delete _root;
}

template <typename T>
void trie<T>::insert(const pair<string, T> &item) {
    insert_aux(_root, item, 0);
    _size++;
}

template <typename T>
const bool trie<T>::contains(const string &key) const {
    Node* it = _root;
    for(int i = 0; i < key.size(); i++) {
        if(it->next_letter[int(key[i])] == nullptr) return false;
        it = it->next_letter[int(key[i])];
    }
    return it->value != nullptr;
}

template <typename T>
T &trie<T>::operator[](const string &key) const {
    Node* it = _root;
    for(int i = 0; i < key.size(); i++) {
        it = it->next_letter[int(key[i])];
    }
    return *(it->value);
}

template <typename T>
void trie<T>::remove(const string &key) {
    remove_aux(_root, key, 0);
    _size--;
}

template <typename T>
const int trie<T>::size() const {
    return _size;
}

template <typename T>
const bool trie<T>::empty() const {
    return _size == 0;
}

template <typename T>
void trie<T>::destroy(Node *n) {
    if (n != nullptr) {
        if(n->value != nullptr) {delete n->value; n->value = nullptr;}
        for (int i = 0; i < n->next_letter.size(); i++) {
            destroy(n->next_letter[i]);
            delete n->next_letter[i];
            n->next_letter[i] = nullptr;
        }
    }
}

template <typename T>
void trie<T>::insert_aux(Node *n, const pair<string, T> &item, int i) {
    if (i < item.first.size()) {
        if (n->next_letter[item.first[i]] == nullptr) {
            n->next_letter[item.first[i]] = new Node();
            n->childs++;
        }
        insert_aux(n->next_letter[item.first[i]], item, i+1);
    } else {
        T* value = new T(item.second); 
        if (n->value != nullptr) delete n->value;
        n->value = value;
    }
}

template <typename T>
void trie<T>::remove_aux(Node*& n, const string &key, int i) {
    if (i == key.size()) {
        delete n->value;
        n->value = nullptr;
        if (n->childs == 0) {
            delete n;
            n = nullptr;
        }
    } else {
        remove_aux(n->next_letter[key[i]], key, i+1);
        if (n->next_letter[key[i]] == nullptr) n->childs--;
        if (n->childs == 0 and n->value == nullptr and n != _root) {
            delete n;
            n = nullptr;
        }
    }
}

template <typename T>
void trie<T>::copy(Node *n, Node *r) {
    for(int i = 0; i < n->next_letter.size(); i++) {
        if (n->next_letter[i] != nullptr) {
            if (n->next_letter[i]->value != nullptr) {
                T* value = new T(*(n->next_letter[i]->value));
                r->next_letter[i] = new Node(value);
            } else {
                r->next_letter[i] = new Node();
            }
            copy(n->next_letter[i], r->next_letter[i]);
        }
    }
}
