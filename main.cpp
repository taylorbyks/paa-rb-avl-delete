//
//  main.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include "rbtree.hpp"

using namespace std;

int readFile(int *array, int size) {
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
  int array[size];
  
  try {
    readFile(array, size);
    
    for (int i = 0; i < size; i++) {
      cout << array[i] << endl;
    }
    
  } catch (const runtime_error& error) {
    cerr << "Error: " << error.what() << std::endl;
  }

  return 0;
}

int main() {
  RbTree rbTree;
  // rbTree.print();

  removeRb(50);

  cout << "Done." << endl;

  return 0;
}
