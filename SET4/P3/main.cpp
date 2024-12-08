#include "avl_tree.h"
#include <algorithm>

Node::Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {}

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::AVLTree(int value) : root_(new Node(value)), size_(1) {}

AVLTree::~AVLTree() {
    while (root_) {
        root_ = removeNode(root_, root_->value);
    }
}

int AVLTree::getNodeHeight(Node *node) {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(Node *node) {
    return getNodeHeight(node->right) - getNodeHeight(node->left);
}

void AVLTree::balanceHeight(Node *node) {
    node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

Node *AVLTree::rotateRight(Node *node) {
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    balanceHeight(node);
    balanceHeight(newRoot);
    return newRoot;
}

Node *AVLTree::rotateLeft(Node *node) {
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    balanceHeight(node);
    balanceHeight(newRoot);
    return newRoot;
}

Node *AVLTree::balanceNode(Node *node) {
    balanceHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

Node *AVLTree::insertNode(Node *node, int value) {
    if (!node) {
        ++size_;
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    return balanceNode(node);
}

Node *AVLTree::removeMinNode(Node *node) {
    if (!node->left) return node->right;
    node->left = removeMinNode(node->left);
    return balanceNode(node);
}

Node *AVLTree::removeNode(Node *node, int value) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        --size_;
        if (!right) return left;
        Node *min = findMinNode(right);
        min->right = removeMinNode(right);
        min->left = left;
        return balanceNode(min);
    }
    return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
    while (node->left) node = node->left;
    return node;
}

Node *AVLTree::findNode(Node *node, int value) {
    if (!node) return nullptr;
    if (value == node->value) return node;
    if (value < node->value) return findNode(node->left, value);
    return findNode(node->right, value);
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
    if (!node) return;
    traversalInternal(node->left, array, index);
    array[(*index)++] = node->value;
    traversalInternal(node->right, array, index);
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
    if (!current) return nullptr;
    if (value > current->value) {
        return lowerBoundInternal(current->right, value);
    }
    Node *candidate = lowerBoundInternal(current->left, value);
    return candidate ? candidate : current;
}

void AVLTree::insert(int value) { root_ = insertNode(root_, value); }

void AVLTree::erase(int value) { root_ = removeNode(root_, value); }

int *AVLTree::find(int value) {
    Node *node = findNode(root_, value);
    return node ? &node->value : nullptr;
}

int *AVLTree::traversal() {
    if (size_ == 0) return nullptr;
    int *result = new int[size_];
    int index = 0;
    traversalInternal(root_, result, &index);
    return result;
}

int *AVLTree::lowerBound(int value) {
    Node *node = lowerBoundInternal(root_, value);
    return node ? &node->value : nullptr;
}

bool AVLTree::empty() { return size_ == 0; }

int AVLTree::getSize() { return size_; }

Node *AVLTree::getRoot() { return root_; }

int AVLTree::getHeight() { return getNodeHeight(root_); }
