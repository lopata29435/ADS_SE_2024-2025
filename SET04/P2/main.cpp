#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <tuple>
#include <limits>

using namespace std;

struct Node {
    int key;
    int left, right;
    char color;
};

bool isBinarySearchTree(const unordered_map<int, Node>& tree, int node, int minKey, int maxKey) {
    if (node == 0) return true;
    const Node& current = tree.at(node);
    if (current.key <= minKey || current.key >= maxKey) return false;
    return isBinarySearchTree(tree, current.left, minKey, current.key) &&
           isBinarySearchTree(tree, current.right, current.key, maxKey);
}

bool hasValidRedBlackProperties(const unordered_map<int, Node>& tree, int node) {
    if (node == 0) return true;
    const Node& current = tree.at(node);
    if (current.color == 'R') {
        if (current.left != 0 && tree.at(current.left).color == 'R') return false;
        if (current.right != 0 && tree.at(current.right).color == 'R') return false;
    }
    return hasValidRedBlackProperties(tree, current.left) &&
           hasValidRedBlackProperties(tree, current.right);
}

int checkBlackHeight(const unordered_map<int, Node>& tree, int node, bool& isBalanced) {
    if (node == 0) return 1;
    const Node& current = tree.at(node);

    int leftHeight = checkBlackHeight(tree, current.left, isBalanced);
    int rightHeight = checkBlackHeight(tree, current.right, isBalanced);

    if (leftHeight != rightHeight) isBalanced = false;

    return leftHeight + (current.color == 'B' ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, root;
    cin >> n;
    if (n == 0) {
        cout << "NO" << endl;
        return 0;
    }
    cin >> root;

    unordered_map<int, Node> tree;

    for (int i = 0; i < n; ++i) {
        int number, key;
        string leftStr, rightStr;
        char color;
        cin >> number >> key >> leftStr >> rightStr >> color;

        int left = (leftStr == "null" ? 0 : stoi(leftStr));
        int right = (rightStr == "null" ? 0 : stoi(rightStr));

        tree[number] = {key, left, right, color};
    }

    bool isValid = true;

    if (tree[root].color != 'B') isValid = false;

    if (!isBinarySearchTree(tree, root, numeric_limits<int>::min(), numeric_limits<int>::max())) isValid = false;

    if (!hasValidRedBlackProperties(tree, root)) isValid = false;

    bool isBalanced = true;
    checkBlackHeight(tree, root, isBalanced);
    if (!isBalanced) isValid = false;

    cout << (isValid ? "YES" : "NO") << endl;

    return 0;
}