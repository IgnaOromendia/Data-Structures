#include<iostream>
#include<string>
#include"bst.cpp"

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
    bst<int> a;
    bool answer = a.size() == 0;
    print_judge("Empty constructor",answer);
}

void test_one_insert() {
    bst<int> a;
    a.insert(37);
    bool answer = a.size() == 1;
    print_judge("One insert",answer);
}

void test_some_inserts() {
    bst<int> a;
    a.insert(37);
    a.insert(58);
    a.insert(1527);
    a.insert(3);
    a.insert(999);
    bool answer = a.size() == 5;
    print_judge("Some inserts",answer);
}

void test_contains() {
    bool anwser = true;
    bst<int> a;

    for (int i = 0; i < 0;i++) {
        if (a.contains(i)) anwser = false;
    }

    a.insert(10);
    if (!a.contains(10)) anwser = false;

    a.insert(88);
    if (!a.contains(10)) anwser = false;
    if (!a.contains(88)) anwser = false;

    print_judge("Contains", anwser);
}

void test_insert_remove() {
    bool answer = true;
    bst<int> a;

    a.insert(153);
    a.remove(153);
    if (a.size() != 0) answer = false;

    a.insert(35);
    if (a.size() != 1 and !a.contains(35)) answer = false;

    print_judge("Insert & remove", answer);
}

void test_min() {
    bool answer = true;
    bst<int> a;
    a.insert(23);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    if(a.min() != 21) answer = false;
    print_judge("Min", answer);
}

void test_max() {
    bool answer = true;
    bst<int> a;
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

void test_next() {
    bool answer = true;
    bst<int> a;
    a.insert(5);
    a.insert(4);
    a.insert(20);
    a.insert(15);
    a.insert(12);
    a.insert(16);
    a.insert(24);
    a.insert(22);
    a.insert(25);
    if (a.next(20) != 22) answer = false;
    if (a.next(4) != 5) answer = false;
    if (a.next(15) != 16) answer = false;
    print_judge("Next number order",answer);
}

void test_remove_leaf() {
    bool answer = true;
    bst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    a.remove(152);
    if(a.size() != 3) answer = false;
    if(a.contains(152)) answer = false;
    print_judge("Remove one leaf",answer);
}

void test_remove_one_son() {
    bool answer = true;
    bst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    a.remove(58);
    if(a.size() != 3) answer = false;
    if(a.contains(58)) answer = false;
    print_judge("Remove with one son",answer);
}

void test_remove_both_sons() {
    bool answer = true;
    bst<int> a;
    a.insert(5);
    a.insert(4);
    a.insert(20);
    a.insert(15);
    a.insert(12);
    a.insert(16);
    a.insert(24);
    a.insert(22);
    a.insert(25);
    a.remove(20);
    if(a.size() != 8) answer = false;
    if(a.contains(20)) answer = false;
    print_judge("Remove with two sons",answer);
}

const int total = 1000;

int key(int i) {
	return total * ((i * i - 100 * i) % total) + i;
}

void test_stress() {
    bool answer = true;
    bst<int> a;

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
	    	a.remove(k);
	    	if (a.contains(k)) answer = false;
	    } else {
            if (a.contains(k)) answer = false;
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
    test_contains();
    test_insert_remove();
    test_min();
    test_max();
    test_next();
    test_remove_leaf();
    test_remove_one_son();
    test_remove_both_sons();
    test_stress();
    cout << "Total accepted: " << acceptedC << "/" << testCases << endl;
}