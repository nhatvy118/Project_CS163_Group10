#include "function.h"

void delete(trieNode*& root, string word, int depth) {
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
	delete(root->c[index], word, depth + 1);
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