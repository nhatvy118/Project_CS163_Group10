#pragma once
#include<iostream>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include "raylib.h"
using namespace std;

	trieNode* VieEng = nullptr;
	trieNode* EngVie = nullptr;
	trieNode* EngEng = nullptr;
	trieNode* VieEngDef = nullptr;
	trieNode* EngVieDef = nullptr;
	trieNode* EngEngDef = nullptr;
	trieNode* emoji = nullptr;
	trieNode* emojiDef = nullptr;
	trieNode* slang = nullptr;
	trieNode* slangDef = nullptr;

int main() {
	const int screenW = 1512;
	const int screenH = 982;
	
<<<<<<< Updated upstream
	//readFileToTree(VieEng,VieEngDef, "VieEng.txt");
	//readFileToTree(EngEng,EngEngDef, "EngEng.txt");
	//readFileToTree(EngVie,EngVieDef, "EngVie.txt");
	
	/*vector<string> ans;
	ans.resize(0);
	if (search(VieEngDef, "Albania", ans)) {
		for (auto x : ans) {
			cout << x << endl;
		}
	}
	else {
		cout << "No";
	}*/
=======

	readFileToTree(VieEng, VieEngDef, "VieEng.txt");
	readFileToTree(EngEng, EngEngDef, "EngEng.txt");
	readFileToTree(EngVie, EngVieDef, "EngVie.txt");
	readFileToTree(Emoji, EmojiDef, "Emoji.txt");
	readFileToTree(Slang, SlangDef, "Slang.txt");

	//vector<string> ans;
	//ans.resize(0);
	//if (search(EngEngDef, "of Abandon", ans)) {
	//	for (auto x : ans) {
	//		cout << x << endl;
	//	}
	//}
	//else {
	//	cout << "No";
	//}
>>>>>>> Stashed changes
	

	InitWindow(screenW, screenH, "Group 10 Dictionary");
	//HomePage(screenW, screenH);
	WaitingPage(screenW, screenH, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);

	return 0;
}