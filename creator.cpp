#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "creator.hpp"

using namespace std;

Puzzle::Puzzle(const string name, const int width, const int height):name(name),width(width),height(height) {}

int Puzzle::puzzleWidth(){
  return width;
}

int Puzzle::puzzleHeight(){
  return height;
}

char* Puzzle::gridAt(const int r, const int c){
  return grid+r*puzzleWidth()+c;
}

void Puzzle::gridPrint(){
  for (int r=0;r<puzzleHeight();++r){
    for (int c=0;c<puzzleWidth();++c){
      cout << *gridAt(r,c) << " ";
    }
    cout << endl;
  }
}

void Puzzle::fillBlanks(){
  for (int r=0;r<puzzleHeight();++r){
    for (int c=0;c<puzzleWidth();++c){
      *gridAt(r,c) = '-';
    }
  }
}

Puzzle createWordSearch(string title, vector<string> &words, const int width, const int height){
  Puzzle wordsearch(title,width,height);
  wordsearch.fillBlanks();
  return wordsearch;
}