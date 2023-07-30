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
    
    print_judge("Some inserts", answer);
}

void test_one_remove() {
    bool answer = true;
    rbst<int> r;
    r.insert(10);
    r.remove(10);
    if (r.size() != 0) answer = false;
    if (r.contains(10)) answer = false;
    print_judge("One remove",answer);
}

void test_root() {
    bool answer = true;
    rbst<int> r;

    r.insert(14);
    r.insert(5);
    r.insert(10);
    r.insert(15);
    r.insert(18);
    r.insert(28);
    r.insert(25);
    r.insert(33);
    r.insert(30);

    while (r.size() > 0) {
        int root = r.root();
        r.remove(root);
    }

    if (r.size() != 0) answer = false;
    if (r.contains(14)) answer = false;
    if (r.contains(5)) answer = false;
    if (r.contains(10)) answer = false;
    if (r.contains(15)) answer = false;
    if (r.contains(18)) answer = false;
    if (r.contains(28)) answer = false;
    if (r.contains(25)) answer = false;
    if (r.contains(33)) answer = false;
    if (r.contains(30)) answer = false;

    print_judge("Root", answer);
}

void test_some_removes() {
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

    r.remove(28);
    r.remove(5);
    r.remove(15);

    if (r.size() != 6) answer = false;
    if (!r.contains(14)) answer = false;
    if (r.contains(5)) answer = false;
    if (!r.contains(10)) answer = false;
    if (r.contains(15)) answer = false;
    if (!r.contains(18)) answer = false;
    if (r.contains(28)) answer = false;
    if (!r.contains(25)) answer = false;
    if (!r.contains(33)) answer = false;
    if (!r.contains(30)) answer = false;

    r.remove(14);
    r.remove(10);
    r.remove(18);
    r.remove(25);
    r.remove(33);
    r.remove(30);

    if (r.size() != 0) answer = false;
    if (r.contains(14)) answer = false;
    if (r.contains(5)) answer = false;
    if (r.contains(10)) answer = false;
    if (r.contains(15)) answer = false;
    if (r.contains(18)) answer = false;
    if (r.contains(28)) answer = false;
    if (r.contains(25)) answer = false;
    if (r.contains(33)) answer = false;
    if (r.contains(30)) answer = false;
    
    print_judge("Some removes", answer);
}

void test_min() {
    bool answer = true;
    rbst<int> a;
    a.insert(23);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    if(a.min() != 21) answer = false;
    print_judge("Min", answer);
}

void test_max() {
    bool answer = true;
    rbst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    if (!a.contains(1)) answer = false;
    if (!a.contains(21)) answer = false;
    if (!a.contains(58)) answer = false;
    if (!a.contains(152)) answer = false;
    if(a.max() != 152) answer = false;
    print_judge("Max", answer);
}

const int total = 1000;

int key(int i) {
	return total * ((i * i - 100 * i) % total) + i;
}

void test_stress() {
    bool answer = true;
    rbst<int> a;

    // Insert
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (a.size() != i) answer = false;
        if (a.contains(k)) answer = false;
	    a.insert(k);
	    if (!a.contains(k)) answer = false;
    }
    if (a.size() != total) answer = false;

    // Insert again
    for (int i = 0; i < total; i++) {
	    int k = key(i);
        if (!a.contains(k)) answer = false;
	    a.insert(k);
	    if (!a.contains(k)) answer = false;
        if (a.size() != total) answer = false;
    }

    // Remove number for even i
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (!a.contains(k)) answer = false;
	    if (i % 2 == 0) {
	    	a.remove(k);
	    	if (a.contains(k)) answer = false;
	    }
    }
    if (a.size() != total / 2) answer = false;

    // Remove number for odd i
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (i % 2 == 1) {
            if (!a.contains(k)) answer = false;
            if (!answer) {
                int b = 0;
            }
	    	a.remove(k);
	    	if (a.contains(k)) answer = false;
            if (!answer) {
                int b = 0;
            }
	    } else {
            if (a.contains(k)) answer = false;
            if (!answer) {
                int b = 0;
            }
        }
    }
    if (a.size() != 0) answer = false;

    for(int i = 0; i < total; i++) {
        int k = key(i);
        if (a.contains(k)) answer = false;
    }

    print_judge("Stress",answer);
}


int main() {
    test_empty_constructor();
    test_one_insert();
    test_some_inserts();
    test_one_remove();
    test_root();
    test_some_removes();
    test_min();
    test_max();
    test_stress();
    cout << "Total accepted: " << acceptedC << "/" << testCases << endl;
    return 0;
}