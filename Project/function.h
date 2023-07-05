#pragma once
#include"struct.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

void insert(trieNode*& root, string s, vector<string> meaning);

void standardWord(string& S);

void readFileToTree(trieNode*& root,trieNode*& rootDef, string direction);

void DeleteAWord(trieNode*& root, string word, int depth);

void DeleteAllTree(trieNode*& root);

void WriteDictionaryToFile(trieNode* root, string prefix, ofstream &fout);

bool search(trieNode* root, string s, vector<string>& ans);

void addToFavor(Stack& favor, string s);

void removeOutFavor(Stack& favor, string s);