#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> value;
    vector<pair<char, Node*>> children;
    Node* output = nullptr;
    Node* suffixLink;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    int n;
    cin >> n;
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }

    Node* root = new Node;
    root->suffixLink = root;
    Node* currentNode;

    for (int i = 0; i < n; i++) {
        currentNode = root;
        int strLen = strings[i].length();
        
        for (int j = 0; j < strLen; j++) {
            bool isNewNode = true;

            for (auto& child : currentNode->children) {
                if (child.first == strings[i][j]) {
                    isNewNode = false;
                    currentNode = child.second;
                    break;
                }
            }

            if (isNewNode) {
                Node* newNode = new Node;
                currentNode->children.push_back({strings[i][j], newNode});
                currentNode = newNode;
            }
        }
        currentNode->value.push_back(i);
    }

    queue<Node*> q;
    for (auto& child : root->children) {
        q.push(child.second);
        child.second->suffixLink = root;
    }

    Node* tmp;
    while (!q.empty()) {
        currentNode = q.front();
        q.pop();

        for (auto& child : currentNode->children) {
            q.push(child.second);
            child.second->suffixLink = root;

            tmp = currentNode;
            bool found = true;

            do {
                tmp = tmp->suffixLink;
                for (auto& suffixChild : tmp->children) {
                    if (suffixChild.first == child.first) {
                        child.second->suffixLink = suffixChild.second;
                        found = false;
                        break;
                    }
                }
            } while (tmp != root && found);

            if (!child.second->suffixLink->value.empty()) {
                child.second->output = child.second->suffixLink;
            } else if (child.second->suffixLink->output != nullptr) {
                child.second->output = child.second->suffixLink->output;
            }
        }
    }

    vector<vector<int>> ans(n);
    int strLen = str.length();
    currentNode = root;

    for (int i = 0; i < strLen; i++) {
        bool foundMatch = true;
        
        while (foundMatch) {
            for (auto& child : currentNode->children) {
                if (child.first == str[i]) {
                    currentNode = child.second;
                    foundMatch = false;
                    break;
                }
            }
            if (currentNode == root) {
                break;
            }
            if (foundMatch) {
                currentNode = currentNode->suffixLink;
            }
        }

        for (auto& idx : currentNode->value) {
            ans[idx].push_back(i - strings[idx].length() + 2);
        }

        tmp = currentNode->output;
        while (tmp != nullptr) {
            for (auto& idx : tmp->value) {
                ans[idx].push_back(i - strings[idx].length() + 2);
            }
            tmp = tmp->output;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i].size() << " ";
        for (auto idx : ans[i]) {
            cout << idx << " ";
        }
        cout << "\n";
    }

    return 0;
}
