#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<int> codes(k);
    for (int i = 0; i < k; ++i) {
        cin >> codes[i];
    }

    vector<string> dict;
    dict.reserve(128 + k);
    for (int i = 0; i < 128; ++i) {
        dict.push_back(string(1, char(i)));
    }
    int nextCode = 128;

    string result;
    result.reserve(k * 4);

    string w = dict[codes[0]];
    result += w;

    for (int i = 1; i < k; ++i) {
        int c = codes[i];
        string entry;
        if (c < (int)dict.size()) {
            entry = dict[c];
        } else if (c == nextCode) {
            entry = w + w[0];
        } else {
            cerr << "Decoding error at position " << i << "\n";
            return 1;
        }
        result += entry;

        dict.push_back(w + entry[0]);
        ++nextCode;

        w = move(entry);
    }

    cout << result << "\n";
    return 0;
}
