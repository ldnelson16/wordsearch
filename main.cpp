#include "input.hpp"
#include "creator.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string title;
  vector<string> words;
  int width,height;
  getinformation(title,words,width,height);
  Puzzle wordsearch = createWordSearch(title,words,width,height);
  wordsearch.gridPrint();
}