#include<vector>

using namespace std;

class unionFindRank {
public:
    unionFindRank(int n);

    void union_(int x, int y);

    int find(int x);

private:
    vector<int> parent;
    int nr_blocks;
};

// In stead of saving the father when we are at the root, which will be p[i] = i,
// we store the rank with a negative so it can be differentiated from the others

unionFindRank::unionFindRank(int n): parent(vector<int>(n)) {
    for (int i = 0; i < n; i++) parent[i] = -1;
    nr_blocks = n;
}

void unionFindRank::union_(int x, int y) {
    int rx = find(x); int ry = find(y);
    if (rx != ry) {
        if (parent[rx] >= parent[ry]) {
            parent[rx] = ry;
            parent[ry] = min(parent[rx] - 1, parent[ry]);
        } else {
            parent[ry] = rx;
            parent[rx] = min(parent[rx], parent[ry] - 1);
        }
        nr_blocks--;
    }
}

int unionFindRank::find(int x) {
    while(parent[x] > 0) x = parent[x];
    return x;
}
