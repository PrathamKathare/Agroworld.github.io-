#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>
#include <set>

// ------------ Graphs for Navigation and Connectivity ------------
class Graph {
public:
    struct Edge {
        int destination;
        int weight;
    };
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    
    // Dijkstra's Algorithm (Shortest Path)
    std::vector<int> dijkstra(int start, int n) {
        std::vector<int> dist(n, INT_MAX);
        dist[start] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const auto& edge : adj[u]) {
                int v = edge.destination;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // Floyd-Warshall Algorithm (All pairs shortest path)
    std::vector<std::vector<int>> floydWarshall(int n) {
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        
        for (const auto& entry : adj) {
            int u = entry.first;
            for (const auto& edge : entry.second) {
                dist[u][edge.destination] = edge.weight;
            }
        }
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        return dist;
    }

private:
    std::unordered_map<int, std::vector<Edge>> adj;
};

// ------------ AVL Tree for Hierarchical Management ------------
class AVLTree {
public:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insertRec(root, key);
    }
    
    bool search(int key) {
        return searchRec(root, key);
    }
    
    void remove(int key) {
        root = removeRec(root, key);
    }

private:
    Node* root;
    
    Node* insertRec(Node* node, int key) {
        if (!node) return new Node(key);
        
        if (key < node->key)
            node->left = insertRec(node->left, key);
        else
            node->right = insertRec(node->right, key);
        
        node->height = 1 + std::max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    Node* removeRec(Node* root, int key) {
        if (!root) return root;
        
        if (key < root->key)
            root->left = removeRec(root->left, key);
        else if (key > root->key)
            root->right = removeRec(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = getMinValueNode(root->right);
                root->key = temp->key;
                root->right = removeRec(root->right, temp->key);
            }
        }
        
        if (!root) return root;
        
        root->height = 1 + std::max(height(root->left), height(root->right));
        
        int balance = getBalance(root);
        
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        
        return root;
    }
    
    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;
        
        y->left = z;
        z->right = T2;
        
        z->height = std::max(height(z->left), height(z->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    Node* getMinValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }
    
    bool searchRec(Node* root, int key) {
        if (!root) return false;
        if (key == root->key) return true;
        if (key < root->key) return searchRec(root->left, key);
        return searchRec(root->right, key);
    }
};

// ------------ Merge Sort (for Sorting) ------------
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ------------ Priority Queue (Min-Heap for Emergency Response) ------------
void priorityQueueExample() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);
    
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;
}

// ------------ Hash Table for Fast Lookups ------------
void hashTableExample() {
    std::unordered_map<std::string, int> hashMap;
    hashMap["Hospital1"] = 1;
    hashMap["Hospital2"] = 2;
    
    std::cout << "Hospital1 ID: " << hashMap["Hospital1"] << std::endl;
}

// ------------ Testing the Code ------------

int main() {
    // Test Graph (Dijkstra & Floyd-Warshall)
    Graph g;
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(1, 3, 5);
    
    std::vector<int> dist = g.dijkstra(0, 4);
    for (int i = 0; i < 4; ++i) {
        std::cout << "Distance from 0 to " << i << ": " << dist[i] << std::endl;
    }
    
    std::vector<std::vector<int>> allDist = g.floydWarshall(4);
    std::cout << "Floyd-Warshall Distance from 0 to 3: " << allDist[0][3] << std::endl;
    
    // Test AVL Tree
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    
    std::cout << "Search 10 in AVL: " << tree.search(10) << std::endl;
    
    // Test Merge Sort
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    mergeSort(arr, 0, arr.size() - 1);
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    
    // Test Priority Queue (Min-Heap)
    priorityQueueExample();
    
    // Test Hash Table
    hashTableExample();
    
    return 0;
}
