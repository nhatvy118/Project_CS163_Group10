#include<iostream>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include "raylib.h"
using namespace std;

int main() {
	const int screenW = 1512;
	const int screenH = 982;

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

	
	readFileToTree(VieEng,VieEngDef, "VieEng.txt");
	readFileToTree(EngEng,EngEngDef, "EngEng.txt");
	readFileToTree(EngVie,EngVieDef, "EngVie.txt");
	readFileToTree(Emoji, EmojiDef, "Emoji.txt");
	readFileToTree(Slang, SlangDef, "Slang.txt");
	
	//vector<string> ans;
	//ans.resize(0);
	//if (search(Emoji, "*<:-)", ans)) {
	//	for (auto x : ans) {
	//		cout << x << endl;
	//	}
	//}
	//else {
	//	cout << "No";
	//}
	//

	InitWindow(screenW, screenH, "Group 10 Dictionary");
	//HomePage(screenW, screenH);
	WaitingPage(screenW, screenH);
	FavoriteListPage(screenW, screenH);

	return 0;
}