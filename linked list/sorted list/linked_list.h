#ifndef _list_h
#define _list_h

#include <ostream>

using namespace std;

template<typename T>
class list {
public:

    list();

    list(const list<T>& l);

    ~list();

    list<T>& operator=(const list<T>& to_copy);

    const T& operator[](int i) const;

    void insert(const T& elem);

    void remove(T elem);

    int length() const;

    void merge(const list<T>& l);

    void print(ostream& os);

    friend ostream& operator<<(ostream& os, list<T>& l) {
        l.print(os);
        return os;
    }

private:

    struct Node {
        Node(const T& elem);
        T value;
        Node* next;
        Node* prev;
    };

    Node* _first;
    Node* _last;
    int _length;

    void delete_all();
};

#endif