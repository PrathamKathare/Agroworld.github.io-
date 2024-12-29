#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
    vector<int> BIT;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        BIT.resize(n + 1, 0);
    }

    void update(int index, int val) {
        while (index <= n) {
            BIT[index] += val;
            index += index & (-index);
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & (-index);
        }
        return sum;
    }
};

int main() {
    int n, q;
    cout << "Enter the number of elements: ";
    cin >> n;
    FenwickTree ft(n);

    cout << "Enter updates to BIT (index and value):\n";
    for (int i = 0; i < n; i++) {
        int index, value;
        cin >> index >> value;
        ft.update(index, value);
    }

    cout << "Enter query index: ";
    cin >> q;
    cout << "Cumulative sum till index " << q << ": " << ft.query(q) << endl;

    return 0;
}
