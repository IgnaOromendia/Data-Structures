#include"../../linked list/linked_list.cpp"
#include<iostream>
#include<fstream>
#include<chrono>
#include<string>
#include<vector>
#include<list>
#include<math.h>

using namespace std;

vector<int> test;

void read_input(string filepath, List<int>& l) {
    int number;
    ifstream inputFile;
    inputFile.open(filepath);
    while (inputFile) {
        inputFile >> number;
        l.push_back(number);
    }
    inputFile.close();
}

void writeData(long long d, int t, string filename) {
    ofstream outputFile;
    outputFile.open(filename,ios::app);
    outputFile << "\n" << to_string(t) << "," << to_string(d);
    outputFile.close();
}

void sample_insertion() {
    for(int i = 20; i < 27; i++) {  
        int k = 0;
        int j = pow(2,i);
        vector<int> v;
        List<int> l1;
        List<int> l2;
        list<int> lc;

        cout << "Testing with size: 2^" << i << endl;

        cout << "My list" << endl;

        auto start = chrono::high_resolution_clock::now();
        while(k <= j) {
            l1.push_front(k);
            k++;
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        writeData(duration.count(), j, "samples/linked_push_front.csv");

        k = 0;
        start = chrono::high_resolution_clock::now();
        while(k <= j) {
            l2.push_back(k);
            k++;
        }
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        writeData(duration.count(), j, "samples/linked_push_back.csv");

        cout << "Vector" << endl;
        k = 0;
        start = chrono::high_resolution_clock::now();
        while(k <= j) {
            v.push_back(k);
            k++;
        }
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        writeData(duration.count(), j, "../samples_cpp/vector_push_back.csv");

        cout << "C++ list" << endl;
        k = 0;
        start = chrono::high_resolution_clock::now();
        while(k <= j) {
            lc.push_back(k);
            k++;
        }
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        writeData(duration.count(), j, "../samples_cpp/list_push_back.csv");

        k = 0;
        start = chrono::high_resolution_clock::now();
        while(k <= j) {
            lc.push_front(k);
            k++;
        }
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        writeData(duration.count(), j, "../samples_cpp/list_push_front.csv");
    }
}

int main() {
    
}