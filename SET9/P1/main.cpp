#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    long long freq;
    Node *left, *right;
    Node(char c, long long f, Node* l = nullptr, Node* r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) const {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* node, const string& prefix, array<string,26>& codes) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->ch - 'a'] = prefix.empty() ? "0" : prefix;
    } else {
        buildCodes(node->left,  prefix + '0', codes);
        buildCodes(node->right, prefix + '1', codes);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0;

    array<long long,26> freq{};
    for (char c : s) {
        if ('a' <= c && c <= 'z')
            freq[c - 'a']++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    int distinct = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            pq.push(new Node(char('a'+i), freq[i]));
            distinct++;
        }
    }

    if (pq.empty()) {
        return 0;
    }
    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node('\0', a->freq + b->freq, a, b));
    }
    Node* root = pq.top();

    array<string,26> codes;
    buildCodes(root, "", codes);

    string encoded;
    encoded.reserve(s.size() * 2);
    long long totalLen = 0;
    for (char c : s) {
        const string& code = codes[c - 'a'];
        encoded += code;
        totalLen += code.size();
    }

    cout << distinct << " " << totalLen << "\n";
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            cout << char('a'+i) << ": " << codes[i] << "\n";
        }
    }
    cout << encoded << "\n";

    return 0;
}
