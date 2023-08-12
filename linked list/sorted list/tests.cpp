#include"linked_list.cpp"
#include<random>
#include<string>
#include<iostream>

int uniform_number(const int l) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, l);
    return distribution(generator);
}

int main() {
    bool anwser = true;
    list<int> l;

    for (int i = 0; i < 100; i++) {
        int number = uniform_number(100);
        l.insert(number);
    }

    for (int i = 0; i < 10; i++){
        int index = uniform_number(l.length());
        l.remove(l[index]);
    }

    for (int i = 1; i < l.length(); i++) {
        if (l[i - 1] > l[i]) anwser = false;
    }

    string ans = anwser ? "accepted" : "wrong anwnser";
    cout << ans << endl;
}