#ifndef CREATOR_HPP
#define CREATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int MAX_WIDTH = 25;
const int MAX_HEIGHT = 25;

struct Path {
  string word;
  int start_r;
  int start_c;
  bool dir;
  bool back;
};

class Puzzle {
  public: 
    // Puzzle constructor
    Puzzle(const string name, const int width, const int height);
    // Fills puzzle with blanks ('-')
    void fillBlanks();
    // Get puzzle width
    int puzzleWidth();
    // Get puzzle height
    int puzzleHeight();
    // Get Ptr to grid value at r,c
    char* gridAt(const int r, const int c);
    // Prints grid to terminal
    void gridPrint();
    // Finds spot on grid
    Path findSpot(string word, int index);
    // Adds word to grid
    void addWord(const Path path);
    // Check if word can fit in a given path
    bool checkPath(const Path path);
    // Fill finished grid with random letters
    void fillRandoms();
  private: 
    string name;
    int width,height;
    char grid[MAX_WIDTH * MAX_HEIGHT];
};


// create word search
// REQUIRES: list of words, width, height
// RETURNS: two-dimensional matrix of letters
Puzzle createWordSearch(string title,vector<string> &words, const int width, const int height);

// 

#endif // CREATOR_HPP