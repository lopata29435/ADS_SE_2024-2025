#include <bits/stdc++.h>
using namespace std;

struct Node {
    array<int, 2> children = {-1, -1};
    int fail = 0;
    bool is_bad = false;
};

vector<Node> nodes;

int get_transition(int u, int c, const vector<Node>& nodes) {
    while (true) {
        if (nodes[u].children[c] != -1) {
            return nodes[u].children[c];
        }
        if (nodes[u].fail == -1) {
            return 0;
        }
        u = nodes[u].fail;
    }
}

void build_aho(const vector<string>& codes) {
    nodes.clear();
    nodes.emplace_back();
    nodes[0].fail = -1;

    for (const string& s : codes) {
        int u = 0;
        for (char ch : s) {
            int c = ch - '0';
            if (nodes[u].children[c] == -1) {
                nodes.emplace_back();
                nodes[u].children[c] = nodes.size() - 1;
            }
            u = nodes[u].children[c];
        }
        nodes[u].is_bad = true;
    }

    queue<int> q;
    for (int c = 0; c < 2; ++c) {
        if (nodes[0].children[c] != -1) {
            int child = nodes[0].children[c];
            nodes[child].fail = 0;
            q.push(child);
            nodes[child].is_bad |= nodes[nodes[child].fail].is_bad;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int c = 0; c < 2; ++c) {
            int v = nodes[u].children[c];
            if (v == -1) continue;

            int f = nodes[u].fail;
            while (f != -1 && nodes[f].children[c] == -1) {
                f = nodes[f].fail;
            }
            nodes[v].fail = (f == -1) ? 0 : nodes[f].children[c];
            
            nodes[v].is_bad |= nodes[nodes[v].fail].is_bad;
            q.push(v);
        }
    }
}

bool has_cycle() {
    if (nodes[0].is_bad) return false;

    vector<int> visited(nodes.size(), 0);
    vector<int> in_path(nodes.size(), 0);

    stack<pair<int, int>> st;
    st.push({0, 0});

    while (!st.empty()) {
        auto [u, c] = st.top();
        st.pop();

        if (c == 2) {
            in_path[u] = 0;
            continue;
        }

        st.push({u, c + 1});

        int next_char = c;
        int v = get_transition(u, next_char, nodes);
        if (nodes[v].is_bad) continue;

        if (in_path[v]) {
            return true;
        }

        if (!visited[v]) {
            visited[v] = 1;
            in_path[v] = 1;
            st.push({v, 0});
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> codes(n);
    for (auto& s : codes) cin >> s;

    build_aho(codes);
    cout << (has_cycle() ? "TAK" : "NIE") << endl;
}