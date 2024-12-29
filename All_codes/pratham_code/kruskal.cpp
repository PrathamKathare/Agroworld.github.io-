#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

int findParent(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = findParent(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);

    int parent[n], rank[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    vector<Edge> result;
    for (auto& e : edges) {
        int x = findParent(parent, e.u);
        int y = findParent(parent, e.v);

        if (x != y) {
            result.push_back(e);
            unionSets(parent, rank, x, y);
        }
    }

    cout << "Minimum spanning tree edges:\n";
    for (auto& e : result) {
        cout << e.u << " -- " << e.v << " == " << e.weight << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;
    vector<Edge> edges(m);

    cout << "Enter edges (u, v, weight):\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskal(n, edges);

    return 0;
}
