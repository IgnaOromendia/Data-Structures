#include "linked_list.cpp"
#include<string>
#include<iostream>

string accepted = "accpeted";
string wrong    = "wrong anwser";

void print_judge(string text, bool a) {
    string res = a ? accepted : wrong;
    cout << text << ": " << res << endl;
}

void test_empty_constructor() {
    List<int> l;
    bool answer = l.length() == 0;
    print_judge("Empty constructor",answer);
}

void test_push_front() {
    bool answer = true;
    List<int> l;
    l.push_front(3);
    if (l.length() != 1) answer = false;
    if (l[0] != 3) answer = false;
    print_judge("Push front",answer);
}

void test_push_back() {
    bool answer = true;
    List<int> l;
    l.push_front(17432);
    if (l.length() != 1) answer = false;
    if (l[0] != 17432) answer = false;
    print_judge("Push back",answer);
}

void test_some_push_front() {
    bool answer = true;
    List<int> l;
    l.push_front(3);
    l.push_front(7794);
    l.push_front(13);
    l.push_front(8432);
    if (l.length() != 4) answer = false;
    if (l[3] != 3) answer = false;
    if (l[2] != 7794) answer = false;
    if (l[1] != 13) answer = false;
    if (l[0] != 8432) answer = false;
    print_judge("Some push front",answer);
}

void test_some_push_back() {
    bool answer = true;
    List<int> l;
    l.push_back(3);
    l.push_back(7794);
    l.push_back(13);
    l.push_back(8432);
    if (l.length() != 4) answer = false;
    if (l[0] != 3) answer = false;
    if (l[1] != 7794) answer = false;
    if (l[2] != 13) answer = false;
    if (l[3] != 8432) answer = false;
    print_judge("Some push back",answer);
}

void test_some_push_front_and_back() {
    bool answer = true;
    List<int> l;
    l.push_back(3);
    l.push_front(7794);
    l.push_back(13);
    l.push_front(8432);
    if (l.length() != 4) answer = false;
    if (l[0] != 8432) answer = false;
    if (l[1] != 7794) answer = false;
    if (l[2] != 3) answer = false;
    if (l[3] != 13) answer = false;
    print_judge("Some push front and back",answer);
}

void test_remove_elements() {
    bool answer = true;
    List<int> l;
    l.push_back(3);
    l.push_back(7794);
    l.push_back(13);
    l.push_back(8432);

    l.remove_at(1);

    if (l.length() != 3) answer = false;
    if (l[0] != 3) answer = false;
    if (l[1] != 13) answer = false;
    if (l[2] != 8432) answer = false;

    l.remove_at(2);

    if (l.length() != 2) answer = false;
    if (l[0] != 3) answer = false;
    if (l[1] != 13) answer = false;

    l.remove_at(0);
    l.remove(13);
    
    if (l.length() != 0) answer = false;

    print_judge("Remove",answer);
}

void test_copy_contructor() {
    bool answer = true;
    List<int> l;
    l.push_back(3);
    l.push_back(7794);
    l.push_back(13);
    l.push_back(8432);

    List<int> l_c(l);

    if (l_c.length() != 4) answer = false;
    if (l_c[0] != 3) answer = false;
    if (l_c[1] != 7794) answer = false;
    if (l_c[2] != 13) answer = false;
    if (l_c[3] != 8432) answer = false;

    l.push_front(1);
    if (l_c[0] != 3) answer = false;

    print_judge("Copy constructor", answer);
}

int main() {
    test_empty_constructor();
    test_push_front();
    test_push_back();
    test_some_push_front();
    test_some_push_back();
    test_some_push_front_and_back();
    test_remove_elements();
    test_copy_contructor();
}