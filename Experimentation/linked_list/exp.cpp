#include"../../linked list/linked_list.cpp"
#include<iostream>
#include<fstream>
#include<chrono>
#include<string>
#include<vector>

using namespace std;

List<int> list;
vector<int> v;

void read_input() {
    int number;
    ifstream inputFile;
    string filePath = "../inputs/input_2";
    inputFile.open(filePath);
    while (inputFile) {
        inputFile >> number;
        list.push_back(number);
        v.push_back(number);
    }
    inputFile.close();
}

void writeData(long long d, int t) {
    ofstream outputFile;
    outputFile.open("runtime.csv",ios::app);
    outputFile << "\n" << to_string(t) << "," << to_string(d);
    outputFile.close();
}

int main() {
    int c = 19;
    int i = 0;
    read_input();

    while (c--) {
        int j = 10000 * (i+1);

        auto start = chrono::high_resolution_clock::now();

        int num = list[j];

        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        writeData(duration.count(), j);
        i++;
    }
}