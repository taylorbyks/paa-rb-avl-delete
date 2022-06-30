//
//  rbtree.hpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#ifndef rbtree_hpp
#define rbtree_hpp

#include <iostream>

#define BLACK 0
#define RED 1

using namespace std;

struct RBNode {
  int data;
  RBNode *parent;
  RBNode *left;
  RBNode *right;
  bool color;
};

class RBTree {
 private:
  RBNode *root = (RBNode *)malloc(sizeof(RBNode));
  RBNode *TNULL = (RBNode *)malloc(sizeof(RBNode));

  void leftRotate(RBNode *node);
  void rightRotate(RBNode *node);
  void transplant(RBNode *u, RBNode *v);
  void fixDelete(RBNode *node);
  void fixInsert(RBNode *node);
  void printHelper(RBNode *node, string indent, bool last);
  RBNode *createNode(int key);
  RBNode *searchTreeHelper(RBNode *node, int key);
  RBNode *searchTree(int key);
  RBNode *maximum(RBNode *node);

 public:
  RBTree();
  ~RBTree();

  void insert(int key);
  void remove(int key);
  void print();
};

#endif /* rbtree */
