#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <algorithm>
using namespace std;


int brute_force_search(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    for (int i = 0; i <= n - m; i++) {
        if (text.substr(i, m) == pattern)
            return i; 
    }
    return -1;
}
int boyer_moore_search(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0) return -1;
    
    vector<int> bad_char(256, -1); 
    
   
    for (int i = 0; i < m; i++) {
        bad_char[(int)pattern[i]] = i;
    }
    
    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        
        if (j < 0) {
            return i; 
        } else {
          
            i += max(1, j - bad_char[(int)text[i + j]]);
        }
    }
    return -1;
}

int kmp_search(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0) return -1;
    
    
    vector<int> lps(m, 0);
    

    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        lps[i] = j;
    }
    
   
    int i = 0;
    j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        
        if (j == m) {
            return i - j; 
        } else if (i < n && text[i] != pattern[j]) {
            if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1; 
}
int rabin_karp_search(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0) return -1;
    
    const int d = 256; 
    const int q = 101; 
    
    int h_pattern = 0, h_text = 0; 
    int h = 1; 
    
  
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    
    
    for (int i = 0; i < m; i++) {
        h_pattern = (d * h_pattern + pattern[i]) % q;
        h_text = (d * h_text + text[i]) % q;
    }
    
    
    for (int i = 0; i <= n - m; i++) {
        
        if (h_pattern == h_text) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) {
                j++;
            }
            if (j == m) {
                return i; 
            }
        }
        
        
        if (i < n - m) {
            h_text = (d * (h_text - text[i] * h) + text[i + m]) % q;
            if (h_text < 0) {
                h_text += q;
            }
        }
    }
    
    return -1; 
}

void dfs(const unordered_map<string, vector<string>>& graph, const string& node, unordered_set<string>& visited) {
    visited.insert(node);
    cout << "Visiting node: " << node << endl; 
    
    for (const string& neighbor : graph.at(node)) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(graph, neighbor, visited); 
        }
    }
}


void bfs(const unordered_map<string, vector<string>>& graph, const string& start) {
    unordered_set<string> visited;
    queue<string> q;
    
    visited.insert(start);
    q.push(start);
    
    while (!q.empty()) {
        string node = q.front();
        q.pop();
        cout << "Visiting node: " << node << endl; 
        
        for (const string& neighbor : graph.at(node)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}


void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); 
            }
        }
    }
}


void insertion_sort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; 
    }
}


void selection_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]); 
    }
}


void floyd_warshall(vector<vector<int>>& graph, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j]; 
                }
            }
        }
    }
}


struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int data) {
    if (!root) return new Node(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        Node* temp = root->right;
        while (temp && temp->left) temp = temp->left;
        
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}


void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        
        quick_sort(arr, low, i);
        quick_sort(arr, i + 2, high);
    }
}


void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


void dijkstra(vector<vector<int>>& graph, int source, int V) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }
    
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "To node " << i << ": " << dist[i] << endl;
    }
}

struct Edge {
    int u, v, weight;
};

bool compare(Edge& e1, Edge& e2) {
    return e1.weight < e2.weight;
}

int find_parent(int i, vector<int>& parent) {
    if (parent[i] == i) return i;
    return parent[i] = find_parent(parent[i], parent);
}

void kruskal(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compare);
    
    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;
    
    vector<Edge> mst;
    
    for (Edge edge : edges) {
        int u = edge.u;
        int v = edge.v;
        
        int root_u = find_parent(u, parent);
        int root_v = find_parent(v, parent);
        
        if (root_u != root_v) {
            mst.push_back(edge);
            parent[root_u] = root_v;
        }
    }
    
    cout << "Edges in the Minimum Spanning Tree (MST):\n";
    for (Edge edge : mst) {
        cout << edge.u << " - " << edge.v << " with weight " << edge.weight << endl;
    }
}
// AVL Tree implementation
class AVLTree {
    struct Node {
        int key, height;
        Node *left, *right;
        Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balance_factor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* right_rotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* left_rotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balance_factor(node);

        if (balance > 1 && key < node->left->key) return right_rotate(node);
        if (balance < -1 && key > node->right->key) return left_rotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};


class RedBlackTree {
    struct Node {
        int data;
        Node *left, *right, *parent;
        bool color; 
        Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
    };

    Node* root;

    void rotate_left(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        if (right->left) right->left->parent = node;
        right->parent = node->parent;
        if (!node->parent) root = right;
        else if (node == node->parent->left) node->parent->left = right;
        else node->parent->right = right;
        right->left = node;
        node->parent = right;
    }

    void rotate_right(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        if (left->right) left->right->parent = node;
        left->parent = node->parent;
        if (!node->parent) root = left;
        else if (node == node->parent->left) node->parent->left = left;
        else node->parent->right = left;
        left->right = node;
        node->parent = left;
    }

    void fix_insert(Node* node) {
        while (node != root && node->parent->color == true) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotate_left(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotate_right(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotate_right(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotate_left(node->parent->parent);
                }
            }
        }
        root->color = false;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* new_node = new Node(data);
        if (!root) {
            root = new_node;
            root->color = false; 
        } else {
            Node* current = root;
            while (current) {
                if (data < current->data) {
                    if (!current->left) {
                        current->left = new_node;
                        new_node->parent = current;
                        break;
                    }
                    current = current->left;
                } else {
                    if (!current->right) {
                        current->right = new_node;
                        new_node->parent = current;
                        break;
                    }
                    current = current->right;
                }
            }
            fix_insert(new_node);
        }
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};


class TwoThreeTree {
    struct Node {
        int key1, key2;
        Node *left, *middle, *right;
        bool isLeaf;
        Node() : key1(INT_MIN), key2(INT_MIN), left(nullptr), middle(nullptr), right(nullptr), isLeaf(true) {}
    };

    Node* root;

    Node* insert(Node* node, int key) {
        if (node->isLeaf) {
            if (key < node->key1) {
                node->key2 = node->key1;
                node->key1 = key;
            } else if (key < node->key2 || node->key2 == INT_MIN) {
                node->key2 = key;
            }
        } else {
            
            if (key < node->key1) insert(node->left, key);
            else if (key < node->key2) insert(node->middle, key);
            else insert(node->right, key);
        }
        return node;
    }

public:
    TwoThreeTree() : root(new Node()) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void inorder() {
        inorder_helper(root);
        cout << endl;
    }

    void inorder_helper(Node* node) {
        if (!node) return;
        inorder_helper(node->left);
        cout << node->key1 << " ";
        inorder_helper(node->middle);
        if (node->key2 != INT_MIN) cout << node->key2 << " ";
        inorder_helper(node->right);
    }
};


class FenwickTree {
    vector<int> tree;

public:
    FenwickTree(int n) : tree(n + 1, 0) {}

    void update(int idx, int delta) {
        while (idx < tree.size()) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};


class SegmentTree {
    vector<int> tree, arr;

    int build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2*node, start, mid);
            build(2*node + 1, mid + 1, end);
            tree[node] = tree[2*node] + tree[2*node + 1];
        }
        return tree[node];
    }

public:
    SegmentTree(const vector<int>& data) {
        arr = data;
        tree.resize(4 * arr.size());
        build(1, 0, arr.size() - 1);
    }

    int range_sum(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int left_sum = range_sum(2*node, start, mid, l, r);
        int right_sum = range_sum(2*node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }
};


class LookupTable {
    unordered_map<int, int> table;

public:
    void insert(int key, int value) {
        table[key] = value;
    }

    int lookup(int key) {
        return table.count(key) ? table[key] : -1;
    }
};

int main() {
    int choice;
    cout << "Choose an algorithm:\n";
    cout << "1. Brute Force String Search\n";
    cout << "2. DFS (Depth First Search)\n";
    cout << "3. BFS (Breadth First Search)\n";
    cout << "4. Bubble Sort\n";
    cout << "5. Insertion Sort\n";
    cout << "6. Selection Sort\n";
    cout << "7. Floyd-Warshall Algorithm\n";
    cout << "8. Binary Search Tree (Insert/Delete/Traversal)\n";
    cout << "9. Quick Sort\n";
    cout << "10. Merge Sort\n";
    cout << "11. Heap Sort\n";
    cout << "12. Dijkstra's Algorithm\n";
    cout << "13. Kruskal's Algorithm\n";
    cout << "14. Boyer-Moore String Search\n";  
    cout << "15. KMP String Search\n";         
    cout << "16. Rabin-Karp String Search\n";
    cout << "17. AVL Tree\n";
    cout << "18. Red-Black Tree\n";
    cout << "19. 2-3 Tree\n";
    cout << "20. Fenwick Tree\n";
    cout << "21. Segment Tree\n";
    cout << "22. Lookup Table\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
        case 1: {
            string text, pattern;
            cout << "Enter the text: ";
            getline(cin, text);
            cout << "Enter the pattern: ";
            getline(cin, pattern);
            int result = brute_force_search(text, pattern);
            if (result != -1)
                cout << "Pattern found at index " << result << endl;
            else
                cout << "Pattern not found!" << endl;
            break;
        }
        case 2: {
            unordered_map<string, vector<string>> graph;
            int n;
            cout << "Enter number of nodes in the graph: ";
            cin >> n;
            cin.ignore();
            
            for (int i = 0; i < n; i++) {
                string node;
                int m;
                cout << "Enter node " << i + 1 << ": ";
                getline(cin, node);
                cout << "Enter number of neighbors for " << node << ": ";
                cin >> m;
                cin.ignore(); 
                vector<string> neighbors(m);
                for (int j = 0; j < m; j++) {
                    cout << "Enter neighbor " << j + 1 << ": ";
                    getline(cin, neighbors[j]);
                }
                graph[node] = neighbors;
            }

            string start;
            cout << "Enter the starting node for DFS: ";
            getline(cin, start);
            unordered_set<string> visited;
            dfs(graph, start, visited);
            break;
        }
        case 3: {
            unordered_map<string, vector<string>> graph;
            int n;
            cout << "Enter number of nodes in the graph: ";
            cin >> n;
            cin.ignore(); 

            for (int i = 0; i < n; i++) {
                string node;
                int m;
                cout << "Enter node " << i + 1 << ": ";
                getline(cin, node);
                cout << "Enter number of neighbors for " << node << ": ";
                cin >> m;
                cin.ignore(); 
                vector<string> neighbors(m);
                for (int j = 0; j < m; j++) {
                    cout << "Enter neighbor " << j + 1 << ": ";
                    getline(cin, neighbors[j]);
                }
                graph[node] = neighbors;
            }

            string start;
            cout << "Enter the starting node for BFS: ";
            getline(cin, start);
            bfs(graph, start);
            break;
        }
        case 4: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            bubble_sort(arr);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 5: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            insertion_sort(arr);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 6: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            selection_sort(arr);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 7: {
            int V;
            cout << "Enter the number of vertices: ";
            cin >> V;
            vector<vector<int>> graph(V, vector<int>(V));
            cout << "Enter the adjacency matrix (use INT_MAX for no connection):\n";
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    cin >> graph[i][j];
                }
            }
            floyd_warshall(graph, V);
            break;
        }
        case 8: {
            Node* root = nullptr;
            int n, val;
            cout << "Enter the number of elements to insert in BST: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Enter the element: ";
                cin >> val;
                root = insert(root, val);
            }
            cout << "Inorder traversal: ";
            inorder(root);
            cout << endl;

            cout << "Enter the element to delete: ";
            cin >> val;
            root = deleteNode(root, val);
            cout << "Inorder traversal after deletion: ";
            inorder(root);
            cout << endl;
            break;
        }
        case 9: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            quick_sort(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 10: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            merge_sort(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 11: {
            int n;
            cout << "Enter the number of elements to sort: ";
            cin >> n;
            vector<int> arr(n);
            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            heap_sort(arr);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            break;
        }
        case 12: {
            int V, source;
            cout << "Enter the number of vertices: ";
            cin >> V;
            vector<vector<int>> graph(V, vector<int>(V));
            cout << "Enter the adjacency matrix (use 0 for no connection):\n";
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    cin >> graph[i][j];
                }
            }
            cout << "Enter the source vertex: ";
            cin >> source;
            dijkstra(graph, source, V);
            break;
        }
        case 13: {
            int V, E;
            cout << "Enter the number of vertices: ";
            cin >> V;
            cout << "Enter the number of edges: ";
            cin >> E;
            
            vector<Edge> edges(E);
            cout << "Enter the edges in the form (u, v, weight):\n";
            for (int i = 0; i < E; i++) {
                cin >> edges[i].u >> edges[i].v >> edges[i].weight;
            }
            kruskal(edges, V);
            break;
        }
              case 14: {
            string text, pattern;
            cout << "Enter the text: ";
            getline(cin, text);
            cout << "Enter the pattern: ";
            getline(cin, pattern);
            int result = boyer_moore_search(text, pattern);
            if (result != -1)
                cout << "Pattern found at index " << result << endl;
            else
                cout << "Pattern not found!" << endl;
            break;
        }
        case 15: {
            string text, pattern;
            cout << "Enter the text: ";
            getline(cin, text);
            cout << "Enter the pattern: ";
            getline(cin, pattern);
            int result = kmp_search(text, pattern);
            if (result != -1)
                cout << "Pattern found at index " << result << endl;
            else
                cout << "Pattern not found!" << endl;
            break;
        }
        case 16: {
            string text, pattern;
            cout << "Enter the text: ";
            getline(cin, text);
            cout << "Enter the pattern: ";
            getline(cin, pattern);
            int result = rabin_karp_search(text, pattern);
            if (result != -1)
                cout << "Pattern found at index " << result << endl;
            else
                cout << "Pattern not found!" << endl;
            break;
        }
        case 17: {
        AVLTree avl;
        int n, value;
        cout << "Enter number of elements to insert: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter value: ";
            cin >> value;
            avl.insert(value);
        }
        avl.inorder();
        break;
    }
    case 18: {
        RedBlackTree rbt;
        int n, value;
        cout << "Enter number of elements to insert: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter value: ";
            cin >> value;
            rbt.insert(value);
        }
        rbt.inorder();
        break;
    }
    case 19: {
        TwoThreeTree tt;
        int n, value;
        cout << "Enter number of elements to insert: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter value: ";
            cin >> value;
            tt.insert(value);
        }
        tt.inorder();
        break;
    }
    case 20: {
        int n, idx, delta;
        cout << "Enter size of Fenwick Tree: ";
        cin >> n;
        FenwickTree fenwick(n);
        cout << "Enter number of updates: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter index and delta: ";
            cin >> idx >> delta;
            fenwick.update(idx, delta);
        }
        cout << "Enter index to query sum: ";
        cin >> idx;
        cout << "Sum up to index " << idx << ": " << fenwick.query(idx) << endl;
        break;
    }
    case 21: {
        int n, l, r;
        cout << "Enter number of elements in Segment Tree: ";
        cin >> n;
        vector<int> data(n);
        cout << "Enter elements:\n";
        for (int i = 0; i < n; ++i) {
            cin >> data[i];
        }
        SegmentTree st(data);
        cout << "Enter range (l, r) for range sum query: ";
        cin >> l >> r;
        cout << "Range sum (" << l << ", " << r << "): " << st.range_sum(1, 0, n - 1, l, r) << endl;
        break;
    }
    case 22: {
        LookupTable lookup;
        int key, value,n;
        cout << "Enter number of entries to insert: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter key and value: ";
            cin >> key >> value;
            lookup.insert(key, value);
        }
        cout << "Enter key to lookup: ";
        cin >> key;
        cout << "Lookup value for key " << key << ": " << lookup.lookup(key) << endl;
        break;
    }
        
        default:
            cout << "Invalid choice!" << endl;
    }
    return 0;
}
