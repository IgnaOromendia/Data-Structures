#ifndef _list_h
#define _list_h

#include <ostream>

using namespace std;

template<typename T>
class List {
public:

    List();

    List(const List<T>& l);

    ~List();

    List<T>& operator=(const List<T>& to_copy);

    const T& operator[](int i) const;

    void push_front(const T& elem);

    void push_back(const T& elem);

    void remove_at(int i);

    void remove(T elem);

    int length() const;

    void print(ostream& os);

    friend ostream& operator<<(ostream& os, List<T>& l) {
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