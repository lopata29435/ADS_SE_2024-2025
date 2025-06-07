#include "rbtree.h"
#include <algorithm>

Node::Node(int key) 
    : key(key), height(1), size(1), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}

RBTree::RBTree() : root(nullptr) {}

RBTree::RBTree(std::initializer_list<int> list) : root(nullptr) {
    for (int key : list) {
        insert(key);
    }
}

void deleteNodes(Node* node) {
    if (!node) return;
    deleteNodes(node->left);
    deleteNodes(node->right);
    delete node;
}

RBTree::~RBTree() {
    deleteNodes(root);
}

void updateSize(Node* node) {
    if (node) {
        int leftSize = node->left ? node->left->size : 0;
        int rightSize = node->right ? node->right->size : 0;
        node->size = 1 + leftSize + rightSize;
    }
}

void leftRotate(Node*& root, Node*& node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right) {
        node->right->parent = node;
    }

    rightChild->parent = node->parent;

    if (!node->parent) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;

    updateSize(node);
    updateSize(rightChild);
}

void rightRotate(Node*& root, Node*& node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left) {
        node->left->parent = node;
    }

    leftChild->parent = node->parent;

    if (!node->parent) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;

    updateSize(node);
    updateSize(leftChild);
}


void fixInsert(Node*& root, Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (node != root && node->color == Color::RED && node->parent->color == Color::RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle && uncle->color == Color::RED) {
                grandparent->color = Color::RED;
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rightRotate(root, grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                grandparent->color = Color::RED;
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                leftRotate(root, grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = Color::BLACK;
}

void updateHeight(Node* node) {
    if (node) {
        int leftHeight = node->left ? node->left->height : 0;
        int rightHeight = node->right ? node->right->height : 0;
        node->height = 1 + std::max(leftHeight, rightHeight);
    }
}

void RBTree::insert(int key) {
    Node* newNode = new Node(key);
    if (!root) {
        root = newNode;
        root->color = Color::BLACK;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    Node* temp = newNode;
    while (temp) {
        updateSize(temp);
        temp = temp->parent;
    }

    fixInsert(root, newNode);
    updateHeight(root);
}

int* RBTree::find(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) {
            return &current->key;
        }
        current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

int RBTree::size() const {
    return root ? root->size : 0;
}


int* RBTree::lowerBound(int key) {
    Node* current = root;
    Node* result = nullptr;

    while (current) {
        if (current->key >= key) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result ? &result->key : nullptr;
}

bool RBTree::empty() const {
    return root == nullptr;
}

Node* minimum(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

void fixErase(Node*& root, Node*& node) {
    while (node != root && (!node || node->color == Color::BLACK)) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling && sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                leftRotate(root, node->parent);
                sibling = node->parent->right;
            }

            if ((!sibling->left || sibling->left->color == Color::BLACK) &&
                (!sibling->right || sibling->right->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (!sibling->right || sibling->right->color == Color::BLACK) {
                    if (sibling->left) sibling->left->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rightRotate(root, sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                if (sibling->right) sibling->right->color = Color::BLACK;
                leftRotate(root, node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;
            if (sibling && sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                rightRotate(root, node->parent);
                sibling = node->parent->left;
            }

            if ((!sibling->right || sibling->right->color == Color::BLACK) &&
                (!sibling->left || sibling->left->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (!sibling->left || sibling->left->color == Color::BLACK) {
                    if (sibling->right) sibling->right->color = Color::BLACK;
                    sibling->color = Color::RED;
                    leftRotate(root, sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                if (sibling->left) sibling->left->color = Color::BLACK;
                rightRotate(root, node->parent);
                node = root;
            }
        }
    }
    if (node) node->color = Color::BLACK;
}

void RBTree::erase(int key) {
    Node* node = root;
    Node* target = nullptr;
    Node* replace = nullptr;

    while (node) {
        if (key == node->key) {
            target = node;
            break;
        }
        node = (key < node->key) ? node->left : node->right;
    }

    if (!target) return;

    Color originalColor = target->color;

    if (!target->left) {
        replace = target->right;
        if (target->parent) {
            if (target == target->parent->left) {
                target->parent->left = replace;
            } else {
                target->parent->right = replace;
            }
        } else {
            root = replace;
        }
        if (replace) replace->parent = target->parent;
    } else if (!target->right) {
        replace = target->left;
        if (target->parent) {
            if (target == target->parent->left) {
                target->parent->left = replace;
            } else {
                target->parent->right = replace;
            }
        } else {
            root = replace;
        }
        if (replace) replace->parent = target->parent;
    } else {
        Node* successor = minimum(target->right);
        originalColor = successor->color;
        replace = successor->right;

        if (successor->parent == target) {
            if (replace) replace->parent = successor;
        } else {
            if (successor->parent) {
                if (successor == successor->parent->left) {
                    successor->parent->left = replace;
                } else {
                    successor->parent->right = replace;
                }
            }
            if (replace) replace->parent = successor->parent;
            successor->right = target->right;
            if (successor->right) successor->right->parent = successor;
        }

        if (target->parent) {
            if (target == target->parent->left) {
                target->parent->left = successor;
            } else {
                target->parent->right = successor;
            }
        } else {
            root = successor;
        }
        successor->parent = target->parent;
        successor->left = target->left;
        if (successor->left) successor->left->parent = successor;
        successor->color = target->color;
    }

    Node* temp = target->parent;
    while (temp) {
        updateSize(temp);
        temp = temp->parent;
    }

    delete target;

    if (originalColor == Color::BLACK) {
        fixErase(root, replace);
    }
}


int RBTree::height() const {
    return root ? root->height : 0;
}
