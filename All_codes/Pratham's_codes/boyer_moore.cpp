#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> preprocess(const string& pattern) {
    vector<int> badChar(256, -1);
    for (int i = 0; i < pattern.size(); i++) {
        badChar[pattern[i]] = i;
    }
    return badChar;
}

void boyerMooreSearch(const string& text, const string& pattern) {
    vector<int> badChar = preprocess(pattern);
    int m = pattern.size();
    int n = text.size();

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
}

int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}
