#include "skip_list.cpp"
#include<string>

string accepted = "accpeted";
string wrong    = "wrong anwser";
bool anwser     = true;

int testsTotal    = 0;
int testsAccepted = 0;

void print_judge(string text) {
    string res = anwser ? accepted : wrong;
    cout << text << ": " << res << endl;
    if (anwser) testsAccepted++;
    anwser = true;
    testsTotal++;
}

void test_constructor() {
    skipList<int> sl(0.5,5);
    if(sl.height() != 0) anwser = false;
    if(!sl.empty()) anwser = false;
    print_judge("Constructor");
}

void test_insert() {
    skipList<int> sl(0.25,5);

    sl.insert(4);
    sl.insert(6);
    sl.insert(1);
    sl.insert(3);
    sl.insert(15);

    cout << sl << endl;

    if(sl.empty()) anwser = false;
    if(!sl.contains(4)) anwser = false;
    if(!sl.contains(6)) anwser = false;
    if(!sl.contains(1)) anwser = false;
    if(!sl.contains(3)) anwser = false;
    if(!sl.contains(15)) anwser = false;

    print_judge("Insert & Contains");
}

int main() {
    test_constructor();
    test_insert();
    cout << "Accepted: " << testsAccepted << "/" << testsTotal << endl;
}