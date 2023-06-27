#pragma once
#include"struct.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

void insert(trieNode*& root, string s, vector<string> meaning);
void standardWord(string& S);