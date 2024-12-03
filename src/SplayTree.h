//
// Created by Giancarlo Vidal on 12/2/24.
//

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include "node.h" // Assuming Node is defined here

class SplayTree {
private:
    Node* root;

    Node* rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }

    Node* leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }

    Node* splay(Node* node, const string& key) {
        if (!node || node->title == key)
            return node;

        // Key is in the left subtree
        if (key < node->title) {
            if (!node->left)
                return node;

            // Zig-Zig
            if (key < node->left->title) {
                node->left->left = splay(node->left->left, key);
                node = rightRotate(node);
            }
            // Zig-Zag
            else if (key > node->left->title) {
                node->left->right = splay(node->left->right, key);
                if (node->left->right)
                    node->left = leftRotate(node->left);
            }

            return node->left ? rightRotate(node) : node;
        }

        // Key is in the right subtree
        else {
            if (!node->right)
                return node;

            // Zag-Zig
            if (key < node->right->title) {
                node->right->left = splay(node->right->left, key);
                if (node->right->left)
                    node->right = rightRotate(node->right);
            }
            // Zag-Zag
            else if (key > node->right->title) {
                node->right->right = splay(node->right->right, key);
                node = leftRotate(node);
            }

            return node->right ? leftRotate(node) : node;
        }
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(const Node& node) {
        if (!root) {
            root = new Node(node.title, node.rating, node.leadingActor, node.genre, node.director);
            return;
        }
        root = splay(root, node.title);

        if (node.title == root->title)
            return;

        Node* newNode = new Node(node.title, node.rating, node.leadingActor, node.genre, node.director);
        if (node.title < root->title) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        root = newNode;
    }

    bool find(const string& key) {
        root = splay(root, key);
        return root && root->title == key;
    }

    void remove(const string& key) {
        if (!root)
            return;

        root = splay(root, key);

        if (root->title != key)
            return;

        Node* temp;
        if (!root->left) {
            temp = root;
            root = root->right;
        } else {
            temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
        }
        delete temp;
    }

    void inorderTraversal(Node* node) const {
        if (!node)
            return;
        inorderTraversal(node->left);
        std::cout << node->title << " (" << node->rating << ")\n";
        inorderTraversal(node->right);
    }

    void display() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    Node* getRoot() const {
        return root;
    }

    ~SplayTree() {
        while (root)
            remove(root->title);
    }
};

#endif // SPLAY_TREE_H