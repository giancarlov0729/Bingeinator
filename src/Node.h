//
// Created by Giancarlo Vidal on 12/2/24.
//

#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

struct Node {
  string title;
  double rating;
  string genre;
  string director;
  Node* left;  // Pointer to the left child
  Node* right; // Pointer to the right child

  // Constructor
  Node(string title, double rating, string genre, string director)
      : title(std::move(title)),
        rating(rating),
        genre(std::move(genre)),
        director(std::move(director)),
        left(nullptr),
        right(nullptr) {}
};

#endif // NODE_H