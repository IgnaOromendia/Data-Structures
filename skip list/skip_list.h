#include"../linked list/sorted list/sortedList.cpp"
#include<random>
#ifndef _SKIP_LIST_H_
#define  _SKIP_LIST_H_

using namespace std;

template<typename T>
class skipList {
public:
    skipList(const float& p, const int& max_level);

    ~skipList();

    bool contains(const T& elem) const;

    void insert(const T& elem);

    void remove(const T& elem);

    int height() const;

    bool empty() const;

    void size() const;
private:
    struct Node {
        T value;
        Node** next;

        Node(T val, int level): value(val) {
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
    float _p;

    // A random number with uniform distribution between 0 and l
    double uniform_number();
};

#endif
