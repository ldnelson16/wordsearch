#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Input title, empty vector words, width, and height to function and it will command user to set up information for word search
void getinformation(string &title,vector<string> &words,int &width,int &height);

// Returns default dimensions when given no height and width
pair<int,int> defaultDimensions(const vector<string> &words);

// Returns amount of words given dimensions
pair <int,int> wordAmount(const int width,const int height);

#endif // INPUT_HPP