#include "btree.h"
#include <algorithm>
#include <numeric>

void splitChild(Node* node, int i, Node* child) {
  Node* newChild = new Node(child->t);
  newChild->isLeaf = child->isLeaf;

  newChild->key.assign(child->key.begin() + node->t, child->key.end());
  child->key.resize(node->t - 1);

  if (!child->isLeaf) {
    newChild->children.assign(child->children.begin() + node->t, child->children.end());
    child->children.resize(node->t);
  }

  node->children.insert(node->children.begin() + i + 1, newChild);
  node->key.insert(node->key.begin() + i, child->key[node->t - 1]);
}

int insertNonFull(Node* node, int key) {
  int i = node->key.size() - 1;
  int result = 0;

  if (node->isLeaf) {
    node->key.push_back(0);
    while (i >= 0 && node->key[i] > key) {
      node->key[i + 1] = node->key[i];
      i--;
    }
    node->key[i + 1] = key;
  } else {
    while (i >= 0 && node->key[i] > key) i--;
    i++;
    if (node->children[i]->key.size() == 2 * node->t - 1) {
      splitChild(node, i, node->children[i]);
      result++;
      if (node->key[i] < key) i++;
    }
    result += insertNonFull(node->children[i], key);
  }

  return result;
}

int64_t sumLeafNodes(const Node* node) {
  if (node->isLeaf) {
    return accumulate(node->key.begin(), node->key.end(), int64_t(0));
  }
    
  return accumulate(node->children.begin(), node->children.end(), int64_t(0),
                         [](int64_t sum, const Node* child) {
                           return sum + sumLeafNodes(child);
                         });
}

Node::Node(int t) : t(t), isLeaf(true), parent(nullptr) {}

void clear(Node* node) {
  if (!node) return;
  for (Node* child : node->children) 
    clear(child);
  delete node;
}

BTree::BTree(int t) : root(nullptr), t_(t), size_(0) {}

BTree::~BTree() {
  clear(root);
}

void BTree::insert(int key) {
  if (!root) {
    root = new Node(t_);
    root->key.push_back(key);
    size_ = 1;
    return;
  }

  Node* current = root;
  while (current) {
    if (std::find(current->key.begin(), current->key.end(), key) != current->key.end()) 
      return;

    if (current->isLeaf) 
      break;

    size_t i = 0;
    while (i < current->key.size() && key > current->key[i]) 
      i++;
    current = current->children[i];
  }

  if (root->key.size() == 2 * t_ - 1) {
    Node* newRoot = new Node(t_);
    newRoot->isLeaf = false;
    newRoot->children.push_back(root);
    splitChild(newRoot, 0, root);
    size_ += 2;
    root = newRoot;
  }

  size_ += insertNonFull(root, key);
}

size_t BTree::size() const {
  return size_;
}

int64_t BTree::sum() const {
  return root ? sumLeafNodes(root) : 0;
}
