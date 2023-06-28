#include"function.h"

void DeleteAWord(trieNode*& root, string word, int depth) {
	if (root == nullptr)
		return;
	if (depth == word.size()) {
		if (root->isEnd) {
			root->isEnd = false;
			root->mean.clear();
		}
		bool hasChild = false;
		for (trieNode* i : root->c)
			if (i != nullptr) {
				hasChild = true;
				break;
			}
		if (!hasChild) {
			delete root;
			root = nullptr;
		}
		return;
	}
	int index = word[depth] - 32;
	DeleteAWord(root->c[index], word, depth + 1);
	bool hasChild = false;
	for (trieNode* i : root->c)
		if (i != nullptr) {
			hasChild = true;
			break;
		}
	if (!hasChild && !root->isEnd) {
		delete root;
		root = nullptr;
	}
}

void DeleteAllTree(trieNode*& root) {
	if (root == nullptr)
		return;
	for (int i = 0; i < alphabet; i++)
		DeleteAllTree(root->c[i]);
	delete root;
	root = nullptr;
}

void WriteDictionaryToFile(trieNode* root, string prefix, ofstream& fout) {
	if (root == nullptr)
		return;
	if (root->isEnd) {
		fout << prefix << "`";
		int numOfMean = root->mean.size();
		for (int i = 0; i < numOfMean; ++i) {
			fout << root->mean[i];
			if (i != numOfMean - 1)
				fout << "|";
		}
		fout << endl;
	}
	for (int i = 0; i < alphabet; i++)
		if (root->c[i] != nullptr) {
			char temp = i + 32;
			WriteDictionaryToFile(root->c[i], prefix + temp, fout);
		}
}