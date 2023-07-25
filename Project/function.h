#pragma once
#include"struct.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <random>

using namespace std;

void insert(trieNode*& root, string s, vector<string> meaning);

void standardWord(string& S);

void readFileToTree(trieNode*& root, trieNode*& rootDef, string direction);

void DeleteAWord(trieNode*& root, string word, int depth, vector<string>& meaning);

void DeleteAllTree(trieNode*& root);

void WriteDictionaryToFile(trieNode* root, string prefix, ofstream& fout);

bool search(trieNode* root, string s, vector<string>& ans);

void random1Word4Def(trieNode* root, string& true_word, string& true_def, vector<string>& wrong_def);

bool updateDef(trieNode*& root, string s, int t, string def);

bool compare(string s1, string s2);

void add(Node*& pHead, string s);

void remove(Node*& pHead, string s);

vector<string> viewList(Node* pHead);

trieNode* find(trieNode* root, string s);

void rcmFunc(trieNode* root, string s, vector<string>& ans);

vector <string> divideString(string def, int part);

void readNode2File(Node*& head, string path);

void writeNode2File(Node* head, ofstream& fout);

bool checkExistFavor(Node* favor, string s);

bool checkExistHis(Node* his, string s);
