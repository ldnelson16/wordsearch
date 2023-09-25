#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "input.hpp"

using namespace std;

pair<int,int> defaultDimensions(vector<string> &words){
  int maxlen = 0;
  for(int i=0;i<words.size();++i){
    if(words[i].size()>maxlen){
      maxlen = words[i].size();
    }
  }
  pair <int,int> dimensions = {maxlen,words.size()*3/2};
  return dimensions;
}

void getinformation(string &title,vector<string> &words,int &width,int &height) {
  cout << "You are creating a word search, please input the title of your word search." << endl;
  cin >> title;
  cout << "Your puzzle is titled " << title << endl << "What width do you want your puzzle? (If default, enter 0)(minimum 10)" << endl;
  cin >> width;
  while (width!=0 && (width <10 || width > 25)){
    cout << "Try again " << endl;
    cin >> width;
  }
  if (width==0) {
    height = 0;
  }
  else {
    cout << "What height do you want your puzzle? (cannot be default)(minimum 10,maximum 25)" << endl;
    cin >> height;
    while (height <10 && height>25){
      cout << "Try again " << endl;
      cin >> height;
    }
  }
  cout << "Now we will begin the process of inputting words . . . " << endl;
  cin.ignore();
  pair<int,int> maxwords = wordAmount(width,height);
  int bigwords = maxwords.first, smallwords =  maxwords.second;
  if (width!=0) {
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
      if (word.size()>min(width,height)&&word.size()<max(width,max(height,25))&&bigwords>0){
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
  }
  else {
    while (true){
      string word;
      cout << "Word (type 'BREAK' to break): ";
      getline(cin,word);
      // check for invariants
      bool flag = false;
      if(word=="BREAK"){
        break;
      }
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
      if (word.size()>1&&word.size()<20){
        words.push_back(word);
      }
      else {
        cout << "Inputted word was too small or large (bounds 1-20 chars). Try again" << endl;
      }
    }
    pair <int,int> dims = defaultDimensions(words);
    width = dims.first;
    height = dims.second;
  }
  cout << "Words have been compiled. Now creating a word search " << width << " x " << height << endl;
}

pair <int,int> wordAmount(const int width, const int height){
  pair <int,int> amt = {min(width,height)- 1 - abs(width-height)/5, max(abs(width-height)/3,0)};
  return amt;
}

