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

void readFileToTree(trieNode*& root, trieNode*& rootDef, string direction) {
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
		while (i < s.size()) {
			if (s[i] != '|') tmp += s[i];
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
		insert(root, str, meaning);
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
void add(Node*& pHead, string s) {
	if (!pHead) {
		pHead = new Node;
		pHead->data = s;
		return;
	}
	Node* tmp = pHead;
	Node* pNew = new Node;
	pNew->data = s;
	pHead = pNew;
	pNew->pNext = tmp;
	return;
}


void remove(Node*& pHead, string s) {
	Node* cur = pHead;
	if (cur == nullptr) {
		return;
	}

	if (pHead->data == s) {
		cur = pHead;
		pHead = pHead->pNext;
		delete cur;
		return;
	}
	while (cur->pNext) {
		if (cur->pNext->data == s) {
			Node* tmp = cur->pNext;
			cur->pNext = cur->pNext->pNext;
			delete tmp;
			break;
		}
		cur = cur->pNext;
	}
}

vector<string> viewList(Node* pHead) {
	Node* cur = pHead;
	vector<string> ans;
	ans.resize(0);
	if (cur == nullptr) return ans;
	while (cur) {
		ans.push_back(cur->data);
		cur = cur->pNext;
	}
	return ans;
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
trieNode* find(trieNode* root, string s) {
	standardWord(s);
	if (!root) return nullptr;
	for (auto x : s) {
		if (root->c[int(x) - 32]) {
			root = root->c[int(x) - 32];
		}
		else {
			return nullptr;
		}
	}
	return root;
}
void rcmFunc(trieNode* root, string s, vector<string>& ans) {
	if (!root) {
		return;
	}
	if (root->isEnd) {
		ans.push_back(s);
	}
	for (int i = 0; i < 96; ++i) {
		if (root->c[i]) {
			char tmp = char(i + 32);
			rcmFunc(root->c[i], s + tmp, ans);
		}
	}
}

bool checkExistFavor(Node* favor, string s) {
	while (favor) {
		if (favor->data == s) {
			return true;
		}
		favor = favor->pNext;
	}
	return false;
}

bool checkExistHis(Node* his, string s) {
	if (!his) return false;
	Node* tmp = his;
	if (his->data == s) {
		return true;
	}
	while (tmp->pNext) {
		if (tmp->pNext->data == s) {
			return true;
		}
		tmp = tmp->pNext;
	}
	return false;
}


