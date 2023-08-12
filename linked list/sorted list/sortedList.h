#ifndef _list_h
#define _list_h

#include <ostream>

using namespace std;

template<typename T>
class sortedList {
public:

    sortedList();

    sortedList(const sortedList<T>& l);

    ~sortedList();

    sortedList<T>& operator=(const sortedList<T>& to_copy);

    const T& operator[](int i) const;

    void insert(const T& elem);

    void remove(T elem);

    int length() const;

    void merge(const sortedList<T>& l);

    void print(ostream& os);

    friend ostream& operator<<(ostream& os, sortedList<T>& l) {
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