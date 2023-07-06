#include<iostream>
#include"function.h"
#include"struct.h"
#include<string>
#include<vector>
#include<fstream>

using namespace std;

const long long hashMod = (long long)(1e15 + 9);
const int prime = 31;

bool compare(string s1, string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i]) return false;
	}
	return true;
}
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
		if (!cur->c[int(x) - 32]) {
			cur->c[int(x) - 32] = new trieNode();
		}
		cur = cur->c[int(x) - 32];
	}
	cur->isEnd = true;
	for (auto x : meaning) {
		standardWord(x);
		bool ok = true;
		for (string st : cur->mean) {
			if (compare(st, x)) {
				ok = false;
				break;
			}
		}
		if (ok) cur->mean.push_back(x);
	}
}

void readFileToTree(trieNode*& root,trieNode*& rootDef, string direction) {
	ifstream fin;
	fin.open("../Dataset/" + direction);
	string s = "";
	while (getline(fin, s)) {
		string str = s.substr(0, s.find('`'));
		vector<string> meaning;
		int i = s.find('`') + 1;
		s += '|';
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
		vector<string> word;
		word.resize(0);
		word.push_back(str);
		insert(root, str,meaning);
		for (auto x : meaning) {
			insert(rootDef, x, word);
		}
	}
	fin.close();
}

bool search(trieNode* root, string s, vector<string>& ans) {
	trieNode* cur = root;
	standardWord(s);
	if (!root) return false;
	for (auto x : s) {
		if (cur->c[int(x) - 32]) {
			cur = cur->c[int(x) - 32];
		}
		else {
			return false;
		}
	}
	if (cur->isEnd) {
		for (auto x : cur->mean) {
			standardWord(x);
			ans.push_back(x);
		}
		return true;
	}
	return false;
}


void add(Stack& name, string s) {
	name.push(s);
	return;
}

void remove(Stack& name, string s) {
	name.removeNode(s);
	return;
}



bool updateDef(trieNode*& root, string s, int t, string def) {
	trieNode* cur = root;
	standardWord(s);
	standardWord(def);
	if (!root) return false;
	for (auto x : s) {
		if (cur->c[int(x) - 32]) {
			cur = cur->c[int(x) - 32];
		}
		else {
			return false;
		}
	}
	if (cur->isEnd) {
		if (t > cur->mean.size() - 1) {
			return false;
		}
		bool ok = true;
		for (int i = 0; i < cur->mean.size(); ++i) {
			if (compare(cur->mean[i], def) && i != t) {
				ok = false;
				break;
			}
		}
		if (ok) cur->mean[t] = def;
		return true;
	}
	return false;
}