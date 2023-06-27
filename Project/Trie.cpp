#include<iostream>
#include"function.h"
#include"struct.h"
#include<string>
#include<vector>

using namespace std;

void standardWord(string& S) {
	int sz = S.size();
	for (int i = 0; i < sz; ++i) {
		if (S[i] >= 65 && S[i] <= 90)
			S[i] = char(S[i] + 32);
	}
}
void insert(trieNode*& root, string s, vector<string> meaning) {
	if (!root) {
		root = new trieNode();
	}
	standardWord(s);
	trieNode* cur = root;
	for (auto x : s) {
		if (!cur->c[int(x) - 'a']) {
			cur->c[int(x) - 'a'] = new trieNode();
		}
		cur = cur->c[int(x) - 'a'];
	}
	cur->isEnd = true;
	for (auto x : meaning) {
		standardWord(x);
		cur->mean.push_back(x);
	}
}