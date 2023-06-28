#include<iostream>
#include"function.h"
#include"struct.h"
#include<string>
#include<vector>
#include<fstream>

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
void readFileToTree(trieNode* root, string direction) {
	ifstream fin;
	fin.open("../Dataset/" + direction);
	string s = "";
	while (getline(fin, s)) {
		string str = s.substr(0, s.find('`'));
		vector<string> meaning;
		int i = s.find('`') + 1;
		int sz = s.size();
		meaning.resize(0);
		string tmp = "";
		while (i < s.size()){
			if (s[i]!='|') tmp += s[i];
			else {
				if (tmp.size() != 0) {
					meaning.push_back(tmp);
					tmp = "";
				}
			}
			i++;
		}
		insert(root, str,meaning);
	}
	fin.close();
}