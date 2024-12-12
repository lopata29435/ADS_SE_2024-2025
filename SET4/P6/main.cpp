#include "splay-tree.h"
#include <algorithm>

Node::Node(int key, Node *parent) : key(key), left(nullptr), right(nullptr), parent(parent) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::insert(int key) {
    if (!root) {
        root = new Node(key, nullptr);
        return;
    }

    Node *current = root;
    Node *parent = nullptr;

    while (current) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return;
    }

    if (key < parent->key)
        parent->left = new Node(key, parent);
    else
        parent->right = new Node(key, parent);
}

Node *SplayTree::find(int key) const {
    Node *current = root;

    while (current) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current;
    }

    return nullptr;
}

int SplayTree::splay(Node *node) {
    if (!node)
        return 0;

    int rotations = 0;

    while (node->parent) {
        if (!node->parent->parent) {
            if (node->parent->left == node)
                rotateRight(node->parent);
            else
                rotateLeft(node->parent);
            rotations++;
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            rotateRight(node->parent->parent);
            rotateRight(node->parent);
            rotations += 2;
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            rotateLeft(node->parent->parent);
            rotateLeft(node->parent);
            rotations += 2;
        } else {
            if (node->parent->left == node && node->parent->parent->right == node->parent) {
                rotateRight(node->parent);
                rotateLeft(node->parent);
            } else {
                rotateLeft(node->parent);
                rotateRight(node->parent);
            }
            rotations++;
        }
    }

    root = node;
    return rotations;
}


int SplayTree::getHeight() const {
    return getHeight(root);
}

void SplayTree::clear(Node *node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void SplayTree::rotateLeft(Node *node) {
    Node *pivot = node->right;
    if (!pivot) return;

    node->right = pivot->left;
    if (pivot->left)
        pivot->left->parent = node;

    pivot->parent = node->parent;
    if (!node->parent)
        root = pivot;
    else if (node->parent->left == node)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;

    pivot->left = node;
    node->parent = pivot;
}

void SplayTree::rotateRight(Node *node) {
    Node *pivot = node->left;
    if (!pivot) return;

    node->left = pivot->right;
    if (pivot->right)
        pivot->right->parent = node;

    pivot->parent = node->parent;
    if (!node->parent)
        root = pivot;
    else if (node->parent->left == node)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;

    pivot->right = node;
    node->parent = pivot;
}

int SplayTree::getHeight(Node *node) const {
    if (!node) return -1;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}
