#pragma once
#include"struct.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

void insert(trieNode*& root, string s, vector<string> meaning);
void standardWord(string& S);

void insert(trieNode*& root, string s, string meaning);

void DeleteAWord(trieNode*& root, string word, int depth);

void DeleteAllTree(trieNode*& root);

void WriteDictionaryToFile(trieNode* root, string prefix, ofstream &fout);
