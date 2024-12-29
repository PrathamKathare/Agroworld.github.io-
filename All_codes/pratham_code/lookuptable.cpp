#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of lookup values: ";
    cin >> n;
    vector<int> lookupTable(n);

    cout << "Enter lookup values:\n";
    for (int i = 0; i < n; i++) {
        cin >> lookupTable[i];
    }

    int index;
    cout << "Enter index to query: ";
    cin >> index;

    if (index >= 0 && index < n) {
        cout << "Value at index " << index << ": " << lookupTable[index] << endl;
    } else {
        cout << "Index out of bounds.\n";
    }

    return 0;
}
