#include<random>
#include<iostream>
#ifndef _SKIP_LIST_H_
#define  _SKIP_LIST_H_

using namespace std;

template<typename T>
class skipList {
public:
    skipList(const double& p, const int& max_level);

    ~skipList();

    bool contains(const T& elem) const;

    void insert(const T& elem);

    void remove(const T& elem);

    int height() const;

    bool empty() const;

    void size() const;

    void print(ostream& os);

    friend ostream& operator<<(ostream& os, skipList<T>& sl) {
        sl.print(os);
        return os;
    }

private:
    struct Node {
        T value;
        int height;
        Node** next;

        Node(T val, int level): value(val) {
            height = level;
            next = new Node*[level+1];
            for(int i = 0; i <= level; i++) next[i] = nullptr;
        }

        ~Node() {
            delete[] next;
        } 
    };

    Node* _header;
    int _size;
    int _max_level;
    int _height;
    double _p;

    // A random number with uniform distribution between 0 and l
    double uniform_number();
};

#endif
