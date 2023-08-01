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

        for (int i = 0; i < 10; i++) {
            int n = 10000 + (2500 * i);
            int j = 0;
            bst<int> b;
            rbst<int> r;
            vector<int> rdata;

            cout << "Test size: " << n << endl;

            for(int k = 0; k < n; k++) rdata.push_back(key(k,n));

            auto start = chrono::high_resolution_clock::now();
            while (j < n) {
                b.insert(rdata[j]);
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_bst.push_back(make_pair(n,duration.count()));

            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                r.insert(rdata[j]);
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_rbst.push_back(make_pair(n,duration.count())); 
        }
        times_bst.push_back(sample_bst);
        times_rbst.push_back(sample_rbst);
    }
    write_mean_time(times_bst, "samples/bst_insertion_random.csv");
    write_mean_time(times_rbst, "samples/rbst_insertion_random.csv");
}

void sample_insertion_sorted() {
    cout << "Insertion sorted" << endl;
    for (int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_bst;
        vector<pair<int,long long> > sample_rbst;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for (int i = 0; i < 10; i++) {
            int n = 10000 + (2500 * i);
            int j = 0;
            bst<int> b;
            rbst<int> r;

            cout << "Test size: " << n << endl;

            cout << "Testing BST" << endl;

            auto start = chrono::high_resolution_clock::now();
            while (j < n) {
                b.insert(j);
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_bst.push_back(make_pair(n,duration.count()));

            cout << "Testing RBST" << endl;

            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                r.insert(j);
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_rbst.push_back(make_pair(n,duration.count())); 
        }
        times_bst.push_back(sample_bst);
        times_rbst.push_back(sample_rbst);
    }
    write_mean_time(times_bst, "samples/bst_insertion_sorted.csv");
    write_mean_time(times_rbst, "samples/rbst_insertion_sorted.csv");
}

void sample_max_random() {
    cout << "Max random" << endl;
    for (int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_bst;
        vector<pair<int,long long> > sample_rbst;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for (int i = 0; i < 10; i++) {
            int n = 30000 + (5000 * i);
            int j = 0;
            bst<int> b;
            rbst<int> r;
            vector<int> rdata;
            random_device rd;
            mt19937 generator(rd());
            uniform_int_distribution<int> distribution(0, n);

            for(int k = 0; k < n; k++) {
                int rand = distribution(generator);
                rdata.push_back(rand);
            }

            cout << "Test size: " << n << endl;

            while (j < n) {
                b.insert(rdata[j]);
                r.insert(rdata[j]);
                j++;
            }

            auto start = chrono::high_resolution_clock::now();
            int max1 = b.max();
            auto stop = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            sample_bst.push_back(make_pair(n,duration1.count()));

            start = chrono::high_resolution_clock::now();
            int max2 = r.max();
            stop = chrono::high_resolution_clock::now();
            duration1 = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            sample_rbst.push_back(make_pair(n,duration1.count())); 
        }
        times_bst.push_back(sample_bst);
        times_rbst.push_back(sample_rbst);
    }
    write_mean_time(times_bst, "samples/bst_max_random.csv");
    write_mean_time(times_rbst, "samples/rbst_max_random.csv");
}

int main() {
    // sample_insertion_random();
    // sample_insertion_sorted();
    sample_max_random();
}