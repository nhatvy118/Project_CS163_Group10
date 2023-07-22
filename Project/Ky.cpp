#include"function.h"

void DeleteAWord(trieNode*& root, string word, int depth, vector<string>& meaning) {
	if (root == nullptr)
		return;
	if (depth == word.size()) {
		if (root->isEnd) {
			root->isEnd = false;
			meaning = root->mean;
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
	int index = tolower(word[depth]) - 32;
	DeleteAWord(root->c[index], word, depth + 1, meaning);
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

void random1Word4Def(trieNode* root, string& true_word, string& true_def, vector<string>& wrong_def) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 95);
	int count = 0;
	while (count != 4) {
		trieNode* node = root;
		string temp = "";
		while (node != nullptr) {
			int rand;
			do {
				rand = dist(gen);

			} while (node->c[rand] == nullptr);
			node = node->c[rand];
			temp.push_back(rand + 32);
			if (node->isEnd) {
				if (count == 0) {
					true_word = temp;
					true_def = node->mean[0];
					count++;
				}
				else {
					bool duplicate = false;
					for (string x : wrong_def)
						if (x == node->mean[0]) {
							duplicate = true;
							break;
						}
					if (!duplicate) {
						wrong_def[count - 1] = node->mean[0];
						count++;
					}
				}
				break;
			}
		}
	}
}

vector <string> divideString(string def) {
	vector <string> save;
	int i = 0;
	int j = 130;
	string tmp;
	while (j < def.size()) {
		while (def[j] != ' ') {
			--j;
		}
		tmp = def.substr(i, j - i);
		save.push_back(tmp);
		i = j + 1;
		j += 130;
	}
	j -= 130;
	tmp = def.substr(j + 1, def.size());
	save.push_back(tmp);

	return save;
}

void readNode2File(Node*& head, string path) {
	ifstream fin;
	fin.open("../Dataset/" + path);
	if (!fin.good()) {
		cout << "Read file error." << endl;
		return;
	}
	string line;
	Node* cur = nullptr;
	while (getline(fin, line)) {
		add(head, line);
	}
	fin.close();
}

void writeNode2File(Node* head, ofstream& fout) {
	if (!head)
		return;
	writeNode2File(head->pNext, fout);
	fout << head->data << endl;
}