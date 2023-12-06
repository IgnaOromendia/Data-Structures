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
    bool anwser = a.size() == 0;
    print_judge("Empty constructor",anwser);
}

void test_one_insert() {
    bst<int> a;
    a.insert(37);
    bool anwser = a.size() == 1;
    print_judge("One insert",anwser);
}

void test_some_inserts() {
    bst<int> a;
    a.insert(37);
    a.insert(58);
    a.insert(1527);
    a.insert(3);
    a.insert(999);
    bool anwser = a.size() == 5;
    print_judge("Some inserts",anwser);
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
    bool anwser = true;
    bst<int> a;

    a.insert(153);
    a.remove(153);
    if (a.size() != 0) anwser = false;

    a.insert(35);
    if (a.size() != 1 and !a.contains(35)) anwser = false;

    print_judge("Insert & remove", anwser);
}

void test_min() {
    bool anwser = true;
    bst<int> a;
    a.insert(23);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    if(a.min() != 21) anwser = false;
    print_judge("Min", anwser);
}

void test_max() {
    bool anwser = true;
    bst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    if (!a.contains(1)) anwser = false;
    if (!a.contains(21)) anwser = false;
    if (!a.contains(58)) anwser = false;
    if (!a.contains(152)) anwser = false;
    if(a.max() != 152) anwser = false;
    print_judge("Max", anwser);
}

void test_next() {
    bool anwser = true;
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
    if (a.next(20) != 22) anwser = false;
    if (a.next(4) != 5) anwser = false;
    if (a.next(15) != 16) anwser = false;
    print_judge("Next number order",anwser);
}

void test_remove_leaf() {
    bool anwser = true;
    bst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    a.remove(152);
    if(a.size() != 3) anwser = false;
    if(a.contains(152)) anwser = false;
    print_judge("Remove one leaf",anwser);
}

void test_remove_one_son() {
    bool anwser = true;
    bst<int> a;
    a.insert(1);
    a.insert(21);
    a.insert(58);
    a.insert(152);
    a.remove(58);
    if(a.size() != 3) anwser = false;
    if(a.contains(58)) anwser = false;
    print_judge("Remove with one son",anwser);
}

void test_remove_both_sons() {
    bool anwser = true;
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
    if(a.size() != 8) anwser = false;
    if(a.contains(20)) anwser = false;
    print_judge("Remove with two sons",anwser);
}

const int total = 1000;

int key(int i) {
	return total * ((i * i - 100 * i) % total) + i;
}

void test_stress() {
    bool anwser = true;
    bst<int> a;

    // Insert
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (a.size() != i) anwser = false;
        if (a.contains(k)) anwser = false;
	    a.insert(k);
	    if (!a.contains(k)) anwser = false;
    }
    if (a.size() != total) anwser = false;

    // Insert again
    for (int i = 0; i < total; i++) {
	    int k = key(i);
        if (!a.contains(k)) anwser = false;
	    a.insert(k);
	    if (!a.contains(k)) anwser = false;
        if (a.size() != total) anwser = false;
    }

    // Remove number for even i
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (!a.contains(k)) anwser = false;
	    if (i % 2 == 0) {
	    	a.remove(k);
	    	if (a.contains(k)) anwser = false;
	    }
    }
    if (a.size() != total / 2) anwser = false;

    // Remove number for odd i
    for (int i = 0; i < total; i++) {
	    int k = key(i);
	    if (i % 2 == 1) {
            if (!a.contains(k)) anwser = false;
	    	a.remove(k);
	    	if (a.contains(k)) anwser = false;
	    } else {
            if (a.contains(k)) anwser = false;
        }
    }
    if (a.size() != 0) anwser = false;

    for(int i = 0; i < total; i++) {
        int k = key(i);
        if (a.contains(k)) anwser = false;
    }

    print_judge("Stress",anwser);
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