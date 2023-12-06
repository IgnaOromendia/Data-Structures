#include<vector>

using namespace std;

class unionFind {
public:
    unionFind(int n);

    void union_(int x, int y);

    int find(int x);

private:
    vector<int> parent;
    int nr_blocks;
};

unionFind::unionFind(int n): parent(vector<int>(n)) {
    for (int i = 0; i < n; i++) parent[i] = i;
    nr_blocks = n;
}

void unionFind::union_(int x, int y) {
    int rx = find(x); int ry = find(y);
    if (rx != ry) {
        parent[rx] = ry;
        nr_blocks--;
    }
}

int unionFind::find(int x) {
    while(parent[x] != x) x = parent[x];
    return x;
}
