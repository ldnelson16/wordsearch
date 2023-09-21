#ifndef CREATOR_HPP
#define CREATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// create word search
// REQUIRES: list of words, width, height
// RETURNS: two-dimensional matrix of letters
vector<vector<char>> createWordSearch(vector<string> &words, const int width, const int height);

// 

#endif // CREATOR_HPP