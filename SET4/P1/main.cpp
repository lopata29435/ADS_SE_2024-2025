#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

int checkBalance(Node* root, bool& isBalanced) {
    if (root == nullptr)
        return 0;

    int leftHeight = checkBalance(root->left, isBalanced);
    int rightHeight = checkBalance(root->right, isBalanced);

    if (abs(leftHeight - rightHeight) > 1)
        isBalanced = false;

    return max(leftHeight, rightHeight) + 1;
}

int main() {
    Node* root = nullptr;
    int value;

    while (cin >> value && value != 0) {
        root = insert(root, value);
    }

    bool isBalanced = true;
    checkBalance(root, isBalanced);

    if (isBalanced)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}