#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
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

Path Puzzle::findSpot(string word, int index){
  srand(static_cast<unsigned>(time(nullptr)));
  int len = word.size();
  int start_r,start_c;
  bool back;
  bool dir;
  if (index==0){
    back = false;
    if (rand()%2 == 0){
      if (rand()%2 == 0){
        cout << "Row-forward" << endl;
        start_c = rand()%(puzzleWidth()-len);
        start_r = rand()%(puzzleHeight());
        dir = 0;
      }
      else {
        cout << "Row-backwards" << endl;
        start_c = puzzleWidth()-1-rand()%(puzzleWidth()-len);
        start_r = rand()%(puzzleHeight());
        dir = 0;
        back = true;
      }
    }
    else {
      if (rand()%2 == 0){
        cout << "Column-forward" << endl;
        start_r = rand()%(puzzleHeight()-len);
        start_c = rand()%(puzzleWidth());
        dir = 1;
      }
      else {
        cout << "Column-backward" << endl;
        start_r = puzzleHeight()-1-rand()%(puzzleHeight()-len);
        start_c = rand()%(puzzleWidth());
        dir = 1;
        back = true;
      }
    }
  }
  else {
    // complex algorithm
  }
  // add word to grid
  Path path{word,start_r,start_c,dir,back};
  return path;
}

void Puzzle::addWord(const Path path){
  if (path.dir==0){ // along a single row
    if (path.back==false){ // not backwards
      for (int i=path.start_c;i<path.start_c+path.word.size();++i){
        cout << i << "," << path.start_r << endl;
        *gridAt(path.start_r,i) = path.word[i-path.start_c];
      }
    }
    else { // backwards
      for (int i=path.start_c;i>path.start_c-path.word.size();--i){
        cout << i << "," << path.start_r << endl;
        *gridAt(path.start_r,i) = path.word[path.start_c-i];
      }
    }
  }
  else { // along a single column
    if (path.back==false){ // not backwards
      for (int i=path.start_r;i<path.start_r+path.word.size();++i){
        cout << path.start_c << "," << i << endl;
        *gridAt(i,path.start_c) = path.word[i-path.start_r];
      }
    }
    else { // backwards
      for (int i=path.start_r;i>path.start_r-path.word.size();--i){
        cout << path.start_c << "," << i << endl;
        *gridAt(i,path.start_c) = path.word[path.start_r-i];
      }
    }
  }
}

Puzzle createWordSearch(string title, vector<string> &words, const int width, const int height){
  Puzzle wordsearch(title,width,height);
  wordsearch.fillBlanks();
  Path path = wordsearch.findSpot(words[0],0);
  cout << path.word << path.start_c << path.start_r << path.dir << path.back << endl;
  wordsearch.addWord(path);
  return wordsearch;
}