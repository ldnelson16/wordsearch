#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "input.hpp"

using namespace std;

void getinformation(string &title,vector<string> &words,int &width,int &height) {
  cout << "You are creating a word search, please input the title of your word search." << endl;
  cin >> title;
  cout << "Your puzzle is titled " << title << endl << "What width do you want your puzzle? (If default, enter 0)(minimum 10)" << endl;
  cin >> width;
  while (width>0 && width <=10){
    cout << "Try again " << endl;
    cin >> width;
  }
  if (width==0) {
    height = 0;
  }
  else {
    cout << "What height do you want your puzzle? (cannot be default)(minimum 10)" << endl;
    cin >> height;
    while (height <=10){
      cout << "Try again " << endl;
      cin >> height;
    }
  }
  cout << "Now we will begin the process of inputting words . . . " << endl;
  cin.ignore();
  pair<int,int> maxwords = wordAmount(width,height);
  int bigwords = maxwords.first, smallwords =  maxwords.second;
  while ((maxwords.first+maxwords.second>words.size())){
    string word;
    cout << "Word: ";
    getline(cin,word);
    // check for invariants
    bool flag = false;
    for (int j=0;j<word.size();++j){
      if (static_cast<int>(word[j])<97||static_cast<int>(word[j])>122){
        flag=true;
        break;
      }
    }
    if (flag) {
      cout << "Non lower-case letter character detected in word. Try again" << endl;
      continue;
    }
    if (word.size()>min(width,height)&&word.size()<max(width,height)&&bigwords>0){
      --bigwords;
      words.push_back(word);
      continue;
    }
    else if (word.size()>max(width,height)){
      cout << "Inputted word was too large. Try again" << endl;
    }
    else if (word.size()<min(width,height)&&(bigwords>0||smallwords>0)&&word.size()>1){
      if (smallwords>0){--smallwords;}
      else {--bigwords;}
      words.push_back(word);
      continue;
    }
    else {
      cout << "Inputted word was too small. Try again" << endl;
    }
  }
  for (int i=0;i<words.size();++i){
    cout << words[i] << endl;
  }
}

pair <int,int> wordAmount(const int width, const int height){
  pair <int,int> amt = {min(width,height) - abs(width-height)/5, abs(width-height)/3};
  return amt;
}

pair<int,int> defaultDimensions(vector<string> &words){
  pair <int,int> dimensions;
  return dimensions;
}