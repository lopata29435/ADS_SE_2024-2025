#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0;

    unordered_map<string, int> dict;
    dict.reserve(1 << 10);
    for (int i = 0; i < 128; ++i) {
        dict[string(1, char(i))] = i;
    }
    int nextCode = 128;

    vector<int> output;
    output.reserve(s.size());

    string w;
    w.reserve(64);
    for (char c : s) {
        string wc = w + c;
        if (dict.count(wc)) {
            w = move(wc);
        } else {
            output.push_back(dict[w]);
            dict[wc] = nextCode++;
            w.clear();
            w.push_back(c);
        }
    }
    if (!w.empty()) {
        output.push_back(dict[w]);
    }

    cout << output.size() << "\n";
    for (int code : output) {
        cout << code << " ";
    }
    cout << "\n";

    return 0;
}
