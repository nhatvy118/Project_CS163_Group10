#include<iostream>
#include"function.h"
#include"struct.h"
#include<string>
#include<vector>

using namespace std;

void insert(trieNode*& root, string s, string meaning) {
	if (!root) {
		root = new trieNode();
	}
	trieNode* cur = root;
	for (auto c : s) {

	}
}