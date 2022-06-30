//
//  main.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

#include "rbtree.hpp"
#include "avltree.hpp"

using namespace std;

int readFile(int* array, int size) {
  string folder = "./inputs/";
  string extension = ".txt";
  string filename = folder + to_string(size) + extension;

  ifstream file;
  file.open(filename);

  if (!file.is_open()) {
    throw runtime_error("Error opening file.");
  }

  for (int i = 0; file >> array[i]; i++) {
    if (i == size) {
      break;
    }
  }

  file.close();
  return 0;
}

int removeRb(int size) {
  RBTree *rbTree = new RBTree();
  int array[size];

  try {
    readFile(array, size);

    for (int i = 0; i < size; i++) {
      rbTree->insert(array[i]);
    }

    clock_t ticks[2];
    ticks[0] = clock();

    for (int i = 0; i < size; i++) {
      rbTree->remove(array[i]);
    }

    ticks[1] = clock();
    double time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time: %g ms.", time);

  } catch (const runtime_error& error) {
    cerr << "Error: " << error.what() << endl;
  }

  delete rbTree;
  return 0;
}

int removeAvl(int size) {
  AVLTree *avlTree = new AVLTree();
  int array[size];

  try {
    readFile(array, size);
    
    for (int i = 0; i < size; i++) {
      avlTree->insert(array[i]);
    }

    clock_t ticks[2];
    ticks[0] = clock();

    for (int i = 0; i < size; i++) {
      avlTree->remove(array[i]);
    }

    ticks[1] = clock();
    double time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time: %g ms.", time);

  } catch (const runtime_error& error) {
    cerr << "Error: " << error.what() << endl;
  }
  
  avlTree->print();

  delete avlTree;
  return 0;
}

int main() {
//  removeRb(250000);
  removeAvl(250000);
  
  
  cout << "Done." << endl;
  return 0;
}
