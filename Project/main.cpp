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
	trieNode* emoji = nullptr;
	trieNode* emojiDef = nullptr;
	trieNode* slang = nullptr;
	trieNode* slangDef = nullptr;

	InitWindow(screenW, screenH, "Group 10 Dictionary");
	//HomePage(screenW, screenH);
	WaitingPage(screenW, screenH);
	FavoriteListPage(screenW, screenH);

	return 0;
}