#include"fibonacci_heap.cpp"
#include<vector>
#include<string>
#include<iostream>

string accepted = "accpeted";
string wrong    = "wrong anwser";
bool anwser     = true;

void print_judge(string text) {
    string res = anwser ? accepted : wrong;
    cout << text << ": " << res << endl;
    anwser = true;
}

void test_constructor() {
    fibonacci_heap<int> f;
    if (!f.empty()) anwser = false;
    if (f.size() != 0) anwser = false;
    print_judge("Constructor");
}

void test_one_insert() {
    fibonacci_heap<int> f;

    f.insert(10,1);

    if (f.empty()) anwser = false;
    if (f.size() != 1) anwser = false;

    fibonacci_heap<int>::FH_handle handle = f.min();
    pair<int, double> data = *handle;

    if (data.first != 10) anwser = false;
    if (data.second != 1.0) anwser = false;
    print_judge("One insert");
}

void test_some_insert() {
    fibonacci_heap<int> f;

    f.insert(10,1);
    f.insert(23,21);
    f.insert(121,11);
    f.insert(2134,4);

    if (f.empty()) anwser = false;
    if (f.size() != 4) anwser = false;

    fibonacci_heap<int>::FH_handle handle = f.min();
    pair<int, double> data = *handle;

    if (data.first != 10) anwser = false;
    if (data.second != 1.0) anwser = false;
    print_judge("Some inserts");
}

void test_extract_min() {
    fibonacci_heap<int> f;
    vector<pair<int, double> > v;

    v.push_back(make_pair(10,1));
    v.push_back(make_pair(14, 2));
    v.push_back(make_pair(5, 3));
    v.push_back(make_pair(15, 4));
    v.push_back(make_pair(28, 5));

    f.insert(10,1);
    f.insert(5,3);
    f.insert(28,5);
    f.insert(15,4);
    f.insert(14,2);

    int i = 0;

    while (f.size() > 0) {
        fibonacci_heap<int>::FH_handle handle = f.min();
        pair<int, double> data = *handle;

        if (data.first != v[i].first) anwser = false;
        if (data.second != v[i].second) anwser = false;

        f.extract_min();

        i++;
    }

    print_judge("Extract min");
}

void test_extract_insert() {
    fibonacci_heap<int> f;
    fibonacci_heap<int>::FH_handle handle;
    pair<int, double> data1;
    pair<int, double> data2;

    for(int i = 0; i < 5; i++) {
        f.insert(i,i);
    }

    int size = f.size();
    for (int i = 0; i < size; i++) {
        handle = f.min();
        data1 = *handle;
        f.extract_min();
        handle = f.min();
        data2 = *handle;
        if (data2.second < data1.second) anwser = false;
    }

    for(int i = 5; i < 10; i++) {
        f.insert(i,i);
    }

    size = f.size();
    for (int i = 0; i < size; i++) {
        handle = f.min();
        data1 = *handle;
        f.extract_min();
        handle = f.min();
        data2 = *handle;
        if (data2.second < data1.second) anwser = false;
    }

    print_judge("Extract min insert");
}

void test_stress() {
    int total = 1000;
    bool anwser1 = true; // debugging
    fibonacci_heap<int> f;
    fibonacci_heap<int>::FH_handle handle;
    vector<fibonacci_heap<int>::FH_handle> handles(total+1);

    // Insert
    for (int i = 0; i <= total; i++) {
	    if (f.size() != i) anwser = false;
	    handle = f.insert(i,i);
        handles[i] = handle;
        if ((*handle).first != i or (*handle).second != i) anwser1 = false;
    }
    if (f.size() != total+1) anwser1 = false;

    f.extract_min();

    // Decrease key
    for (int i = 0; i < (total / 2); i++) {
        handle = handles[((total) / 2) + 1 + i];
        pair<int, double> old_data = *handle;
        f.decrease_key(handle, -1);
	    handle = f.min();
        pair<int, double> data = *handle;
        if (old_data.first != data.first) anwser1 = false;
        if (old_data.second < data.second) anwser1 = false;
        f.extract_min();
        handle = f.min();
        pair<int, double> new_data = *handle;
        if (data.first < new_data.first) anwser1 = false;
        if (data.second > new_data.second) anwser1 = false;
    }    

    // Extract min
    while(!f.empty()) {
        handle = f.min();
        pair<int, double> data = *handle;
        f.extract_min();
        handle = f.min();
        pair<int, double> new_data = *handle;
        if (data.second > new_data.second) anwser1 = false;
    }
    if (f.size() != 0) anwser1 = false;

    anwser = anwser1;
    print_judge("Stress");
}

void test_decrease_key() {
    fibonacci_heap<int> f;
    fibonacci_heap<int>::FH_handle handle1;
    fibonacci_heap<int>::FH_handle handle2;
    fibonacci_heap<int>::FH_handle handle3;

    f.insert(1,1);
    handle1 = f.insert(21,21);
    handle2 = f.insert(11,11);
    f.insert(4,4);
    handle3 = f.insert(7,7);
    f.insert(5,5);

    f.extract_min();

    f.decrease_key(handle1,2);

    handle1 = f.min();
    if ((*handle1).second != 2 or (*handle1).first != 21) anwser = false;

    f.extract_min();
    f.decrease_key(handle2,2);

    handle2 = f.min();
    if ((*handle2).second != 2 or (*handle2).first != 11) anwser = false;

    f.decrease_key(handle3,1); 

    handle3 = f.min();
    if ((*handle3).second != 1 or (*handle3).first != 7) anwser = false;

    print_judge("Decrease key simple");
}

int main() {
    test_constructor();
    test_one_insert();
    test_some_insert();
    test_extract_min();
    test_extract_insert();
    test_decrease_key();
    test_stress();
}