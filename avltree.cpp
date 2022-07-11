//
//  avltree.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 26/06/22.
//

#include "avltree.hpp"

AVLNode *AVLTree::createNode(int key) {
  AVLNode *node = new AVLNode;
  node->data = key;
  node->parent = TNULL;
  node->left = TNULL;
  node->right = TNULL;
  node->height = 0;

  return node;
}

AVLTree::AVLTree() {
  TNULL = new AVLNode;
  TNULL->left = nullptr;
  TNULL->right = nullptr;
  root = TNULL;
  
}

AVLTree::~AVLTree() {
  while (root != nullptr) {
    remove(root->data);
  }
}

AVLNode *AVLTree::searchTreeHelper(AVLNode *node, int key) {
  if (node == nullptr || key == node->data) {
    return node;
  }

  if (key < node->data) {
    return searchTreeHelper(node->left, key);
  } else {
    return searchTreeHelper(node->right, key);
  }
}

AVLNode *AVLTree::searchTree(int key) {
  return searchTreeHelper(root, key);
}

void AVLTree::insert(int key) {
  AVLNode *node = createNode(key);

  AVLNode *parent = nullptr;
  AVLNode *current = root;

  while (current != TNULL) {
    parent = current;
    if (node->data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  node->parent = parent;
  if (parent == nullptr) {
    root = node;
  } else {
    if (node->data < parent->data) {
      parent->left = node;
    } else {
      parent->right = node;
    }
  }
  
  balance(node);

}

AVLNode *AVLTree::maximum(AVLNode *node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

void AVLTree::transplant(AVLNode *x, AVLNode *y) {
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->parent = x->parent;
}

void AVLTree::remove(int data) {
  AVLNode *node = searchTree(data);

  if (node == TNULL) {
    cout << "Key: " << data << " can't be found" << endl;
    return;
  }

  AVLNode *x, *y;
  y = node;

  if (node->left == TNULL) {
    x = node->right;
    transplant(node, node->right);
  } else if (node->right == TNULL) {
    x = node->left;
    transplant(node, node->left);
  } else {
    y = maximum(node->left);
    x = y->left;
    if (y->parent == node) {
      x->parent = y;
    } else {
      transplant(y, y->left);
      y->left = node->left;
      y->left->parent = y;
    }

    transplant(node, y);
    y->right = node->right;
    y->right->parent = y;
  }
  
  balance(node);
}

void AVLTree::printHelper(AVLNode *root, string indent, bool last) {
  if (root != TNULL) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "     ";
    } else {
      cout << "L----";
      indent += "|    ";
    }

    cout << root->data << "(" << root->height << ")" << endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}

void AVLTree::print() { printHelper(root, "", false); }

int AVLTree::height(AVLNode *t) {
  if (t == nullptr) {
    return -1;
  } else {
    return t->height;
  }
}

void AVLTree::balance(AVLNode *&t) {
  if (t != TNULL) {

    if (height(t->left) - height(t->right) > 1){
      if (height(t->left->left) >= height(t->left->right)){
          rotateWithLeftChild(t);
      }
      else {
        doubleWithLeftChild(t);
      }
    }
      
    else if (height(t->right) - height(t->left) > 1){
      if (height(t->right->right) >= height(t->right->left)) {
        rotateWithRightChild(t);
      } else {
        doubleWithRightChild(t);
      }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
  }
}

void AVLTree::rotateWithLeftChild(AVLNode *&k2) {
  AVLNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max(height(k2->left), height(k2->right)) + 1;
  k1->height = max(height(k1->left), k2->height) + 1;
  k2 = k1;
}

void AVLTree::rotateWithRightChild(AVLNode *&k1) {
  AVLNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max(height(k1->left), height(k1->right)) + 1;
  k2->height = max(height(k2->right), k1->height) + 1;
  k1 = k2;
}

void AVLTree::doubleWithLeftChild(AVLNode *&k3) {
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

void AVLTree::doubleWithRightChild(AVLNode *&k1) {
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

void AVLTree::removePostorderHelper(AVLNode* node) {
  if (node != TNULL) {
    removePostorderHelper(node->left);
    removePostorderHelper(node->right);
    
    delete node;
  }
}

void AVLTree::removePostorder(){
  removePostorderHelper(root);
}
