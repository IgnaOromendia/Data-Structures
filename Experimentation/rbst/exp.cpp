#include"../../binary search tree/bst.cpp"
#include"../../randomized bst/rbst.cpp"
#include<chrono>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

vector<vector<pair<int,long long> > > times_bst;
vector<vector<pair<int,long long> > > times_rbst;

void writeData(double d, int t, string filename) {
    ofstream outputFile;
    outputFile.open(filename,ios::app);
    outputFile << "\n" << to_string(t) << "," << to_string(d);
    outputFile.close();
}

int key(int i, int total) {
    return total * ((i * i - 100 * i) % total) + i;
}

void write_mean_time(vector<vector<pair<int,long long> > > sample, string filename) {
    vector<long long> sum_time(sample[0].size()); 

    for (int i = 0; i < sample.size(); i++) {
        for (int j = 0; j < sample[0].size(); j++) {
            sum_time[j] += sample[i][j].second;
        }
    }

    for (int i = 0; i < sum_time.size(); i++) {
        double result = static_cast<double>(sum_time[i]) / sample.size();
        writeData(result, sample[0][i].first, filename);
    }
}

void sample_insertion_random() {
    cout << "Insertion random" << endl;
    for (int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_bst;
        vector<pair<int,long long> > sample_rbst;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for (int i = 20; i <= 25; i++) {
            int n = pow(2,i);
            int j = 0;
            bst<int> b;
            rbst<int> r;
            vector<int> rdata;

            for(int k = 0; k < n; k++) rdata.push_back(key(i,n));

            cout << "Test size: 2^" << i << endl;

            auto start = chrono::high_resolution_clock::now();
            while (j < n) {
                b.insert(rdata[j]);
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_bst.push_back(make_pair(i+1,duration.count()));

            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                r.insert(rdata[j]);
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_rbst.push_back(make_pair(i+1,duration.count())); 
        }
        times_bst.push_back(sample_bst);
        times_rbst.push_back(sample_rbst);
    }
    write_mean_time(times_bst, "samples/bst_insertion_random.csv");
    write_mean_time(times_rbst, "samples/rbst_insertion_random.csv");
}

void sample_insertion_sorted_and_max() {
    cout << "Insertion sorted" << endl;
    vector<vector<pair<int,long long> > > times_max_bst;
    vector<vector<pair<int,long long> > > times_max_rbst;
    for (int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_bst;
        vector<pair<int,long long> > sample_rbst;
        vector<pair<int,long long> > sample_max_bst;
        vector<pair<int,long long> > sample_max_rbst;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for (int i = 0; i < 10; i++) {
            int n = 1000 + (1000 * i);
            int j = 0;
            bst<int> b;
            rbst<int> r;

            cout << "Test size: " << n << endl;

            auto start = chrono::high_resolution_clock::now();
            while (j < n) {
                b.insert(j);
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_bst.push_back(make_pair(n,duration.count()));

            start = chrono::high_resolution_clock::now();
            int max1 = b.max();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_max_bst.push_back(make_pair(n,duration.count())); 

            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                r.insert(j);
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_rbst.push_back(make_pair(n,duration.count())); 

            start = chrono::high_resolution_clock::now();
            int max2 = r.max();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_max_rbst.push_back(make_pair(n,duration.count())); 
        }
        times_bst.push_back(sample_bst);
        times_rbst.push_back(sample_rbst);
        
        times_max_bst.push_back(sample_max_bst);
        times_max_rbst.push_back(sample_max_rbst);
    }
    write_mean_time(times_max_bst, "samples/bst_max_sorted.csv");
    write_mean_time(times_max_rbst, "samples/rbst_max_sorted.csv");
    write_mean_time(times_bst, "samples/bst_insertion_sorted.csv");
    write_mean_time(times_rbst, "samples/rbst_insertion_sorted.csv");
}


int main() {
    sample_insertion_sorted_and_max();
}