#include"../../fibonacci heap/fibonacci_heap.cpp"
#include<queue>
#include<chrono>
#include<iostream>
#include<fstream>
#include<string>
#include<list>

vector<vector<pair<int,long long> > > times_fibo;
vector<vector<pair<int,long long> > > times_pqueue;

void writeData(double d, int t, string filename) {
    ofstream outputFile;
    outputFile.open(filename,ios::app);
    outputFile << "\n" << to_string(t) << "," << to_string(d);
    outputFile.close();
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

void sample_insertion() {
    cout << "Insertion" << endl;
    for(int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_1;
        vector<pair<int,long long> > sample_2;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for(int i = 0; i < 10; i++) {
            int j = 0;
            int n = 200000 + (200000 * i);
            fibonacci_heap<int> f;
            priority_queue<int> pq;

            cout << "Test size: " << n << endl;

            auto start = chrono::high_resolution_clock::now();
            while(j < n) {
                f.insert(j,j);
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_1.push_back(make_pair(n,duration.count())); 

            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                pq.push(j);
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_2.push_back(make_pair(n,duration.count())); 
        }
        times_fibo.push_back(sample_1);
        times_pqueue.push_back(sample_2);
    }
    write_mean_time(times_fibo, "samples/fibo_insertion.csv");
    write_mean_time(times_pqueue, "../samples_cpp/pqueue_insertion.csv");
}

void sample_extract_min() {
    cout << "Extract min" << endl;
    for(int q = 0; q < 5; q++) {
        vector<pair<int,long long> > sample_1;
        vector<pair<int,long long> > sample_2;

        cout << "--------------- Test " << q+1 << "---------------" << endl;

        for(int i = 0; i < 10; i++) {
            int j = 0;
            int n = 200000 + (200000 * i);
            fibonacci_heap<int> f;
            priority_queue<int> pq;

            cout << "Test size: " << n << endl;

            while(j < n) {
                f.insert(j,j);
                j++;
            }

            j = 0;
            auto start = chrono::high_resolution_clock::now();
            while(j < n) {
                f.extract_min();
                j++;
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_1.push_back(make_pair(n,duration.count())); 

            j = 0;
            while (j < n) {
                pq.push(j);
                j++;
            }
            j = 0;
            start = chrono::high_resolution_clock::now();
            while (j < n) {
                pq.pop();
                j++;
            }
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            sample_2.push_back(make_pair(n,duration.count())); 
        }
        times_fibo.push_back(sample_1);
        times_pqueue.push_back(sample_2);
    }
    write_mean_time(times_fibo, "samples/fibo_min.csv");
    write_mean_time(times_pqueue, "../samples_cpp/pqueue_min.csv");
}

// Dijkstra
typedef int vertex; 
struct edge {
    vertex target;
    double weight; 
};
const vertex NULL_VERTEX = -1;
typedef vector<list<edge> > weighted_graph;

void Dijkstra(const weighted_graph& G, vertex s, vector <double >& D, vector <vertex >& path) {
    vector<fibonacci_heap<int>::FH_handle> FH_handles(G.size()); 
    fibonacci_heap<int> cand;

    for (vertex u = 0; u < G.size(); ++u) { 
        D[u] = INFINITY; path[u] = NULL_VERTEX; 
        FH_handles[u] = cand.insert(u, INFINITY);
    }

    cand.decrease_key(FH_handles[s], 0); 
    D[s] = 0; path[s] = s;

    while (not cand.empty()) {
        fibonacci_heap<int>::FH_handle hu = cand.min(); 
        pair<int, double> data = *hu;
        vertex u = data.first;
        D[u] = data.second; 

        for (edge e : G[u]) {
            vertex v = e.target;
            double weight_u_v = e.weight; 
            if (D[u] + weight_u_v < D[v]) {
                D[v] = D[u] + weight_u_v; 
                path[v] = u;
                cand.decrease_key(FH_handles[v], D[v]); 
            }
        } 
    }
}

void sample_dijkstra() {

}

int main() {
    
}