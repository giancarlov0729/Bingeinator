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
  string director;
  string leadingActor;
  string genre;

  Node( string title, double rating, string leadingActor, string genre, string director);{
    this->title = title;
    this->rating = rating;
    this->leadingActor = leadingActor;
    this->genre = genre;
    this->director = director;
  }
};

#endif //NODE_H
