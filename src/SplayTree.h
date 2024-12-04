#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h" // Assuming Node is defined here

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

    Node* splay(Node* node, const std::string& key) {
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

    // Inorder traversal to gather all nodes of a specific genre
    void inorderTraversalByGenre(Node* node, const std::string& genre, std::vector<Node>& filteredShows) const {
        if (!node) return;

        if (node->genre == genre) {
            filteredShows.push_back(*node); // Add to filtered list if genre matches
        }

        inorderTraversalByGenre(node->left, genre, filteredShows);
        inorderTraversalByGenre(node->right, genre, filteredShows);
    }

public:
    SplayTree() : root(nullptr) {}

    // Insert a node into the splay tree
    void insert(const Node& node) {
        if (!root) {
            root = new Node(node.title, node.rating, node.genre, node.director);
            return;
        }
        root = splay(root, node.title);

        if (node.title == root->title)
            return;

        Node* newNode = new Node(node.title, node.rating, node.genre, node.director);
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

    // Find a node by title (splay the tree)
    bool find(const std::string& key) {
        root = splay(root, key);
        return root && root->title == key;
    }

    // Remove a node by title (splay the tree)
    void remove(const std::string& key) {
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

    // Inorder traversal to display the tree
    void inorderTraversal(Node* node) const {
        if (!node)
            return;
        inorderTraversal(node->left);
        std::cout << node->title << " (" << node->rating << ")\n";
        inorderTraversal(node->right);
    }

    // Display the entire tree (inorder)
    void display() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    // Get shows of a specific genre, sorted by rating in descending order
    std::vector<Node> getShowsByGenre(const std::string& genre) {
        std::vector<Node> filteredShows;
        inorderTraversalByGenre(root, genre, filteredShows);

        // Sort the filtered shows by rating (descending order)
        std::sort(filteredShows.begin(), filteredShows.end(), [](const Node& a, const Node& b) {
            return a.rating > b.rating;
        });

        return filteredShows;
    }

    // Get the root of the splay tree
    Node* getRoot() const {
        return root;
    }

    // Destructor to clean up memory
    ~SplayTree() {
        while (root)
            remove(root->title);
    }
};

#endif // SPLAY_TREE_H