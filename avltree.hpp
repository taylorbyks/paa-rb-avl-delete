//
//  avltree.hpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 26/06/22.
//

#ifndef avltree_hpp
#define avltree_hpp

#include <iostream>

using namespace std;

struct AVLNode {
  int data;
  int height;
  AVLNode *parent;
  AVLNode *left;
  AVLNode *right;
};

class AVLTree {
  AVLNode *root = (AVLNode *)malloc(sizeof(AVLNode));
  AVLNode *TNULL = (AVLNode *)malloc(sizeof(AVLNode));
  
  AVLNode *searchTreeHelper(AVLNode *node, int key);
  AVLNode *searchTree(int key);
  AVLNode *createNode(int key);
  AVLNode *maximum(AVLNode *node);
  void transplant(AVLNode *u, AVLNode *v);
  void printHelper(AVLNode *root, string indent, bool last);
  int height(AVLNode *t);
  void balance(AVLNode *&t);
  void rotateWithLeftChild(AVLNode *&k2);
  void rotateWithRightChild(AVLNode *&k1);
  void doubleWithLeftChild(AVLNode *&k3);
  void doubleWithRightChild(AVLNode *&k1);
  void removePostorderHelper(AVLNode* node);

 public:
  AVLTree();
  ~AVLTree();

  void insert(const int key);
  void print();
  void remove(const int data);
  void removePostorder();
};

#endif /* avltree_hpp */
