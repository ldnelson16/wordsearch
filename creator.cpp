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
  int len = word.size();
  bool back;
  bool dir;
  int start_r = rand() % puzzleHeight();
  int start_c = rand() & puzzleWidth();
  for (int r=start_r;r<puzzleHeight()+start_r;++r){
    for (int c=start_c; c<puzzleWidth()+start_c;++c){
      int real_r = r % puzzleHeight();
      int real_c = c % puzzleWidth();
      cout << "Checking at position " << r << ", " << c << endl;
      // check if word will fit in both directions
      bool random_dim1 = rand()%2;
      bool random_dim2 = rand()%2;
      if (checkPath(Path{word,real_r,real_c,random_dim1,random_dim2})){
        cout << "Found path row-wise,forwards at " << r << ", " << c << endl;
        return Path{word,real_r,real_c,random_dim1,random_dim2};
      }
      else if (checkPath(Path{word,real_r,real_c,random_dim1,!random_dim2})){
        cout << "Found path row-wise,backwards at " << r << ", " << c << endl;
        return Path{word,real_r,real_c,random_dim1,!random_dim2};
      }
      else if (checkPath(Path{word,real_r,real_c,!random_dim1,random_dim2})){
        cout << "Found path column-wise,forwards at " << r << ", " << c << endl;
        return Path{word,real_r,real_c,!random_dim1,random_dim2};
      }
      else if (checkPath(Path{word,real_r,real_c,!random_dim1,!random_dim2})){
        cout << "Found path column-wise,backwards at " << r << ", " << c << endl;
        return Path{word,real_r,real_c,!random_dim1,!random_dim2};
      }
    }
  }
  // if nothing is found
  cout << "couldn't find a spot for " << word << endl;
  return Path{word,-1,-1,0,0};
}

bool Puzzle::checkPath(const Path path){
  cout << "Checking path" << endl;
  if (!path.dir){
    cout << "Row-wise" << endl;
    if (path.back){
      cout << "Backwards" << endl;
      // row-wise and backwards
      if (path.start_c-static_cast<int>(path.word.size())+1>=0) {
        cout << "Word in bounds" << endl;
        cout << path.word << endl;
        // check if each cell allows word
        cout << path.start_c << "to" << path.start_c-static_cast<int>(path.word.size())+1 << endl;
        for (int c=path.start_c;c>path.start_c-static_cast<int>(path.word.size());--c){
          // check that each grid spot is either blank or correct letter
          cout << path.start_c << "Checking between indexes at word " << path.start_c-c << endl;
          cout << "Checking between " << *gridAt(path.start_r,c) << " and " << path.word[path.start_c-c] << endl;
          if (!(*gridAt(path.start_r,c)=='-' || *gridAt(path.start_r,c)==path.word[path.start_c-c])){
            return false;
          }
        }
      }
      else {return false;}
    }
    else {
      cout << "Forwards" << endl;
      // row-wise and forwards
      if (path.start_c+static_cast<int>(path.word.size())-1<puzzleWidth()){
        cout << "Word in bounds" << endl;
        // check if each cell allows word
        for (int c=path.start_c;c<path.start_c+static_cast<int>(path.word.size());++c){
          // check that each grid spot is either blank or correct letter
          cout << path.start_c << "Checking between indexes at word " << c-path.start_c << endl;
          cout << "Checking between " << *gridAt(path.start_r,c) << " and " << path.word[c-path.start_c] << endl;
          cout << (*gridAt(path.start_r,c)=='-') << " " << (*gridAt(path.start_r,c)==path.word[c-path.start_c]) << endl;
          if (!(*gridAt(path.start_r,c)=='-' || *gridAt(path.start_r,c)==path.word[c-path.start_c])){
            return false;
          }
        }
      }
      else {return false;}
    }
  }
  else {
    cout << "Column-wise" << endl;
    if (path.back) {
      // column-wise and backwards
      if (path.start_r-static_cast<int>(path.word.size())+1>=0){
        cout << "Word in bounds" << endl;
        // check if each cell allows word
        for (int r=path.start_r;r>path.start_r-static_cast<int>(path.word.size());--r){
          // check that each grid spot is either blank or correct letter
          if (!(*gridAt(r,path.start_c)=='-' || *gridAt(r,path.start_c)==path.word[path.start_r-r])){
            return false;
          }
        }
      }
      else {return false;}
    }
    else {
      // column-wise and forwards
      if (path.start_r+static_cast<int>(path.word.size())-1<puzzleHeight()){
        cout << "Word in bounds" << endl;
        // check if each cell allows word
        for (int r=path.start_r;r<path.start_r+static_cast<int>(path.word.size());++r){
          // check that each grid spot is either blank or correct letter
          if (!(*gridAt(r,path.start_c)=='-' || *gridAt(r,path.start_c)==path.word[r-path.start_r])){
            return false;
          }
        }
      }
      else {return false;}
    }
  }
  return true;
}

void Puzzle::addWord(const Path path){
  if (path.dir==0){ // along a single row
    if (path.back==false){ // not backwards
      for (int i=path.start_c;i<path.start_c+static_cast<int>(path.word.size());++i){
        cout << i << "," << path.start_r << endl;
        *gridAt(path.start_r,i) = path.word[i-path.start_c];
      }
    }
    else { // backwards
      for (int i=path.start_c;i>path.start_c-static_cast<int>(path.word.size());--i){
        cout << i << "," << path.start_r << endl;
        *gridAt(path.start_r,i) = path.word[path.start_c-i];
      }
    }
  }
  else { // along a single column
    if (path.back==false){ // not backwards
      for (int i=path.start_r;i<path.start_r+static_cast<int>(path.word.size());++i){
        cout << path.start_c << "," << i << endl;
        *gridAt(i,path.start_c) = path.word[i-path.start_r];
      }
    }
    else { // backwards
      for (int i=path.start_r;i>path.start_r-static_cast<int>(path.word.size());--i){
        cout << path.start_c << "," << i << endl;
        *gridAt(i,path.start_c) = path.word[path.start_r-i];
      }
    }
  }
}

void Puzzle::fillRandoms() {
  cout << "Filling grid with random characters" << endl;
  for (int r=0;r<puzzleHeight();++r){
    for (int c=0;c<puzzleWidth();++c){
      if (*gridAt(r,c)=='-'){
        // if a char in a grid is still uninitialize, give it a random character
        *gridAt(r,c) = static_cast<char>(rand()%26+97);
      }
    }
  }
}

Puzzle createWordSearch(string title, vector<string> &words, const int width, const int height){
  srand(static_cast<unsigned>(time(nullptr)));
  Puzzle wordsearch(title,width,height);
  wordsearch.fillBlanks();
  for (int i=0;i<words.size();++i) {
    cout << "Finding spot for " << words[i] << endl;
    wordsearch.addWord(wordsearch.findSpot(words[i],i));
  }
  wordsearch.fillRandoms();
  return wordsearch;
}