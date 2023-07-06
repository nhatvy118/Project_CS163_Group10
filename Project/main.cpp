#pragma once
#include<iostream>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include "raylib.h"
using namespace std;
/*

	trieNode* VieEng = nullptr;
	trieNode* EngVie = nullptr;
	trieNode* EngEng = nullptr;
	trieNode* VieEngDef = nullptr;
	trieNode* EngVieDef = nullptr;
	trieNode* EngEngDef = nullptr;
	trieNode* Emoji = nullptr;
	trieNode* EmojiDef = nullptr;
	trieNode* Slang = nullptr;
	trieNode* SlangDef = nullptr;

int main() {
	const int screenW = 1512;
	const int screenH = 982;
	

	readFileToTree(VieEng, VieEngDef, "VieEng.txt");
	readFileToTree(EngEng, EngEngDef, "EngEng.txt");
	readFileToTree(EngVie, EngVieDef, "EngVie.txt");
	readFileToTree(Emoji, EmojiDef, "Emoji.txt");
	readFileToTree(Slang, SlangDef, "Slang.txt");

	

	InitWindow(screenW, screenH, "Group 10 Dictionary");
	//HomePage(screenW, screenH);
	WaitingPage(screenW, screenH, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);
	
	
	return 0;
}*/
int main() {
	trieNode* root = nullptr, * rootDef = nullptr;
	readFileToTree(root, rootDef, "VieEng.txt");
	vector<string> ans;
	if (search(root, "Anh My", ans)) {
		for (string i : ans)
			cout << i << endl;
		cout << endl;
	}
	else {
		cout << "not found" << endl;
	}
	ans.clear();
	DeleteAWord(root, "Anh My", 0);
	if (search(root, "Anh My", ans)) {
		for (string i : ans)
			cout << i << endl;
		cout << endl;
	}
	else {
		cout << "not found" << endl;
	}
	DeleteAllTree(root);
	DeleteAllTree(rootDef);
}