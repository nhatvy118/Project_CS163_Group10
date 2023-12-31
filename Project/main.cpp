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
trieNode* Emoji = nullptr;
trieNode* EmojiDef = nullptr;
trieNode* Slang = nullptr;
trieNode* SlangDef = nullptr;
Node* favor[5] = { nullptr };
Node* history[10] = { nullptr };
int main() {
	const int screenW = 1512;
	const int screenH = 982;

	readFileToTree(VieEng, VieEngDef, "VieEng.txt");
	readFileToTree(EngEng, EngEngDef, "EngEng.txt");
	readFileToTree(EngVie, EngVieDef, "EngVie.txt");
	readFileToTree(Emoji, EmojiDef, "Emoji.txt");
	readFileToTree(Slang, SlangDef, "Slang.txt");
	readNode2File(favor, "Favor.txt");
	readNode2File(history, "History.txt");

	InitWindow(screenW, screenH, "Group 10 Dictionary");
	WaitingPage(screenW, screenH, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);

	return 0;
}

