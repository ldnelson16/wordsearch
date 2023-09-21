#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Input title, empty vector words, width, and height to function and it will command user to set up information for word search
void getinformation(string &title,vector<string> &words,int &width,int &height);
pair<int,int> defaultDimensions(vector<string> &words);
pair <int,int> wordAmount(const int width,const int height);

#endif // INPUT_HPP