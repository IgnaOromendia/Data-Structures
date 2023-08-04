#include"trie.cpp"

#include<iostream>

string accepted = "accpeted";
string wrong    = "wrong anwser";
bool anwser     = true;
int total       = 1000;
int testCases   = 0;
int acceptedC   = 0;

void print_judge(string text) {
    string res = anwser ? accepted : wrong;
    cout << text << ": " << res << endl;
    testCases++;
    if (anwser) acceptedC++; 
    anwser = true;
}

void test_constructor() {
    trie<int> t;
    if (not t.empty()) anwser = false;
    print_judge("Constructor");
}

void test_insert() {
    trie<int> t;
    t.insert(make_pair("hola", 1));
    t.insert(make_pair("chau", 2));
    t.insert(make_pair("adios", 3));
    t.insert(make_pair("c",  4));
    t.insert(make_pair("casa",  5));
    t.insert(make_pair("casona",  6));

    if (t.size() != 6) anwser = false;
    if (not t.contains("hola")) anwser = false;
    if (not t.contains("chau")) anwser = false;
    if (not t.contains("adios")) anwser = false;
    if (not t.contains("c")) anwser = false;
    if (not t.contains("casa")) anwser = false;
    if (not t.contains("casona")) anwser = false;

    if (t["hola"] != 1) anwser = false;
    if (t["chau"] != 2) anwser = false;
    if (t["adios"] != 3) anwser = false;
    if (t["c"] != 4) anwser = false;
    if (t["casa"] != 5) anwser = false;
    if (t["casona"] != 6) anwser = false;

    print_judge("Insert");
}

void test_update() {
    trie<int> t;
    t.insert(make_pair("c",  1));
    t.insert(make_pair("casa",  2));
    t.insert(make_pair("casona",  3));

    if (t["c"] != 1) anwser = false;
    if (t["casa"] != 2) anwser = false;
    if (t["casona"] != 3) anwser = false;

    t.insert(make_pair("c",  12));
    t.insert(make_pair("casa",  23));
    t.insert(make_pair("casona",  34));

    if (t["c"] != 12) anwser = false;
    if (t["casa"] != 23) anwser = false;
    if (t["casona"] != 34) anwser = false;

    print_judge("Update");
}

void test_trieOftries() {
    trie<int> t1;
    trie<int> t2;
    trie<trie<int> > superT;

    t1.insert(make_pair("hola", 1));
    t1.insert(make_pair("chau", 2));
    t1.insert(make_pair("adios", 3));

    t2.insert(make_pair("c",  4));
    t2.insert(make_pair("casa",  5));
    t2.insert(make_pair("casona",  6));

    superT.insert(make_pair("ft",t1));
    superT.insert(make_pair("st",t2));

    if (superT["ft"]["hola"] != 1) anwser = false;
    if (superT["ft"]["chau"] != 2) anwser = false;
    if (superT["ft"]["adios"] != 3) anwser = false;

    if (superT["st"]["c"] != 4) anwser = false;
    if (superT["st"]["casa"] != 5) anwser = false;
    if (superT["st"]["casona"] != 6) anwser = false;

    print_judge("Trie of tries");
}

void test_remove() {
    trie<int> t;
    t.insert(make_pair("hola", 1));
    t.insert(make_pair("chau", 2));
    t.insert(make_pair("adios", 3));
    t.insert(make_pair("c",  4));
    t.insert(make_pair("casa",  5));
    t.insert(make_pair("casona",  6));

    t.remove("hola");
    t.remove("chau");
    t.remove("adios");
    t.remove("casona");
    t.remove("casa");
    t.remove("c");
    

    if (t.size() != 0) anwser = false;
    if (t.contains("hola")) anwser = false;
    if (t.contains("chau")) anwser = false;
    if (t.contains("adios")) anwser = false;
    if (t.contains("c")) anwser = false;
    if (t.contains("casa")) anwser = false;
    if (t.contains("casona")) anwser = false;

    print_judge("Remove");
}

int main() {
    test_constructor();
    test_insert();
    test_update();
    test_remove();
    test_trieOftries();
    cout << "Total accepted: " << acceptedC << "/" << testCases << endl;
}