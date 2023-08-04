#ifndef _TRIE_H_
#define _TRIE_H_

#include<string>
#include<vector>

using namespace std;

template<typename T>
class trie {
public:

    trie();

    trie(const trie<T>& to_copy);

    trie<T>& operator=(const trie<T>& r);

    ~trie();

    void insert(const pair<string, T>& item);

    const bool contains(const string& key) const;

    T& operator[](const string& key) const;

    void remove(const string& key);

    const int size() const;

    const bool empty() const;
private:

    struct Node {
        vector<Node*> next_letter;
        int childs;
        T* value;
        Node(): next_letter(256, nullptr), value(nullptr), childs(0) {}
        Node(T* val): next_letter(256, nullptr), value(val), childs(0) {}
    };

    Node* _root;
    int _size;

    // Recursive destructor
    void destroy(Node* n);

    // Recursive insertion
    void insert_aux(Node* n, const pair<string, T>& item, int i);

    // Recursive remove
    void remove_aux(Node*& n, const string &key, int i);

    // Recursive copy
    void copy(Node* n, Node* r);
};

#endif
