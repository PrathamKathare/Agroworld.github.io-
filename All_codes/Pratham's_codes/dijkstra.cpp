#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minDistance(vector<int>& dist, vector<bool>& sptSet, int n) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < n; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(vector<vector<int>>& graph, int src, int n) {
    vector<int> dist(n, INT_MAX);
    vector<bool> sptSet(n, false);
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Shortest paths from source " << src << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));

    cout << "Enter the edges (src, dest, weight):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    dijkstra(graph, 0, n);

    return 0;
}
