#include<iostream>
#include<string>
#include"rbst.cpp"

using namespace std;

string accepted = "accpeted";
string wrong    = "wrong anwser";
int testCases   = 0;
int acceptedC   = 0;

void print_judge(string text, bool a) {
    string res = a ? accepted : wrong;
    testCases++;
    if (a) acceptedC++; 
    cout << text << ": " << res << endl;
}

void test_empty_constructor() {
    rbst<int> r;
    print_judge("Constructor",r.size() == 0);
}

void test_one_insert() {
    bool answer = true;
    rbst<int> r;
    r.insert(10);
    if (r.size() != 1) answer = false;
    if (!r.contains(10)) answer = false;
    print_judge("One insert",answer);
}

void test_some_inserts() {
    bool answer = true;
    rbst<int> r;

    for (int i = 0; i < 10; i++) {
        if (r.contains(i)) answer = false;
    }

    r.insert(14);
    r.insert(5);
    r.insert(10);
    r.insert(15);
    r.insert(18);
    r.insert(28);
    r.insert(25);
    r.insert(33);
    r.insert(30);

    if (!r.contains(14)) answer = false;
    if (!r.contains(5)) answer = false;
    if (!r.contains(10)) answer = false;
    if (!r.contains(15)) answer = false;
    if (!r.contains(18)) answer = false;
    if (!r.contains(28)) answer = false;
    if (!r.contains(25)) answer = false;
    if (!r.contains(33)) answer = false;
    if (!r.contains(30)) answer = false;
    
    print_judge("Some inserts and contains", answer);
}

int main() {
    test_empty_constructor();
    test_one_insert();
    test_some_inserts();
    cout << "Total accepted: " << acceptedC << "/" << testCases << endl;
    return 0;
}