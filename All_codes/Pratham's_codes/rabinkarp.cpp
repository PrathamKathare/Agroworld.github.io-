#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int d = 256; // Number of characters in the input alphabet
const int q = 101; // A prime number for modulo operation

void rabinKarpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    int i, j;
    int h = 1;
    int p = 0; // Hash value for the pattern
    int t = 0; // Hash value for the text

    // Calculate h = (d^(m-1)) % q
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            // Check for character by character match
            bool match = true;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        if (i < n - m) {
            // Calculate hash value for the next window of text
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) {
                t = (t + q); // Convert negative value of t
            }
        }
    }
}

int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    rabinKarpSearch(text, pattern);

    return 0;
}
