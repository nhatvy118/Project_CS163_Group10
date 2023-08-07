#include <raylib.h>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include <string>

void WaitingPage(const int screenWidth, const int screenHeight, trieNode*& VieEng, trieNode*& EngVie, trieNode*& EngEng, trieNode*& VieEngDef, trieNode*& EngVieDef, trieNode*& EngEngDef, trieNode*& Emoji, trieNode*& EmojiDef, trieNode*& Slang, trieNode*& SlangDef, Node* favor[], Node* history[])
{
	// Set up the page
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };
	////---------------------------------------------------------------------------------------------------
	// Set up components
	Texture2D logo2 = LoadTexture("../resources/School Logo2.png");
	Texture2D DrawStartBtn = LoadTexture("../resources/StartBtn.png");
	NewPageButton StartBtn;
	StartBtn.button = { 655,700,200,100 };
	////---------------------------------------------------------------------------------------------------

	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();

		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, navy);
		DrawTexture(logo2, 611, 218, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 629,537 }, 60, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 644,611 }, 32, 0, white);

		DrawTexture(DrawStartBtn, 655, 700, WHITE);
		StartBtn.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);
		EndDrawing();
	}
	ofstream fout;
	fout.open("../Dataset/EngEng.txt");
	WriteDictionaryToFile(EngEng, "", fout);
	fout.close();
	fout.open("../Dataset/EngVie.txt");
	WriteDictionaryToFile(EngVie, "", fout);
	fout.close();
	fout.open("../Dataset/VieEng.txt");
	WriteDictionaryToFile(VieEng, "", fout);
	fout.close();
	fout.open("../Dataset/Slang.txt");
	WriteDictionaryToFile(Slang, "", fout);
	fout.close();
	fout.open("../Dataset/Emoji.txt");
	WriteDictionaryToFile(Emoji, "", fout);
	fout.close();

	fout.open("../Dataset/Favor.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(favor[i], fout);
	}
	fout.close();
	fout.open("../Dataset/History.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(history[i], fout);
	}
	fout.close();

	for (int i = 0; i < 5; ++i) {
		deleteLL(history[i]);
		deleteLL(favor[i]);
	}
	DeleteAllTree(EngEng);
	DeleteAllTree(EngEngDef);
	DeleteAllTree(EngVie);
	DeleteAllTree(EngVieDef);
	DeleteAllTree(VieEng);
	DeleteAllTree(VieEngDef);
	DeleteAllTree(Slang);
	DeleteAllTree(SlangDef);
	DeleteAllTree(Emoji);
	DeleteAllTree(EmojiDef);
	CloseWindow();
}
void HomePage(const int screenWidth, const int screenHeight, trieNode*& VieEng, trieNode*& EngVie, trieNode*& EngEng, trieNode*& VieEngDef, trieNode*& EngVieDef, trieNode*& EngEngDef, trieNode*& Emoji, trieNode*& EmojiDef, trieNode*& Slang, trieNode*& SlangDef, Node* favor[], Node* history[])
{
	// Set up the page
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);
	int scrollSpeed = 20;
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };
	////---------------------------------------------------------------------------------------------------
	// Set up searching components
	Rectangle SearchBar = { 551, 122, 911, 60 };
	Textbox ActualSearchBar;
	ActualSearchBar.textbox = { 731, 122, 616, 60 };
	bool isSearching = false;
	bool isDisplayingResult = false;
	Texture2D SearchWordModeBtn = LoadTexture("../resources/SearchWordMode.png");
	Texture2D SearchDefModeBtn = LoadTexture("../resources/SearchDefMode.png");
	Texture2D SearchBtn = LoadTexture("../resources/searchBtn.png");
	bool SearchDefMode = true;
	////---------------------------------------------------------------------------------------------------
	// Set up Page component
	NewPageButton AddWordBtn;
	AddWordBtn.button = { 188,12,166,31 };
	NewPageButton FavoriteList;
	FavoriteList.button = { 15,9,131,31 };
	NewPageButton RevisionBtn;
	RevisionBtn.button = { 388,12,120,31 };

	NewPageButton exit;
	exit.button = { 15,923,38,38 };

	Rectangle Vocab = { 41,411,150,49 };
	Rectangle Definition = { 41, 530,207,49 };
	Rectangle VocabBox = { 639,391,49,49 };
	Rectangle DefinitionBox = { 639, 605, 49, 49 };
	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D whiteStar = LoadTexture("../resources/White Star.png");
	Texture2D blueStar = LoadTexture("../resources/Blue Star.png");
	Texture2D editIcon = LoadTexture("../resources/Edit Icon.png");
	Texture2D arrow = LoadTexture("../resources/Arrow.png");
	Texture2D trashcan = LoadTexture("../resources/TrashCan.png");
	Texture2D hisIcon = LoadTexture("../resources/historyicon.png");
	Texture2D hisDelIcon = LoadTexture("../resources/deleteHisIcon.png");
	Texture2D confirmBtn = LoadTexture("../resources/confirmBtn.png");
	////---------------------------------------------------------------------------------------------------
	// Set up choose Dict
	Rectangle chooseDictBox = { 551,122,180,60 };
	bool choose = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	bool chooseSlang = false;
	bool chooseEmo = false;

	string DictType = "NONE";
	////---------------------------------------------------------------------------------------------------
	// Set up for reset data
	bool resetData = false;
	Texture2D closeIcon = LoadTexture("../resources/Xicon.png");
	////---------------------------------------------------------------------------------------------------
	// Set up for Random a word
	Texture2D randomBtn = LoadTexture("../resources/RandomBtn.png");
	bool isFavorite = false;
	bool confirmDelete = false;
	Rectangle randomWordBox = { 551, 227, 197, 60 };
	string randomWord = "";
	string randomWordDef = "";
	vector<string> wrongdef(3);
	for (int i = 0; i < 3; ++i) {
		wrongdef[i] = "";
	}
	int randomNum = 0;
	//=================================================================================================

	string tmpWord = "";
	vector <string> tmpdef;
	int defPositionY = 590;
	int StarPositionY = 595;
	int index = 0;

	vector<string> ans;
	ans.resize(0);

	vector <string> hisList;
	hisList.resize(0);
	int hisPosY = 195;
	bool isDisplayHis = false;
	int delHisPosY = 205;

	bool isUpdatingDef = false;
	Textbox updateDefIndex;
	updateDefIndex.textbox = { 566,348,55,48 };
	bool chooseIndexDef = false;

	Textbox changeDef;
	changeDef.textbox = { 165,505,1191,331 };
	bool isChangingDef = false;
	string s = "";
	int UpdateIndex = 0;

	bool isDisplayRecommend = false;
	vector <string> recommendResult;
	int recommendBoxPosY = 182;
	string recommendTmp = "";
	trieNode* hehe = nullptr;
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, white);
		//---------------------------------------------------------------------------------------------------------------------------------
		if (CheckCollisionPointRec(mousePoint, randomWordBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (chooseEE) {
				random1Word4Def(EngEng, randomWord, randomWordDef, wrongdef);
				ans.resize(0);
				isDisplayingResult = search(EngEng, randomWord, ans);
				tmpWord = randomWord;
			}
			if (chooseEV) {
				random1Word4Def(EngVie, randomWord, randomWordDef, wrongdef);
				ans.resize(0);
				isDisplayingResult = search(EngVie, randomWord, ans);
				tmpWord = randomWord;
			}
			if (chooseVE) {
				random1Word4Def(VieEng, randomWord, randomWordDef, wrongdef);
				ans.resize(0);
				isDisplayingResult = search(VieEng, randomWord, ans);
				tmpWord = randomWord;
			}
			if (chooseSlang) {
				random1Word4Def(Slang, randomWord, randomWordDef, wrongdef);
				ans.resize(0);
				isDisplayingResult = search(Slang, randomWord, ans);
				tmpWord = randomWord;
			}
			if (chooseEmo) {
				random1Word4Def(Emoji, randomWord, randomWordDef, wrongdef);
				ans.resize(0);
				isDisplayingResult = search(Emoji, randomWord, ans);
				tmpWord = randomWord;
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------
		if ((CheckCollisionPointRec(mousePoint, { 1345,132,41,41 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || (CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && IsKeyPressed(KEY_ENTER))) {
			if (DictType == "ENG-ENG") {
				if (!SearchDefMode) {
					ans.resize(0);
					isDisplayingResult = search(EngEng, ActualSearchBar.text, ans);
					tmpWord = ActualSearchBar.text;
					if (isDisplayingResult) {
						if (!checkExistHis(history[0], ActualSearchBar.text))	add(history[0], ActualSearchBar.text);
						else {
							remove(history[0], ActualSearchBar.text);
							add(history[0], ActualSearchBar.text);
						}
					}
					hisList.resize(0);
					hisList = viewList(history[0]);
				}
				else {
					ans.resize(0);
					tmpWord = ActualSearchBar.text;
					isDisplayingResult = search(EngEngDef, ActualSearchBar.text, ans);
					//if (isDisplayingResult) add(history[0], ActualSearchBar.text);
				}
			}
			if (DictType == "ENG-VIE") {
				if (!SearchDefMode) {
					ans.resize(0);
					isDisplayingResult = search(EngVie, ActualSearchBar.text, ans);
					tmpWord = ActualSearchBar.text;
					if (isDisplayingResult) {
						if (!checkExistHis(history[1], ActualSearchBar.text))	add(history[1], ActualSearchBar.text);
						else {
							remove(history[1], ActualSearchBar.text);
							add(history[1], ActualSearchBar.text);
						}
					}
					hisList.resize(0);
					hisList = viewList(history[1]);
				}
				else {
					ans.resize(0);
					isDisplayingResult = search(EngVieDef, ActualSearchBar.text, ans);
				}
			}
			if (DictType == "VIE-ENG") {
				if (!SearchDefMode) {
					ans.resize(0);
					isDisplayingResult = search(VieEng, ActualSearchBar.text, ans);
					tmpWord = ActualSearchBar.text;
					if (isDisplayingResult) {
						if (!checkExistHis(history[2], ActualSearchBar.text))	add(history[2], ActualSearchBar.text);
						else {
							remove(history[2], ActualSearchBar.text);
							add(history[2], ActualSearchBar.text);
						}
					}
					hisList.resize(0);
					hisList = viewList(history[2]);
				}
				else {
					ans.resize(0);
					isDisplayingResult = search(VieEngDef, ActualSearchBar.text, ans);
				}
			}
			if (DictType == "SLANG") {
				if (!SearchDefMode) {
					ans.resize(0);
					isDisplayingResult = search(Slang, ActualSearchBar.text, ans);
					tmpWord = ActualSearchBar.text;
					if (isDisplayingResult) {
						if (!checkExistHis(history[3], ActualSearchBar.text))	add(history[3], ActualSearchBar.text);
						else {
							remove(history[3], ActualSearchBar.text);
							add(history[3], ActualSearchBar.text);
						}
					}
					hisList.resize(0);
					hisList = viewList(history[3]);
				}
				else {
					ans.resize(0);
					isDisplayingResult = search(SlangDef, ActualSearchBar.text, ans);
				}
			}
			if (DictType == "EMOJI") {
				if (!SearchDefMode) {
					ans.resize(0);
					isDisplayingResult = search(Emoji, ActualSearchBar.text, ans);
					tmpWord = ActualSearchBar.text;
					if (isDisplayingResult) {
						if (!checkExistHis(history[4], ActualSearchBar.text))	add(history[4], ActualSearchBar.text);
						else {
							remove(history[4], ActualSearchBar.text);
							add(history[4], ActualSearchBar.text);
						}
					}
					hisList.resize(0);
					hisList = viewList(history[4]);
				}
				else {
					ans.resize(0);
					isDisplayingResult = search(EmojiDef, ActualSearchBar.text, ans);
				}
			}
		}
		if (CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && IsKeyPressed(KEY_BACKSPACE)) {
			isDisplayingResult = false;
		}

		if (isDisplayingResult) {
			if (!SearchDefMode) {
				if (CheckCollisionPointRec(mousePoint, { 0,338,753,644 })) {
					defPositionY += (GetMouseWheelMove() * scrollSpeed);
					StarPositionY += (GetMouseWheelMove() * scrollSpeed);
				}
				if (defPositionY > 590) defPositionY = 590;
				if (StarPositionY > 595) StarPositionY = 595;
				int newDefMark = 0;
				for (int i = 0; i < ans.size(); ++i) {
					if (ans[i].size() > 130) {
						tmpdef = divideString(ans[i], 130);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 50, (StarPositionY + 50 * (float)(i + newDefMark + j)) }, 30, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 72, (defPositionY + 50 * (float)(i + newDefMark + j)) }, 30, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 50, (StarPositionY + 50 * (float)(i + newDefMark)) }, 30, 0, navy);
						DrawTextEx(bold, ans[i].c_str(), { 72, (defPositionY + 50 * (float)(i + newDefMark)) }, 30, 0, navy);
						//newDefMark += 1;
					}
				}

				DrawRectangle(10, 388, 1492, 200, white);
				DrawRectangleRounded(Definition, 0.3, 0, yellow);
				DrawRectangleRounded(Vocab, 0.3, 0, yellow);
				DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 2, Vocab.x + 1400, Vocab.y + Vocab.height - 2, yellow);
				DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 1, Vocab.x + 1400, Vocab.y + Vocab.height - 1, yellow);
				DrawLine(Definition.x + 10, Definition.y + Definition.height - 2, Definition.x + 1400, Definition.y + Definition.height - 2, yellow);
				DrawLine(Definition.x + 10, Definition.y + Definition.height - 1, Definition.x + 1400, Definition.y + Definition.height - 1, yellow);
				DrawRectangleRounded({ Vocab.x + 158,Vocab.y,49,49 }, 0.3, 0, yellow);
				DrawRectangleRounded({ Vocab.x + 1365 ,Vocab.y,49,49 }, 0.3, 0, yellow);
				DrawRectangleRounded({ Definition.x + 1365,Definition.y,49,49 }, 0.3, 0, yellow);
				DrawTexture(trashcan, Vocab.x + 1376, Vocab.y + 10, WHITE);
				DrawTexture(editIcon, Definition.x + 1370 + 3, Definition.y + 5, WHITE);
				DrawTextEx(bold, "Vocab", { 69,412 }, 43, 0, navy);
				DrawTextEx(bold, "Definition", { 67,530 }, 43, 0, navy);

				if (chooseEE) index = 0;
				if (chooseEV) index = 1;
				if (chooseVE) index = 2;
				if (chooseSlang) index = 3;
				if (chooseEmo) index = 4;
				if (!checkExistFavor(favor[index], tmpWord)) {
					isFavorite = false;
					if (CheckCollisionPointRec(mousePoint, { Vocab.x + 167, Vocab.y + 8, 32,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						isFavorite = true;
						add(favor[index], tmpWord);
					}
				}
				else {
					isFavorite = true;
					if (CheckCollisionPointRec(mousePoint, { Vocab.x + 167, Vocab.y + 8, 32,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						isFavorite = false;
						remove(favor[index], tmpWord);
					}
				}
				if (!isFavorite) {
					DrawTexture(whiteStar, Vocab.x + 167, Vocab.y + 8, GRAY);
				}
				else {
					DrawTexture(blueStar, Vocab.x + 167, Vocab.y + 8, GRAY);
				}
				DrawTextEx(bold, tmpWord.c_str(), { 72, 470 }, 30, 0, navy);

				if (CheckCollisionPointRec(mousePoint, { Vocab.x + 1365, Vocab.y, 49, 49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					confirmDelete = true;
				}
				if (confirmDelete)
				{
					DrawRectangleRounded({ 501,395,511,243 }, 0.08, 0, blue);
					DrawRectangleRounded({ 542,554,161,49 }, 0.08, 0, yellow);
					DrawRectangleRounded({ 811,554,161, 49 }, 0.08, 0, yellow);
					DrawTexture(closeIcon, 966, 413, WHITE);
					DrawTextEx(bold, "Delete Confirmation", { 585,468 }, 48, 0, white);
					DrawTextEx(bold, "Yes", { 597,557 }, 44, 0, navy);
					DrawTextEx(bold, "No", { 874,557 }, 44, 0, navy);
					if (CheckCollisionPointRec(mousePoint, { 965,413,31,27 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						confirmDelete = false;
					}
					if (CheckCollisionPointRec(mousePoint, { 811,554,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						confirmDelete = false;
					}
					string str(ActualSearchBar.text);
					vector <string> tmp;
					tmp.resize(0);
					if (CheckCollisionPointRec(mousePoint, { 542,554,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(favor[index], ActualSearchBar.text);

						if (DictType == "ENG-ENG")
						{
							DeleteAWord(EngEng, str, 0, tmp);
							vector <string> tmp2 = tmp;
							for (auto x : tmp)
							{
								DeleteAWord(EngEngDef, x, 0, tmp2);
							}
						}
						else if (DictType == "ENG-VIE")
						{
							DeleteAWord(EngVie, str, 0, tmp);
							vector <string> tmp2 = tmp;
							for (auto x : tmp)
							{
								DeleteAWord(EngVieDef, x, 0, tmp2);
							}
						}
						else if (DictType == "VIE-ENG")
						{
							DeleteAWord(VieEng, str, 0, tmp);
							vector <string> tmp2 = tmp;
							for (auto x : tmp)
							{
								DeleteAWord(VieEngDef, x, 0, tmp2);
							}
						}
						else if (DictType == "SLANG")
						{
							DeleteAWord(Slang, str, 0, tmp);
							vector <string> tmp2 = tmp;
							for (auto x : tmp)
							{
								DeleteAWord(SlangDef, x, 0, tmp2);
							}
						}
						else if (DictType == "EMOJI")
						{
							DeleteAWord(Emoji, str, 0, tmp);
							vector <string> tmp2 = tmp;
							for (auto x : tmp)
							{
								DeleteAWord(EmojiDef, x, 0, tmp2);
							}
						}
						isDisplayingResult = false;
						confirmDelete = false;
					}
				}
				if (CheckCollisionPointRec(mousePoint, { Definition.x + 1370 + 3, Definition.y + 5, 37,37 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					isUpdatingDef = true;
				}
			}
			else {

				if (CheckCollisionPointRec(mousePoint, { 0,338,753,644 })) {
					defPositionY += (GetMouseWheelMove() * scrollSpeed);
					StarPositionY += (GetMouseWheelMove() * scrollSpeed);
				}
				if (defPositionY > 470) defPositionY = 470;
				if (StarPositionY > 475) StarPositionY = 475;
				int newDefMark = 0;
				for (int i = 0; i < ans.size(); ++i) {
					if (ans[i].size() > 130) {
						tmpdef = divideString(ans[i], 130);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 50, (StarPositionY + 50 * (float)(i + newDefMark + j)) }, 30, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 72, (defPositionY + 50 * (float)(i + newDefMark + j)) }, 30, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 50, (StarPositionY + 50 * (float)(i + newDefMark)) }, 30, 0, navy);
						DrawTextEx(bold, ans[i].c_str(), { 72, (defPositionY + 50 * (float)(i + newDefMark)) }, 30, 0, navy);
						//newDefMark += 1;
					}
				}

				DrawRectangle(10, 388, 1492, 80, white);
				DrawRectangleRounded(Vocab, 0.3, 0, yellow);
				DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 2, Vocab.x + 1400, Vocab.y + Vocab.height - 2, yellow);
				DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 1, Vocab.x + 1400, Vocab.y + Vocab.height - 1, yellow);
				DrawTextEx(bold, "Vocab", { 69,412 }, 43, 0, navy);
			}
		}
		else {
			DrawTextEx(bold, "No Data Available", { 20 + 450, (520) }, 100, 0, RED);
			DrawTextEx(bold, "Please try again", { 20 + 50 + 450, (600) }, 90, 0, RED);
			defPositionY = 590;
			StarPositionY = 595;
		};


		DrawRectangle(0, 0, 1512, 340, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangle(0, 340, 1512, 48, yellow);
		DrawTexture(logo, 15, 100, WHITE);

		//----------------------------------------------------------------------------------------------------
		if (CheckCollisionPointRec(mousePoint, { 754, 182, 708, 216 })) {
			hisPosY += (GetMouseWheelMove() * scrollSpeed);
			delHisPosY += (GetMouseWheelMove() * scrollSpeed);
		}
		if (hisPosY > 195) hisPosY = 195;
		if (delHisPosY > 205) delHisPosY = 205;
		if (CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && ActualSearchBar.text[0] == '\0' && !SearchDefMode) {
			isDisplayHis = true;
		}
		if (isDisplayHis) {
			DrawRectangle(1432, 182 - 30, 30, 30, white);
			for (int i = 0; i < hisList.size(); ++i) {
				DrawRectangle(754, hisPosY - 13 + 54 * i, 708, 54, white);
				DrawTextEx(bold, hisList[i].c_str(), { 820,hisPosY + 54 * (float)i }, 26, 0, navy);
				DrawLine(754, hisPosY - 13 + 54 * i, 1462, hisPosY - 13 + 54 * i, blue);
				DrawLine(754, hisPosY - 13 + 54 + 54 * i, 1462, hisPosY - 13 + 54 + 54 * i, blue);
				DrawTexture(hisIcon, 764, hisPosY - 5 + 54 * i, WHITE);
				DrawTexture(hisDelIcon, 1420, delHisPosY + 54 * i, WHITE);

				if (chooseEE) {
					if (CheckCollisionPointRec(mousePoint, { 1420, delHisPosY + 54 * (float)i,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(history[0], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[0]);
					}
					if (CheckCollisionPointRec(mousePoint, { 756, delHisPosY - 22 + 54 * (float)i,664,59 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						ans.resize(0);
						tmpWord = hisList[i];
						isDisplayingResult = search(EngEng, tmpWord, ans);
						remove(history[0], hisList[i]);
						add(history[0], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[0]);
					}
				}
				if (chooseEV) {
					if (CheckCollisionPointRec(mousePoint, { 1420, delHisPosY + 54 * (float)i,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(history[1], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[1]);
					}
					if (CheckCollisionPointRec(mousePoint, { 756, delHisPosY - 22 + 54 * (float)i,664,59 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						ans.resize(0);
						tmpWord = hisList[i];
						isDisplayingResult = search(EngVie, tmpWord, ans);
						remove(history[1], hisList[i]);
						add(history[1], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[1]);
					}
				}
				if (chooseVE) {
					if (CheckCollisionPointRec(mousePoint, { 1420, delHisPosY + 54 * (float)i,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(history[2], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[2]);
					}
					if (CheckCollisionPointRec(mousePoint, { 756, delHisPosY - 22 + 54 * (float)i,664,59 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						ans.resize(0);
						tmpWord = hisList[i];
						isDisplayingResult = search(VieEng, tmpWord, ans);
						remove(history[2], hisList[i]);
						add(history[2], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[2]);
					}
				}
				if (chooseSlang) {
					if (CheckCollisionPointRec(mousePoint, { 1420, delHisPosY + 54 * (float)i,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(history[3], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[3]);
					}
					if (CheckCollisionPointRec(mousePoint, { 756, delHisPosY - 22 + 54 * (float)i,664,59 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						ans.resize(0);
						tmpWord = hisList[i];
						isDisplayingResult = search(Slang, tmpWord, ans);
						remove(history[3], hisList[i]);
						add(history[3], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[3]);
					}
				}
				if (chooseEmo) {
					if (CheckCollisionPointRec(mousePoint, { 1420, delHisPosY + 54 * (float)i,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						remove(history[4], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[4]);
					}
					if (CheckCollisionPointRec(mousePoint, { 756, delHisPosY - 22 + 54 * (float)i,664,59 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						ans.resize(0);
						tmpWord = hisList[i];
						isDisplayingResult = search(Emoji, tmpWord, ans);
						remove(history[4], hisList[i]);
						add(history[4], hisList[i]);
						hisList.resize(0);
						hisList = viewList(history[4]);
					}
				}
			}
		}
		if ((!CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && !CheckCollisionPointRec(mousePoint, { 754,182,708,1103 })) || ActualSearchBar.lettercount > 0) {
			isDisplayHis = false;
		}
		if ((!CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && !CheckCollisionPointRec(mousePoint, { 754,182,708,1103 })) || ActualSearchBar.lettercount == 0) {
			isDisplayRecommend = false;
		}
		//////----------------------------------------------------------------------------------------------------------------
		if (CheckCollisionPointRec(mousePoint, ActualSearchBar.textbox) && ActualSearchBar.text[0] != '\0' /*&& !SearchDefMode*/) {
			isDisplayRecommend = true;
		}
		if (isDisplayRecommend) {
			if (chooseEE) {
				if (!SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(EngEng, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(EngEng, tmpWord, ans);
							remove(history[0], recommendResult[i]);
							add(history[0], recommendResult[i]);
							hisList.resize(0);
							hisList = viewList(history[0]);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
				if (SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(EngEngDef, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						if (recommendResult[i].size() > 75) {
							DrawTextEx(bold, divideString1Part(recommendResult[i], 75).c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						}
						else DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(EngEngDef, tmpWord, ans);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
			}
			if (chooseEV) {
				if (!SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(EngVie, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(EngVie, tmpWord, ans);
							remove(history[1], recommendResult[i]);
							add(history[1], recommendResult[i]);
							hisList.resize(0);
							hisList = viewList(history[1]);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
				if (SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(EngVieDef, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						if (recommendResult[i].size() > 75) {
							DrawTextEx(bold, divideString1Part(recommendResult[i], 75).c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						}
						else DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(EngVieDef, tmpWord, ans);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
			}
			if (chooseVE) {
				if (!SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(VieEng, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(VieEng, tmpWord, ans);
							remove(history[2], recommendResult[i]);
							add(history[2], recommendResult[i]);
							hisList.resize(0);
							hisList = viewList(history[2]);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
				if (SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(VieEngDef, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						if (recommendResult[i].size() > 75) {
							DrawTextEx(bold, divideString1Part(recommendResult[i], 75).c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						}
						else DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(VieEngDef, tmpWord, ans);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
			}
			if (chooseSlang) {
				if (!SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(Slang, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(Slang, tmpWord, ans);
							remove(history[3], recommendResult[i]);
							add(history[3], recommendResult[i]);
							hisList.resize(0);
							hisList = viewList(history[3]);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
				if (SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(SlangDef, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						if (recommendResult[i].size() > 75) {
							DrawTextEx(bold, divideString1Part(recommendResult[i], 75).c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						}
						else DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(SlangDef, tmpWord, ans);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
			}
			if (chooseEmo) {
				if (!SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(Emoji, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(Emoji, tmpWord, ans);
							remove(history[4], recommendResult[i]);
							add(history[4], recommendResult[i]);
							hisList.resize(0);
							hisList = viewList(history[4]);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
				if (SearchDefMode) {
					recommendTmp = ActualSearchBar.text;
					hehe = find(EmojiDef, recommendTmp);
					recommendResult.resize(0);
					rcmFunc(hehe, recommendTmp, recommendResult);
					DrawRectangle(1432, 182 - 30, 30, 30, white);
					for (int i = 0; i < recommendResult.size(); ++i) {
						DrawRectangle(754, recommendBoxPosY + 54 * i, 708, 54, white);
						if (recommendResult[i].size() > 75) {
							DrawTextEx(bold, divideString1Part(recommendResult[i], 75).c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						}
						else DrawTextEx(bold, recommendResult[i].c_str(), { 800, recommendBoxPosY + 13 + 54 * (float)i }, 26, 0, navy);
						DrawLine(754, recommendBoxPosY + 54 * i, 1462, recommendBoxPosY + 54 * i, blue);
						DrawLine(754, recommendBoxPosY + 54 + 54 * i, 1462, recommendBoxPosY + 54 + 54 * i, blue);

						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i,708,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							ans.resize(0);
							tmpWord = recommendResult[i];
							isDisplayingResult = search(EmojiDef, tmpWord, ans);
						}
						if (CheckCollisionPointRec(mousePoint, { 754, recommendBoxPosY + 54 * (float)i, 708, 54 })) {
							recommendBoxPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						if (recommendBoxPosY > 182) recommendBoxPosY = 182;
					}
				}
			}
		}
		//----------------------------------------------------------------------------------------------------------------
		DrawRectangle(754, 48, 715, 74, navy);
		DrawRectangle(754, 0, 715, 48, blue);
		DrawTexture(randomBtn, 550, 227, WHITE);
		DrawRectangleRounded(SearchBar, 60, 0, white);
		if (!isSearching) {
			if (!SearchDefMode) DrawTextEx(italic, "Search for a word...", { 774,138 }, 28, 0, navy);
			else DrawTextEx(italic, "Search for a definition...", { 774,138 }, 28, 0, navy);
		}
		ActualSearchBar.worktextbox(isSearching);
		DrawTextEx(bold, ActualSearchBar.text, { 774,138 }, 28, 0, navy);

		DrawTextEx(bold, "Favorite List", { 15,12 }, 24, 0, white);
		DrawTextEx(bold, "Add new words", { 188,12 }, 24, 0, white);
		AddWordBtn.workbutton(mousePoint, AddWordPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);
		FavoriteList.workbutton(mousePoint, FavoriteListPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);
		exit.workbutton(mousePoint, WaitingPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);
		DrawTextEx(bold, "Revision", { 388,12 }, 24, 0, white);
		DrawTextEx(bold, "Reset Data", { 1369,12 }, 24, 0, white);
		DrawTextEx(bold, "or", { 634,189 }, 30, 0, white);

		DrawTextEx(bold, "DICTIONARY", { 248,146 }, 49, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 219, 196 }, 41, 0, white);
		DrawLineEx({ 155, 10 }, { 155, 38 }, 3.0, white);
		DrawLineEx({ 355, 10 }, { 355, 38 }, 3.0, white);
		DrawLineEx({ 744,133 }, { 744, 168 }, 4.0, { 16,49,107,255 });
		//------------------------------------------------------------------------------------------------------------------------
		if (isUpdatingDef) {
			DrawRectangle(108, 236, 1312, 710, blue);
			DrawRectangle(108, 452, 1312, 494, navy);
			DrawRectangleRoundedLines({ 137,491,1253,367 }, 0.349, 0, 4.0, blue);
			DrawRectangleRounded({ 108,236,1312,31 }, 0.26, 0, yellow);
			DrawRectangle(108, 254, 1312, 19, yellow);
			DrawTexture(confirmBtn, 667, 872, white);
			DrawTexture(hisDelIcon, 1379, 244, WHITE);

			DrawTextEx(bold, "There are     definitions for this word. You want to update the", { 190,298 }, 55, 0, yellow);
			DrawTextEx(bold, "definition number:", { 190,343 }, 55, 0, yellow);
			DrawTextEx(bold, to_string(ans.size()).c_str(), { 382,300 }, 55, 0, yellow);
			if (CheckCollisionPointRec(mousePoint, { 1379,244,22,22 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				for (int i = 0; i < updateDefIndex.lettercount; ++i) {
					updateDefIndex.text[i] = '\0';
				}
				updateDefIndex.lettercount = 0;
				for (int i = 0; i < changeDef.lettercount; ++i) {
					changeDef.text[i] = '\0';
				}
				changeDef.lettercount = 0;
				isUpdatingDef = false;
			}
			DrawRectangleRec(updateDefIndex.textbox, yellow);
			updateDefIndex.worktextbox(chooseIndexDef);
			DrawTextEx(bold, updateDefIndex.text, { 583,342 }, 55, 0, navy);

			if (IsKeyPressed(KEY_ENTER) && atoi(updateDefIndex.text) >= 1 && atoi(updateDefIndex.text) <= ans.size()) {
				UpdateIndex = atoi(updateDefIndex.text) - 1;
				for (int i = 0; i < ans[UpdateIndex].size(); ++i) {
					changeDef.text[i] = ans[UpdateIndex][i];
				}
				changeDef.lettercount = ans[UpdateIndex].size();
			}
			changeDef.worktextbox(isChangingDef);

			if (changeDef.text[0] == '\0') DrawTextEx(bold, "No Definition for this index !", { 175,515 }, 45, 0, RED);
			else {
				s = changeDef.text;
				if (s.size() > 70) {
					tmpdef = divideString(s, 70);
					for (int j = 0; j < tmpdef.size(); ++j) {
						DrawTextEx(bold, tmpdef[j].c_str(), { 175,515 + 50 * (float)(j) }, 45, 0, white);
					}
				}
				else {
					DrawTextEx(bold, s.c_str(), { 175, 515 }, 45, 0, white);
				}
			}

			if (chooseEE) {
				if (CheckCollisionPointRec(mousePoint, { 675,877,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					updateDef(EngEng, tmpWord, UpdateIndex, changeDef.text);
					trieNode* oldDef = find(EngEngDef, ans[UpdateIndex]);
					vector <string> trash;
					if (oldDef->mean.size() == 1)
						DeleteAWord(EngEngDef, ans[UpdateIndex], 0, trash);
					else
					{
						for (int i = 0; i < oldDef->mean.size(); i++)
						{
							if (oldDef->mean[i] == tmpWord)
							{
								oldDef->mean.erase(oldDef->mean.begin() + i);
							}
						}
					}
					insert(EngEngDef, changeDef.text, { tmpWord });

					ans.resize(0);
					isDisplayingResult = search(EngEng, tmpWord, ans);

					for (int i = 0; i < updateDefIndex.lettercount; ++i) {
						updateDefIndex.text[i] = '\0';
					}
					updateDefIndex.lettercount = 0;
					for (int i = 0; i < changeDef.lettercount; ++i) {
						changeDef.text[i] = '\0';
					}
					changeDef.lettercount = 0;
					isUpdatingDef = false;
				}
			}
			if (chooseEV) {
				if (CheckCollisionPointRec(mousePoint, { 675,877,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					updateDef(EngVie, tmpWord, UpdateIndex, changeDef.text);
					trieNode* oldDef = find(EngVieDef, ans[UpdateIndex]);
					vector <string> trash;
					if (oldDef->mean.size() == 1)
						DeleteAWord(EngVieDef, ans[UpdateIndex], 0, trash);
					else
					{
						for (int i = 0; i < oldDef->mean.size(); i++)
						{
							if (oldDef->mean[i] == tmpWord)
							{
								oldDef->mean.erase(oldDef->mean.begin() + i);
							}
						}
					}
					insert(EngVieDef, changeDef.text, { tmpWord });

					ans.resize(0);
					isDisplayingResult = search(EngVie, tmpWord, ans);

					for (int i = 0; i < updateDefIndex.lettercount; ++i) {
						updateDefIndex.text[i] = '\0';
					}
					updateDefIndex.lettercount = 0;
					for (int i = 0; i < changeDef.lettercount; ++i) {
						changeDef.text[i] = '\0';
					}
					changeDef.lettercount = 0;
					isUpdatingDef = false;
				}
			}
			if (chooseVE) {
				if (CheckCollisionPointRec(mousePoint, { 675,877,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					updateDef(VieEng, tmpWord, UpdateIndex, changeDef.text);
					trieNode* oldDef = find(VieEngDef, ans[UpdateIndex]);
					vector <string> trash;
					if (oldDef->mean.size() == 1)
						DeleteAWord(VieEngDef, ans[UpdateIndex], 0, trash);
					else
					{
						for (int i = 0; i < oldDef->mean.size(); i++)
						{
							if (oldDef->mean[i] == tmpWord)
							{
								oldDef->mean.erase(oldDef->mean.begin() + i);
							}
						}
					}
					insert(VieEngDef, changeDef.text, { tmpWord });

					ans.resize(0);
					isDisplayingResult = search(VieEng, tmpWord, ans);

					for (int i = 0; i < updateDefIndex.lettercount; ++i) {
						updateDefIndex.text[i] = '\0';
					}
					updateDefIndex.lettercount = 0;
					for (int i = 0; i < changeDef.lettercount; ++i) {
						changeDef.text[i] = '\0';
					}
					changeDef.lettercount = 0;
					isUpdatingDef = false;
				}
			}
			if (chooseSlang) {
				if (CheckCollisionPointRec(mousePoint, { 675,877,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					updateDef(Slang, tmpWord, UpdateIndex, changeDef.text);
					trieNode* oldDef = find(SlangDef, ans[UpdateIndex]);
					vector <string> trash;
					if (oldDef->mean.size() == 1)
						DeleteAWord(SlangDef, ans[UpdateIndex], 0, trash);
					else
					{
						for (int i = 0; i < oldDef->mean.size(); i++)
						{
							if (oldDef->mean[i] == tmpWord)
							{
								oldDef->mean.erase(oldDef->mean.begin() + i);
							}
						}
					}
					insert(SlangDef, changeDef.text, { tmpWord });

					ans.resize(0);
					isDisplayingResult = search(Slang, tmpWord, ans);

					for (int i = 0; i < updateDefIndex.lettercount; ++i) {
						updateDefIndex.text[i] = '\0';
					}
					updateDefIndex.lettercount = 0;
					for (int i = 0; i < changeDef.lettercount; ++i) {
						changeDef.text[i] = '\0';
					}
					changeDef.lettercount = 0;
					isUpdatingDef = false;
				}
			}
			if (chooseEmo) {
				if (CheckCollisionPointRec(mousePoint, { 675,877,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					updateDef(Emoji, tmpWord, UpdateIndex, changeDef.text);
					trieNode* oldDef = find(EmojiDef, ans[UpdateIndex]);
					vector <string> trash;
					if (oldDef->mean.size() == 1)
						DeleteAWord(EmojiDef, ans[UpdateIndex], 0, trash);
					else
					{
						for (int i = 0; i < oldDef->mean.size(); i++)
						{
							if (oldDef->mean[i] == tmpWord)
							{
								oldDef->mean.erase(oldDef->mean.begin() + i);
							}
						}
					}
					insert(EmojiDef, changeDef.text, { tmpWord });

					ans.resize(0);
					isDisplayingResult = search(Emoji, tmpWord, ans);

					for (int i = 0; i < updateDefIndex.lettercount; ++i) {
						updateDefIndex.text[i] = '\0';
					}
					updateDefIndex.lettercount = 0;
					for (int i = 0; i < changeDef.lettercount; ++i) {
						changeDef.text[i] = '\0';
					}
					changeDef.lettercount = 0;
					isUpdatingDef = false;
				}
			}
		}

		//Choose Dictionary
		DrawTextEx(bold, "None", { 610,132 }, 40, 0, navy);
		DrawTexture(arrow, 710, 145, WHITE);
		if (CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
			chooseSlang = false;
			chooseEmo = false;
		}
		if (choose) { //{ 551, 122, 911, 60 };
			DrawRectangle(551, 152, 30, 30, white);
			DrawRectangle(551, 182, 185, 60, white);
			DrawRectangle(551, 182 + 60, 185, 60, white);
			DrawRectangle(551, 182 + 120, 185, 60, white);
			DrawRectangle(551, 182 + 180, 185, 60, white);
			DrawRectangle(551, 182 + 240, 185, 60, white);

			DrawRectangleLines(550, 182, 187, 301, blue);
			DrawLine(551, 182 + 60, 736, 182 + 60, blue);
			DrawLine(551, 182 + 120, 736, 182 + 120, blue);
			DrawLine(551, 182 + 180, 736, 182 + 180, blue);
			DrawLine(551, 182 + 240, 736, 182 + 240, blue);

			DrawTextEx(bold, "ENG-ENG", { 595,200 }, 30, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 600,200 + 60 }, 30, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 600,200 + 120 }, 30, 0, navy);
			DrawTextEx(bold, "SLANG", { 610,200 + 180 }, 30, 0, navy);
			DrawTextEx(bold, "EMOJI", { 610,200 + 240 }, 30, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "ENG-ENG", { 585, 132 }, 40, 0, navy);
			choose = false;
			DictType = "ENG-ENG";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 60, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "ENG-VIE", { 595, 132 }, 40, 0, navy);
			choose = false;
			DictType = "ENG-VIE";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 120, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		}
		if (chooseVE) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "VIE-ENG", { 595, 132 }, 40, 0, navy);
			choose = false;
			DictType = "VIE-ENG";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 180, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang = true;
		}
		if (chooseSlang) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "SLANG", { 605, 132 }, 40, 0, navy);
			choose = false;
			DictType = "SLANG";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 240, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmo = true;
		}
		if (chooseEmo) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "EMOJI", { 605, 132 }, 40, 0, navy);
			choose = false;
			DictType = "EMOJI";
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = false;
		}


		RevisionBtn.workbutton(mousePoint, RevisionPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);

		if (SearchDefMode) DrawTexture(SearchDefModeBtn, 1405, 132, WHITE);
		else DrawTexture(SearchWordModeBtn, 1405, 132, WHITE);
		if (CheckCollisionPointRec(mousePoint, { 1405,132,40,40 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (SearchDefMode) SearchDefMode = false;
			else SearchDefMode = true;
		}
		DrawTexture(SearchBtn, 1345, 132, WHITE);


		if (CheckCollisionPointRec(mousePoint, { 1369,12,120,20 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			resetData = true;
		}
		if (resetData) {
			DrawRectangleRounded({ 501,375,511,243 }, 0.08, 0, blue);
			DrawRectangleRounded({ 542,534,161,49 }, 0.08, 0, yellow);
			DrawRectangleRounded({ 811,534,161, 49 }, 0.08, 0, yellow);
			DrawTexture(closeIcon, 966, 393, WHITE);
			DrawTextEx(bold, "Reset Data Confirmation", { 550,433 }, 48, 0, white);
			DrawTextEx(bold, "Yes", { 597,537 }, 44, 0, navy);
			DrawTextEx(bold, "No", { 874,537 }, 44, 0, navy);
			if (CheckCollisionPointRec(mousePoint, { 966,393,24,24 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				resetData = false;
			}
			if (CheckCollisionPointRec(mousePoint, { 811,534,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				resetData = false;
			}
			if (CheckCollisionPointRec(mousePoint, { 542,534,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				DeleteAllTree(EngEng);
				DeleteAllTree(EngVie);
				DeleteAllTree(VieEng);
				DeleteAllTree(Slang);
				DeleteAllTree(Emoji);
				DeleteAllTree(EngEngDef);
				DeleteAllTree(EngVieDef);
				DeleteAllTree(VieEngDef);
				DeleteAllTree(SlangDef);
				DeleteAllTree(EmojiDef);
				readFileToTree(VieEng, VieEngDef, "VieEng.txt");
				readFileToTree(EngEng, EngEngDef, "EngEng.txt");
				readFileToTree(EngVie, EngVieDef, "EngVie.txt");
				readFileToTree(Emoji, EmojiDef, "Emoji.txt");
				readFileToTree(Slang, SlangDef, "Slang.txt");

				for (int i = 0; i < 5; ++i) {
					deleteLL(history[i]);
					deleteLL(favor[i]);
				}
				hisList.resize(0);
				hisList = viewList(history[0]);
				resetData = false;
			}
		}
		EndDrawing();
	}

	ofstream fout;
	fout.open("../Dataset/EngEng.txt");
	WriteDictionaryToFile(EngEng, "", fout);
	fout.close();
	fout.open("../Dataset/EngVie.txt");
	WriteDictionaryToFile(EngVie, "", fout);
	fout.close();
	fout.open("../Dataset/VieEng.txt");
	WriteDictionaryToFile(VieEng, "", fout);
	fout.close();
	fout.open("../Dataset/Slang.txt");
	WriteDictionaryToFile(Slang, "", fout);
	fout.close();
	fout.open("../Dataset/Emoji.txt");
	WriteDictionaryToFile(Emoji, "", fout);
	fout.close();

	fout.open("../Dataset/Favor.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(favor[i], fout);
	}
	fout.close();
	fout.open("../Dataset/History.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(history[i], fout);
	}
	fout.close();

	for (int i = 0; i < 5; ++i) {
		deleteLL(history[i]);
		deleteLL(favor[i]);
	}
	DeleteAllTree(EngEng);
	DeleteAllTree(EngEngDef);
	DeleteAllTree(EngVie);
	DeleteAllTree(EngVieDef);
	DeleteAllTree(VieEng);
	DeleteAllTree(VieEngDef);
	DeleteAllTree(Slang);
	DeleteAllTree(SlangDef);
	DeleteAllTree(Emoji);
	DeleteAllTree(EmojiDef);

	CloseWindow();
}
void AddWordPage(const int screenWidth, const int screenHeight, trieNode*& VieEng, trieNode*& EngVie, trieNode*& EngEng, trieNode*& VieEngDef, trieNode*& EngVieDef, trieNode*& EngEngDef, trieNode*& Emoji, trieNode*& EmojiDef, trieNode*& Slang, trieNode*& SlangDef, Node* favor[], Node* history[]) {
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D confirm = LoadTexture("../resources/confirmBtn.png");

	NewPageButton Back;
	Back.button = { 1431,9,61,31 };

	Textbox WordBar;
	WordBar.textbox = { 667, 340, 751, 60 };
	bool isTypingWord = false;
	Textbox DefBar;
	DefBar.textbox = { 667, 534, 751, 60 };
	bool isTypingDef = false;

	Texture2D confirmBtn = LoadTexture("../resources/confirmBtn.png");
	float frameHeightconfirmBtn = (float)confirmBtn.height;
	Rectangle sourceRecconfirmBtn = { 0, 0, (float)confirmBtn.width,frameHeightconfirmBtn };
	// Define button bounds on screen
	Rectangle btnBoundsconfirmBtn = { 650, 400, (float)confirmBtn.width, frameHeightconfirmBtn };
	int confirmBtnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
	bool confirmBtnAction = false;         // Button action should be activated
	bool confirmBtnFalseDisplay = false;


	bool choose = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	bool chooseSlang = false;
	bool chooseEmo = false;

	int addSuccessfully = 1;
	Rectangle chooseDictBox = { 217,627,261,60 };
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawTexture(logo, 265, 126, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 255,331 }, 49, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 212,392 }, 41, 0, white);

		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);

		DrawRectangleRounded({ 667,295,125,90 }, 0.18, 0, yellow);
		DrawRectangleRounded({ 667,487,199,90 }, 0.18, 0, yellow);
		DrawTextEx(bold, "Word", { 689,295 }, 44, 0, navy);
		DrawTextEx(bold, "Definition", { 689,491 }, 44, 0, navy);

		DrawRectangleRounded(WordBar.textbox, 0.18, 0, WHITE);
		if (!isTypingWord) {
			DrawTextEx(italic, "Type in a word...", { 690,355 }, 28, 0, navy);
		}
		WordBar.worktextbox(isTypingWord);
		DrawTextEx(bold, WordBar.text, { 690,355 }, 28, 0, navy);

		DrawRectangleRounded(DefBar.textbox, 0.18, 0, WHITE);
		if (!isTypingDef) {
			DrawTextEx(italic, "Type in its definition...", { 690,550 }, 28, 0, navy);
		}
		DefBar.worktextbox(isTypingDef);
		DrawTextEx(bold, DefBar.text, { 690,550 }, 28, 0, navy);

		DrawTextEx(bold, "Please choose the dictionary", { 132,522 }, 43, 0, yellow);
		DrawTextEx(bold, "you want to update", { 205, 564 }, 43, 0, yellow);


		//Choose Dictionary
		DrawRectangleRec(chooseDictBox, WHITE);
		DrawTextEx(bold, "Choose Dict", { 265,637 }, 40, 0, navy);

		if (CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
			chooseSlang = false;
			chooseEmo = false;
		}
		if (choose) { //{ 217,627,261,60 };
			DrawRectangle(217, 687, 261, 60, yellow);
			DrawRectangle(217, 687 + 60, 261, 60, yellow);
			DrawRectangle(217, 687 + 120, 261, 60, yellow);
			DrawRectangle(217, 687 + 180, 261, 60, yellow);
			DrawRectangle(217, 687 + 240, 261, 60, yellow);

			DrawLine(217, 747, 478, 747, navy);
			DrawLine(217, 747 + 60, 478, 747 + 60, navy);
			DrawLine(217, 747 + 120, 478, 747 + 120, navy);
			DrawLine(217, 747 + 180, 478, 747 + 180, navy);
			DrawLine(217, 747 + 240, 478, 747 + 240, navy);

			DrawTextEx(bold, "ENG-ENG", { 285,697 }, 40, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 292,697 + 60 }, 40, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 293,697 + 120 }, 40, 0, navy);
			DrawTextEx(bold, "SLANG", { 293 + 10,697 + 180 }, 40, 0, navy);
			DrawTextEx(bold, "EMOJI", { 293 + 15,697 + 240 }, 40, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-ENG", { 287, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687 + 60,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-VIE", { 290, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687 + 120,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		}
		if (chooseVE) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "VIE-ENG", { 290, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687 + 180,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang = true;
		}
		if (chooseSlang) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "SLANG", { 285 + 20, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687 + 240,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmo = true;
		}
		if (chooseEmo) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "EMOJI", { 285 + 20, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;

		DrawTexture(confirm, 969, 643, WHITE);
		if (CheckCollisionPointRec(mousePoint, { 969,643,162,60 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (WordBar.text[0] == '\0' || DefBar.text[0] == '\0' || choose == true) {
				addSuccessfully = 2;
			}
			else
			{
				if (chooseEE)
				{
					insert(EngEng, WordBar.text, { DefBar.text });
					insert(EngEngDef, DefBar.text, { WordBar.text });
					addSuccessfully = 3;
				}
				if (chooseEV)
				{
					insert(EngVie, WordBar.text, { DefBar.text });
					insert(EngVieDef, DefBar.text, { WordBar.text });
					addSuccessfully = 3;
				}
				if (chooseVE)
				{
					insert(VieEng, WordBar.text, { DefBar.text });
					insert(VieEngDef, DefBar.text, { WordBar.text });
					addSuccessfully = 3;
				}
				if (chooseEmo)
				{
					insert(Emoji, WordBar.text, { DefBar.text });
					insert(EmojiDef, DefBar.text, { WordBar.text });
					addSuccessfully = 3;
				}
				if (chooseSlang)
				{
					insert(Slang, WordBar.text, { DefBar.text });
					insert(SlangDef, DefBar.text, { WordBar.text });
					addSuccessfully = 3;
				}
			}
		}
		if (addSuccessfully == 3) DrawTextEx(bold, "Successful !", { 1000 - 60, 800 - 30 }, 60, 0, GREEN);
		else if (addSuccessfully == 2) DrawTextEx(bold, "Failed !", { 1000 - 24, 800 - 30 }, 60, 0, RED);
		EndDrawing();
	}
	ofstream fout;
	fout.open("../Dataset/EngEng.txt");
	WriteDictionaryToFile(EngEng, "", fout);
	fout.close();
	fout.open("../Dataset/EngVie.txt");
	WriteDictionaryToFile(EngVie, "", fout);
	fout.close();
	fout.open("../Dataset/VieEng.txt");
	WriteDictionaryToFile(VieEng, "", fout);
	fout.close();
	fout.open("../Dataset/Slang.txt");
	WriteDictionaryToFile(Slang, "", fout);
	fout.close();
	fout.open("../Dataset/Emoji.txt");
	WriteDictionaryToFile(Emoji, "", fout);
	fout.close();

	fout.open("../Dataset/Favor.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(favor[i], fout);
	}
	fout.close();
	fout.open("../Dataset/History.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(history[i], fout);
	}
	fout.close();

	for (int i = 0; i < 5; ++i) {
		deleteLL(history[i]);
		deleteLL(favor[i]);
	}
	DeleteAllTree(EngEng);
	DeleteAllTree(EngEngDef);
	DeleteAllTree(EngVie);
	DeleteAllTree(EngVieDef);
	DeleteAllTree(VieEng);
	DeleteAllTree(VieEngDef);
	DeleteAllTree(Slang);
	DeleteAllTree(SlangDef);
	DeleteAllTree(Emoji);
	DeleteAllTree(EmojiDef);
	CloseWindow();
}
void FavoriteListPage(const int screenWidth, const int screenHeight, trieNode*& VieEng, trieNode*& EngVie, trieNode*& EngEng, trieNode*& VieEngDef, trieNode*& EngVieDef, trieNode*& EngEngDef, trieNode*& Emoji, trieNode*& EmojiDef, trieNode*& Slang, trieNode*& SlangDef, Node* favor[], Node* history[])

{

	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);

	Textbox SearchBar2;
	SearchBar2.textbox = { 327 + 195, 307 - 150, 860, 60 }; //x+195, y-150
	bool isSearching2 = false;

	Textbox ActualSearchBar;
	ActualSearchBar.textbox = { 510 + 195, 307 - 150,860 - (510 - 327), 60 };

	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D arrow = LoadTexture("../resources/Arrow.png");
	Texture2D glass = LoadTexture("../resources/Magnifying Glass.png");
	Texture2D trashCan = LoadTexture("../resources/TrashCan.png");

	Rectangle chooseDictBox = { 327 + 195,306 - 150,174, 60 };
	bool choose = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	bool chooseEmoji = false;
	bool chooseSlang = false;

	bool isSearchingFav = false;

	NewPageButton Back;
	Back.button = { 1431,9,61,31 };

	vector <string> listFavorite;
	listFavorite.resize(0);

	int scrollSpeed = 20;
	int listFavoritePosY = 494;
	int listFavoriteLinePosY = 539;

	vector <string> tmpdef;
	int defPosY = 494;
	int starPosY = 497;
	int trashCanPosY = 494;

	vector <bool> displayListDef;
	displayListDef.resize(0);
	while (!WindowShouldClose())
	{
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, 1512, 982, navy);
		//--------------------------------------------------------------------------------------------------------------------------------------------

		DrawRectangle(134, 485, 523, 283, white);
		DrawRectangle(859, 485, 523, 283, white);


		if (CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
			chooseSlang = false;
			chooseEmoji = false;
		}
		if (choose) {  //{ 327,306,174, 60 }
			DrawRectangle(327 + 195, 306 - 150 + 30, 30, 30, white);
			DrawRectangle(327 + 195, 306 - 150 + 60, 174, 60, white);
			DrawRectangle(327 + 195, 306 - 150 + 120, 174, 60, white);
			DrawRectangle(327 + 195, 306 - 150 + 180, 174, 60, white);
			DrawRectangle(327 + 195, 306 - 150 + 240, 174, 60, white);
			DrawRectangle(327 + 195, 306 - 150 + 300, 174, 60, white);

			DrawLine(327 + 195, 306 - 150 + 61, 327 + 195 + 175, 307 - 150 + 61, blue);
			DrawLine(327 + 195, 306 - 150 + 120, 327 + 195 + 175, 307 - 150 + 120, blue);
			DrawLine(327 + 195, 306 - 150 + 180, 327 + 195 + 175, 307 - 150 + 180, blue);
			DrawLine(327 + 195, 306 - 150 + 240, 327 + 195 + 175, 307 - 150 + 240, blue);
			DrawLine(327 + 195, 306 - 150 + 300, 327 + 195 + 175, 307 - 150 + 300, blue);
			DrawLine(327 + 195, 306 - 150 + 360, 327 + 195 + 175, 307 - 150 + 360, blue);

			DrawTextEx(bold, "ENG-ENG", { 327 + 25 + 19 + 195,306 + 29 + 49 - 150 }, 35, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 327 + 25 + 19 + 195,306 + 29 + 49 + 60 - 150 }, 35, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 327 + 25 + 19 + 195,306 + 29 + 49 + 120 - 150 }, 35, 0, navy);
			DrawTextEx(bold, "SLANG", { 327 + 25 + 19 + 195,306 + 29 + 49 + 180 - 150 }, 35, 0, navy);
			DrawTextEx(bold, "EMOJI", { 327 + 25 + 19 + 195,306 + 29 + 49 + 240 - 150 }, 35, 0, navy);
		}
		//------------------------------------------------------------------------------------------
		vector <string> favoriteDef;
		favoriteDef.resize(0);
		//------------------------------------------------------------------------------------------
		if (CheckCollisionPointRec(mousePoint, { 327 + 195, 306 + 60 - 150, 174, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
			listFavoritePosY = 494;
			listFavoriteLinePosY = 539;
			defPosY = 494;
			starPosY = 497;
			trashCanPosY = 494;
		}
		if (chooseEE) {
			choose = false;
			listFavorite = viewList(favor[0]);
			if (CheckCollisionPointRec(mousePoint, { 134, 485, 523, 283 })) {
				listFavoritePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoritePosY > 494) listFavoritePosY = 494;
				listFavoriteLinePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoriteLinePosY > 539) listFavoriteLinePosY = 539;
				trashCanPosY += (GetMouseWheelMove() * scrollSpeed);
				if (trashCanPosY > 494) trashCanPosY = 494;
			}
			for (int i = 0; i < listFavorite.size(); i++)
			{
				DrawTextEx(bold, listFavorite[i].c_str(), { 149,listFavoritePosY + 54 * (float)i }, 28, 0, navy);
				DrawLine(134, listFavoriteLinePosY + 54 * i, 134 + 522, listFavoriteLinePosY + 54 * i, navy);
				DrawTexture(trashCan, 600, trashCanPosY + 54 * (float)i, WHITE);
				DrawRectangle(600, 217, 30, 268, navy);
				DrawRectangle(600, 48, 30, 109, navy);
				if (CheckCollisionPointRec(mousePoint, { 134,listFavoritePosY - 14 + 54 * (float)i ,457,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					displayListDef.resize(0);
					for (int j = 0; j < listFavorite.size(); ++j) {
						displayListDef.push_back(false);
					}
					displayListDef[i] = true;

					ActualSearchBar.lettercount = 0;
					ActualSearchBar.text[0] = '\0';
				}
				if (CheckCollisionPointRec(mousePoint, { 600, trashCanPosY + 54 * (float)i ,30,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					remove(favor[0], listFavorite[i]);
				}
			}
			if (displayListDef.size() > 0) {
				for (int k = 0; k < listFavorite.size(); ++k) {
					if (displayListDef[k]) {
						if (defPosY > 494) defPosY = 494;
						if (starPosY > 497) starPosY = 497;
						if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
							defPosY += (GetMouseWheelMove() * scrollSpeed);
							starPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						int newDefMark = 0;
						search(EngEng, listFavorite[k], favoriteDef);
						for (int i = 0; i < favoriteDef.size(); i++)
						{
							if (favoriteDef[i].size() > 50) {
								tmpdef = divideString(favoriteDef[i], 50);
								for (int j = 0; j < tmpdef.size(); ++j) {
									if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
									DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
								}
								newDefMark += tmpdef.size() - 1;
							}
							else {
								DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
								DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
							}
						}
					}
				}
			}
			if (checkExistFavor(favor[0], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0') {
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				if (defPosY > 494) defPosY = 494;
				if (starPosY > 497) starPosY = 497;
				if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
					defPosY += (GetMouseWheelMove() * scrollSpeed);
					starPosY += (GetMouseWheelMove() * scrollSpeed);
				}
				int newDefMark = 0;
				search(EngEng, ActualSearchBar.text, favoriteDef);
				for (int i = 0; i < favoriteDef.size(); i++)
				{
					if (favoriteDef[i].size() > 50) {
						tmpdef = divideString(favoriteDef[i], 50);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
						DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
					}
				}
			}
			if (!checkExistFavor(favor[0], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0')
			{
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				DrawTextEx(italic, "Favorite word not found", { 988,595 }, 34, 0, navy);
			}
			if (listFavorite.size() == 0)
			{
				DrawTextEx(italic, "There are no favorite words yet :( Please add one", { 204,613 }, 25, 0, navy);
			}
		}
		if (CheckCollisionPointRec(mousePoint, { 327 + 195, 306 + 120 - 150, 174, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
			listFavoritePosY = 494;
			listFavoriteLinePosY = 539;
			defPosY = 494;
			starPosY = 497;
			trashCanPosY = 494;
		}
		if (chooseEV) {
			choose = false;
			listFavorite = viewList(favor[1]);
			if (CheckCollisionPointRec(mousePoint, { 134, 485, 523, 283 })) {
				listFavoritePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoritePosY > 494) listFavoritePosY = 494;
				listFavoriteLinePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoriteLinePosY > 539) listFavoriteLinePosY = 539;
				trashCanPosY += (GetMouseWheelMove() * scrollSpeed);
				if (trashCanPosY > 494) trashCanPosY = 494;
			}
			for (int i = 0; i < listFavorite.size(); i++)
			{
				DrawTextEx(bold, listFavorite[i].c_str(), { 149,listFavoritePosY + 54 * (float)i }, 28, 0, navy);
				DrawLine(134, listFavoriteLinePosY + 54 * i, 134 + 522, listFavoriteLinePosY + 54 * i, navy);
				DrawTexture(trashCan, 600, trashCanPosY + 54 * i, WHITE);
				DrawRectangle(600, 217, 30, 268, navy);
				DrawRectangle(600, 48, 30, 109, navy);
				if (CheckCollisionPointRec(mousePoint, { 134,listFavoritePosY - 14 + 54 * (float)i ,457,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					displayListDef.resize(0);
					for (int j = 0; j < listFavorite.size(); ++j) {
						displayListDef.push_back(false);
					}
					displayListDef[i] = true;
					ActualSearchBar.lettercount = 0;
					ActualSearchBar.text[0] = '\0';
				}
				if (CheckCollisionPointRec(mousePoint, { 600, trashCanPosY + 54 * (float)i ,30,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					remove(favor[1], listFavorite[i]);
				}
			}
			if (displayListDef.size() > 0) {
				for (int k = 0; k < listFavorite.size(); ++k) {
					if (displayListDef[k]) {
						if (defPosY > 494) defPosY = 494;
						if (starPosY > 497) starPosY = 497;
						if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
							defPosY += (GetMouseWheelMove() * scrollSpeed);
							starPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						int newDefMark = 0;
						search(EngVie, listFavorite[k], favoriteDef);
						for (int i = 0; i < favoriteDef.size(); i++)
						{
							if (favoriteDef[i].size() > 50) {
								tmpdef = divideString(favoriteDef[i], 50);
								for (int j = 0; j < tmpdef.size(); ++j) {
									if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
									DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
								}
								newDefMark += tmpdef.size() - 1;
							}
							else {
								DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
								DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
							}
						}
					}
				}
			}
			if (checkExistFavor(favor[1], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0') {
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				if (defPosY > 494) defPosY = 494;
				if (starPosY > 497) starPosY = 497;
				if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
					defPosY += (GetMouseWheelMove() * scrollSpeed);
					starPosY += (GetMouseWheelMove() * scrollSpeed);
				}
				int newDefMark = 0;
				search(EngVie, ActualSearchBar.text, favoriteDef);
				for (int i = 0; i < favoriteDef.size(); i++)
				{
					if (favoriteDef[i].size() > 50) {
						tmpdef = divideString(favoriteDef[i], 50);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
						DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
					}
				}
			}
			if (!checkExistFavor(favor[1], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0')
			{
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				DrawTextEx(italic, "Favorite word not found", { 988,595 }, 34, 0, navy);
			}
			if (listFavorite.size() == 0)
			{
				DrawTextEx(italic, "There are no favorite words yet :( Please add one", { 204,613 }, 25, 0, navy);
			}
		}
		if (CheckCollisionPointRec(mousePoint, { 327 + 195, 306 + 180 - 150, 174, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
			listFavoritePosY = 494;
			listFavoriteLinePosY = 539;
			defPosY = 494;
			starPosY = 497;
			trashCanPosY = 494;
		}
		if (chooseVE) {
			choose = false;
			listFavorite = viewList(favor[2]);
			if (CheckCollisionPointRec(mousePoint, { 134, 485, 523, 283 })) {
				listFavoritePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoritePosY > 494) listFavoritePosY = 494;
				listFavoriteLinePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoriteLinePosY > 539) listFavoriteLinePosY = 539;
				trashCanPosY += (GetMouseWheelMove() * scrollSpeed);
				if (trashCanPosY > 494) trashCanPosY = 494;
			}
			for (int i = 0; i < listFavorite.size(); i++)
			{
				DrawTextEx(bold, listFavorite[i].c_str(), { 149,listFavoritePosY + 54 * (float)i }, 28, 0, navy);
				DrawLine(134, listFavoriteLinePosY + 54 * i, 134 + 522, listFavoriteLinePosY + 54 * i, navy);
				DrawTexture(trashCan, 600, trashCanPosY + 54 * (float)i, WHITE);
				DrawRectangle(600, 217, 30, 268, navy);
				DrawRectangle(600, 48, 30, 109, navy);
				if (CheckCollisionPointRec(mousePoint, { 134,listFavoritePosY - 14 + 54 * (float)i ,457,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					displayListDef.resize(0);
					for (int j = 0; j < listFavorite.size(); ++j) {
						displayListDef.push_back(false);
					}
					displayListDef[i] = true;
					ActualSearchBar.lettercount = 0;
					ActualSearchBar.text[0] = '\0';
				}
				if (CheckCollisionPointRec(mousePoint, { 600, trashCanPosY + 54 * (float)i ,30,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					remove(favor[2], listFavorite[i]);
				}
			}
			if (displayListDef.size() > 0) {
				for (int k = 0; k < listFavorite.size(); ++k) {
					if (displayListDef[k]) {
						if (defPosY > 494) defPosY = 494;
						if (starPosY > 497) starPosY = 497;
						if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
							defPosY += (GetMouseWheelMove() * scrollSpeed);
							starPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						int newDefMark = 0;
						search(VieEng, listFavorite[k], favoriteDef);
						for (int i = 0; i < favoriteDef.size(); i++)
						{
							if (favoriteDef[i].size() > 50) {
								tmpdef = divideString(favoriteDef[i], 50);
								for (int j = 0; j < tmpdef.size(); ++j) {
									if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
									DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
								}
								newDefMark += tmpdef.size() - 1;
							}
							else {
								DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
								DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
							}
						}
					}
				}
			}
			if (checkExistFavor(favor[2], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0') {
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				if (defPosY > 494) defPosY = 494;
				if (starPosY > 497) starPosY = 497;
				if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
					defPosY += (GetMouseWheelMove() * scrollSpeed);
					starPosY += (GetMouseWheelMove() * scrollSpeed);
				}
				int newDefMark = 0;
				search(VieEng, ActualSearchBar.text, favoriteDef);
				for (int i = 0; i < favoriteDef.size(); i++)
				{
					if (favoriteDef[i].size() > 50) {
						tmpdef = divideString(favoriteDef[i], 50);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
						DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
					}
				}
			}
			if (!checkExistFavor(favor[2], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0')
			{
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				DrawTextEx(italic, "Favorite word not found", { 988,595 }, 34, 0, navy);
			}
			if (listFavorite.size() == 0)
			{
				DrawTextEx(italic, "There are no favorite words yet :( Please add one", { 204,613 }, 25, 0, navy);
			}
		}
		if (CheckCollisionPointRec(mousePoint, { 327 + 195, 306 - 150 + 240, 174, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang = true;
			listFavoritePosY = 494;
			listFavoriteLinePosY = 539;
			defPosY = 494;
			starPosY = 497;
			trashCanPosY = 494;
		}
		if (CheckCollisionPointRec(mousePoint, { 327 + 195, 306 - 150 + 300, 174, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmoji = true;
			listFavoritePosY = 494;
			listFavoriteLinePosY = 539;
			defPosY = 494;
			starPosY = 497;
			trashCanPosY = 494;
		}
		if (chooseSlang)
		{
			choose = false;
			listFavorite = viewList(favor[3]);
			if (CheckCollisionPointRec(mousePoint, { 134, 485, 523, 283 })) {
				listFavoritePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoritePosY > 494) listFavoritePosY = 494;
				listFavoriteLinePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoriteLinePosY > 539) listFavoriteLinePosY = 539;
				trashCanPosY += (GetMouseWheelMove() * scrollSpeed);
				if (trashCanPosY > 494) trashCanPosY = 494;
			}
			for (int i = 0; i < listFavorite.size(); i++)
			{
				DrawTextEx(bold, listFavorite[i].c_str(), { 149,listFavoritePosY + 54 * (float)i }, 28, 0, navy);
				DrawLine(134, listFavoriteLinePosY + 54 * i, 134 + 522, listFavoriteLinePosY + 54 * i, navy);
				DrawTexture(trashCan, 600, trashCanPosY + 54 * (float)i, WHITE);
				DrawRectangle(600, 217, 30, 268, navy);
				DrawRectangle(600, 48, 30, 109, navy);
				if (CheckCollisionPointRec(mousePoint, { 134,listFavoritePosY - 14 + 54 * (float)i ,457,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					displayListDef.resize(0);
					for (int j = 0; j < listFavorite.size(); ++j) {
						displayListDef.push_back(false);
					}
					displayListDef[i] = true;
					ActualSearchBar.lettercount = 0;
					ActualSearchBar.text[0] = '\0';
				}
				if (CheckCollisionPointRec(mousePoint, { 600, trashCanPosY + 54 * (float)i ,30,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					remove(favor[3], listFavorite[i]);
				}
			}
			if (displayListDef.size() > 0) {
				for (int k = 0; k < listFavorite.size(); ++k) {
					if (displayListDef[k]) {
						if (defPosY > 494) defPosY = 494;
						if (starPosY > 497) starPosY = 497;
						if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
							defPosY += (GetMouseWheelMove() * scrollSpeed);
							starPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						int newDefMark = 0;
						search(Slang, listFavorite[k], favoriteDef);
						for (int i = 0; i < favoriteDef.size(); i++)
						{
							if (favoriteDef[i].size() > 50) {
								tmpdef = divideString(favoriteDef[i], 50);
								for (int j = 0; j < tmpdef.size(); ++j) {
									if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
									DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
								}
								newDefMark += tmpdef.size() - 1;
							}
							else {
								DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
								DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
							}
						}
					}
				}
			}
			if (checkExistFavor(favor[3], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0') {
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				if (defPosY > 494) defPosY = 494;
				if (starPosY > 497) starPosY = 497;
				if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
					defPosY += (GetMouseWheelMove() * scrollSpeed);
					starPosY += (GetMouseWheelMove() * scrollSpeed);
				}
				int newDefMark = 0;
				search(Slang, ActualSearchBar.text, favoriteDef);
				for (int i = 0; i < favoriteDef.size(); i++)
				{
					if (favoriteDef[i].size() > 50) {
						tmpdef = divideString(favoriteDef[i], 50);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
						DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
					}
				}
			}
			if (!checkExistFavor(favor[3], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0')
			{
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				DrawTextEx(italic, "Favorite word not found", { 988,595 }, 34, 0, navy);
			}
			if (listFavorite.size() == 0)
			{
				DrawTextEx(italic, "There are no favorite words yet :( Please add one", { 204,613 }, 25, 0, navy);
			}
		}
		if (chooseEmoji)
		{
			choose = false;
			listFavorite = viewList(favor[4]);
			if (CheckCollisionPointRec(mousePoint, { 134, 485, 523, 283 })) {
				listFavoritePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoritePosY > 494) listFavoritePosY = 494;
				listFavoriteLinePosY += (GetMouseWheelMove() * scrollSpeed);
				if (listFavoriteLinePosY > 539) listFavoriteLinePosY = 539;
				trashCanPosY += (GetMouseWheelMove() * scrollSpeed);
				if (trashCanPosY > 494) trashCanPosY = 494;
			}
			for (int i = 0; i < listFavorite.size(); i++)
			{
				DrawTextEx(bold, listFavorite[i].c_str(), { 149,listFavoritePosY + 54 * (float)i }, 28, 0, navy);
				DrawLine(134, listFavoriteLinePosY + 54 * i, 134 + 522, listFavoriteLinePosY + 54 * i, navy);
				DrawTexture(trashCan, 600, trashCanPosY + 54 * (float)i, WHITE);
				DrawRectangle(600, 217, 30, 268, navy);
				DrawRectangle(600, 48, 30, 109, navy);
				if (CheckCollisionPointRec(mousePoint, { 134,listFavoritePosY - 14 + 54 * (float)i ,457,54 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					displayListDef.resize(0);
					for (int j = 0; j < listFavorite.size(); ++j) {
						displayListDef.push_back(false);
					}
					displayListDef[i] = true;
					ActualSearchBar.lettercount = 0;
					ActualSearchBar.text[0] = '\0';
				}
				if (CheckCollisionPointRec(mousePoint, { 600, trashCanPosY + 54 * (float)i ,30,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					remove(favor[4], listFavorite[i]);
				}
			}
			if (displayListDef.size() > 0) {
				for (int k = 0; k < listFavorite.size(); ++k) {
					if (displayListDef[k]) {
						if (defPosY > 494) defPosY = 494;
						if (starPosY > 497) starPosY = 497;
						if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
							defPosY += (GetMouseWheelMove() * scrollSpeed);
							starPosY += (GetMouseWheelMove() * scrollSpeed);
						}
						int newDefMark = 0;
						search(Emoji, listFavorite[k], favoriteDef);
						for (int i = 0; i < favoriteDef.size(); i++)
						{
							if (favoriteDef[i].size() > 50) {
								tmpdef = divideString(favoriteDef[i], 50);
								for (int j = 0; j < tmpdef.size(); ++j) {
									if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
									DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
								}
								newDefMark += tmpdef.size() - 1;
							}
							else {
								DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
								DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
							}
						}
					}
				}
			}
			if (checkExistFavor(favor[4], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0') {
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				if (defPosY > 494) defPosY = 494;
				if (starPosY > 497) starPosY = 497;
				if (CheckCollisionPointRec(mousePoint, { 859, 485, 523, 283 })) {
					defPosY += (GetMouseWheelMove() * scrollSpeed);
					starPosY += (GetMouseWheelMove() * scrollSpeed);
				}
				int newDefMark = 0;
				search(Emoji, ActualSearchBar.text, favoriteDef);
				for (int i = 0; i < favoriteDef.size(); i++)
				{
					if (favoriteDef[i].size() > 50) {
						tmpdef = divideString(favoriteDef[i], 50);
						for (int j = 0; j < tmpdef.size(); ++j) {
							if (j == 0) DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
							DrawTextEx(bold, tmpdef[j].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark + j) }, 28, 0, navy);
						}
						newDefMark += tmpdef.size() - 1;
					}
					else {
						DrawTextEx(bold, "*", { 861,starPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
						DrawTextEx(bold, favoriteDef[i].c_str(), { 873,defPosY + 54 * (float)(i + newDefMark) }, 28, 0, navy);
					}
				}
			}
			if (!checkExistFavor(favor[4], ActualSearchBar.text) && ActualSearchBar.text[0] != '\0')
			{
				displayListDef.resize(0);
				for (int j = 0; j < listFavorite.size(); ++j) {
					displayListDef.push_back(false);
				}
				DrawTextEx(italic, "Favorite word not found", { 988,595 }, 34, 0, navy);
			}
			if (listFavorite.size() == 0)
			{
				DrawTextEx(italic, "There are no favorite words yet :( Please add one", { 204,613 }, 25, 0, navy);
			}
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;

		DrawRectangle(0, 0, 1512, 48, blue);
		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);
		DrawTextEx(bold, "FAVORITE", { 242,292 }, 54, 0, white);
		DrawTextEx(bold, "LIST", { 295,342 }, 54, 0, white);
		DrawTexture(logo, 245, 91, white);
		DrawRectangleRounded({ 134,442,222,54 }, 0.18, 0, yellow);
		DrawRectangleRounded({ 859,442,220,54 }, 0.18, 0, yellow);
		DrawTextEx(bold, "List of Words", { 149,442 }, 44, 0, navy);
		DrawTextEx(bold, "Definition", { 893,442 }, 44, 0, navy);

		DrawRectangleRounded(SearchBar2.textbox, 60, 0, white);
		DrawLine(327 + 195, 306 - 150 + 61, 327 + 195 + 175, 307 - 150 + 61, blue);
		DrawCircle(1132 + 20.5 + 195, 317 + 20.5 - 150, 20.5, yellow);
		DrawTexture(glass, 1143 + 195, 328 - 150, white);
		DrawLineEx({ 702,170 }, { 702,170 + 35 }, 4.0, navy);
		DrawTextEx(bold, "NONE", { 378 + 195,318 - 150 }, 37, 0, navy);
		DrawTexture(arrow, 474.41 + 195, 332 - 150, WHITE);

		if (!isSearching2) {
			DrawTextEx(italic, "Search for your favorite word...", { 525 + 195, 324 - 150 }, 28, 0, navy);
		}
		ActualSearchBar.worktextbox(isSearching2);
		DrawTextEx(bold, ActualSearchBar.text, { 525 + 195,324 - 150 }, 28, 0, navy);

		if (chooseEE) {
			DrawRectangle(338 + 195, 314 - 150, 122, 44, white);
			DrawTextEx(bold, "ENG-ENG", { 349 + 195, 319 - 150 }, 35, 0, navy);
		}
		if (chooseEV) {
			DrawRectangle(338 + 195, 314 - 150, 122, 44, white);
			DrawTextEx(bold, "ENG-VIE", { 355 + 195, 319 - 150 }, 35, 0, navy);
		}
		if (chooseVE) {
			DrawRectangle(338 + 195, 314 - 150, 122, 44, white);
			DrawTextEx(bold, "VIE-ENG", { 355 + 195, 319 - 150 }, 35, 0, navy);
		}
		if (chooseSlang) {
			DrawRectangle(338 + 195, 314 - 150, 122, 44, white);
			DrawTextEx(bold, "SLANG", { 369 + 195, 319 - 150 }, 35, 0, navy);
		}
		if (chooseEmoji) {
			DrawRectangle(338 + 195, 314 - 150, 122, 44, white);
			DrawTextEx(bold, "EMOJI", { 369 + 195, 319 - 150 }, 35, 0, navy);
		}
		EndDrawing();
	}
	ofstream fout;
	fout.open("../Dataset/EngEng.txt");
	WriteDictionaryToFile(EngEng, "", fout);
	fout.close();
	fout.open("../Dataset/EngVie.txt");
	WriteDictionaryToFile(EngVie, "", fout);
	fout.close();
	fout.open("../Dataset/VieEng.txt");
	WriteDictionaryToFile(VieEng, "", fout);
	fout.close();
	fout.open("../Dataset/Slang.txt");
	WriteDictionaryToFile(Slang, "", fout);
	fout.close();
	fout.open("../Dataset/Emoji.txt");
	WriteDictionaryToFile(Emoji, "", fout);
	fout.close();

	fout.open("../Dataset/Favor.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(favor[i], fout);
	}
	fout.close();
	fout.open("../Dataset/History.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(history[i], fout);
	}
	fout.close();

	for (int i = 0; i < 5; ++i) {
		deleteLL(history[i]);
		deleteLL(favor[i]);
	}
	DeleteAllTree(EngEng);
	DeleteAllTree(EngEngDef);
	DeleteAllTree(EngVie);
	DeleteAllTree(EngVieDef);
	DeleteAllTree(VieEng);
	DeleteAllTree(VieEngDef);
	DeleteAllTree(Slang);
	DeleteAllTree(SlangDef);
	DeleteAllTree(Emoji);
	DeleteAllTree(EmojiDef);
	CloseWindow();
}
void RevisionPage(const int screenWidth, const int screenHeight, trieNode*& VieEng, trieNode*& EngVie, trieNode*& EngEng, trieNode*& VieEngDef, trieNode*& EngVieDef, trieNode*& EngEngDef, trieNode*& Emoji, trieNode*& EmojiDef, trieNode*& Slang, trieNode*& SlangDef, Node* favor[], Node* history[]) {
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);

	Rectangle ChooseModeBox{ 1036,148 - 30,218,54 };
	Rectangle wordRevision{ 818,148 - 30,218,54 };
	Rectangle defRevision{ 818,202 - 30,218,54 };
	Rectangle ChooseDictBox{ 1036, 230, 218, 54 };
	Rectangle ChooseEEbox{ 818, 230, 218, 54 };
	Rectangle ChooseEVbox{ 818, 230 + 54, 218, 54 };
	Rectangle ChooseVEbox{ 818, 230 + 54 * 2, 218, 54 };
	Rectangle ChooseSlangbox{ 818, 230 + 54 * 3, 218, 54 };
	Rectangle ChooseEmobox{ 818, 230 + 54 * 4, 218, 54 };

	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };
	Color skin = { 252,213,155,255 };

	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D refreshBtn = LoadTexture("../resources/RefreshBtn.png");
	Texture2D arrow = LoadTexture("../resources/Arrow2.png");

	NewPageButton Back;
	Back.button = { 1431,9,61,31 };


	bool ChooseMode = false;
	bool ChooseWord = false;
	bool ChooseDef = false;

	bool chooseDict = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	bool chooseSlang = false;
	bool chooseEmo = false;

	string trueWord = "";
	string trueDef = "";
	vector<string> wrongdef(3);
	for (int i = 0; i < 3; ++i) {
		wrongdef[i] = "";
	}
	int randomNum = 0;
	bool correctAns = false;
	bool wrongAns = false;
	int positionWrong = 0;
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, 1512, 982, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangle(270, 342, 984, 104, white);
		DrawRectangle(270, 503, 984, 77, white);
		DrawRectangle(270, 628, 984, 77, white);
		DrawRectangle(270, 753, 984, 77, white);
		DrawRectangle(270, 878, 984, 77, white);
		DrawRectangle(270, 342, 984, 17, yellow);
		DrawRectangle(270, 503, 984, 17, skin);
		DrawRectangle(270, 628, 984, 17, skin);
		DrawRectangle(270, 753, 984, 17, skin);
		DrawRectangle(270, 878, 984, 17, skin);
		DrawRectangle(270, 292, 61, 49, yellow);
		DrawRectangle(1036, 148 - 30, 218, 54, yellow);
		DrawRectangleRec(ChooseDictBox, yellow);
		//Refresh button
		DrawTexture(refreshBtn, 283, 300, WHITE);
		DrawTexture(logo, 270, 80, WHITE);
		DrawTexture(arrow, 1057, 168 - 33 + 58 * 2, WHITE);
		DrawTexture(arrow, 1057, 168 - 30, WHITE);
		DrawTextEx(bold, "Revision", { 492,127 }, 54, 0, white);
		DrawTextEx(bold, "Tool", { 530,179 }, 54, 0, white);
		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		DrawTextEx(bold, "MODE", { 1098,154 - 30 }, 44, 0, navy);
		DrawTextEx(bold, "DICT", { 1108, 237 }, 44, 0, navy);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef, favor, history);

		if (CheckCollisionPointRec(mousePoint, ChooseModeBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ChooseMode = true;
			ChooseWord = false;
			ChooseDef = false;
		}
		if (ChooseMode)
		{
			DrawRectangle(818, 148 - 30, 218, 54, white);
			DrawRectangle(818, 202 - 30, 218, 54, white);
			DrawLine(818, 203 - 30, 818 + 218, 203 - 30, navy);
			DrawTextEx(bold, "Word revision", { 856,162 - 30 }, 30, 0, navy);
			DrawTextEx(bold, "Definition revision", { 829,213 - 30 }, 30, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, wordRevision) && ChooseMode)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseWord = true;
		if (CheckCollisionPointRec(mousePoint, defRevision) && ChooseMode)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseDef = true;
		if (ChooseWord)
		{
			DrawRectangleRec(ChooseModeBox, yellow);
			DrawTextEx(bold, "Word revision", { 1078,159 - 30 }, 30, 0, navy);
			ChooseMode = false;
		}
		if (ChooseDef)
		{
			DrawRectangleRec(ChooseModeBox, yellow);
			DrawTextEx(bold, "Definition revision", { 1047,162 - 30 }, 30, 0, navy);
			ChooseMode = false;
		}
		if (!CheckCollisionPointRec(mousePoint, ChooseModeBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseMode = false;

		if (CheckCollisionPointRec(mousePoint, ChooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			chooseDict = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
			chooseSlang = false;
			chooseEmo = false;
		}
		if (chooseDict) {
			DrawRectangleRec(ChooseEEbox, white);
			DrawRectangleRec(ChooseEVbox, white);
			DrawRectangleRec(ChooseVEbox, white);
			DrawRectangleRec(ChooseSlangbox, white);
			DrawRectangleRec(ChooseEmobox, white);

			DrawTextEx(bold, "ENG-ENG", { 876, 242 }, 30, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 876 + 1, 242 + 54 }, 30, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 876 + 2, 242 + 108 }, 30, 0, navy);
			DrawTextEx(bold, "SLANG", { 876 + 3, 242 + 54 * 3 }, 30, 0, navy);
			DrawTextEx(bold, "EMOJI", { 876 + 4, 242 + 54 * 4 }, 30, 0, navy);


			DrawLine(ChooseEEbox.x, ChooseEEbox.y + 54, ChooseEEbox.x + ChooseEEbox.width, ChooseEEbox.y + 54, navy);
			DrawLine(ChooseEVbox.x, ChooseEVbox.y + 54, ChooseEVbox.x + ChooseEVbox.width, ChooseEVbox.y + 54, navy);
			DrawLine(ChooseVEbox.x, ChooseVEbox.y + 54, ChooseVEbox.x + ChooseVEbox.width, ChooseVEbox.y + 54, navy);
			DrawLine(ChooseSlangbox.x, ChooseSlangbox.y + 54, ChooseSlangbox.x + ChooseSlangbox.width, ChooseSlangbox.y + 54, navy);
			DrawLine(ChooseEmobox.x, ChooseEmobox.y + 54, ChooseEmobox.x + ChooseEmobox.width, ChooseEmobox.y + 54, navy);
		}
		if (CheckCollisionPointRec(mousePoint, ChooseEEbox) && chooseDict)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		if (CheckCollisionPointRec(mousePoint, ChooseEVbox) && chooseDict)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		if (CheckCollisionPointRec(mousePoint, ChooseVEbox) && chooseDict)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		if (CheckCollisionPointRec(mousePoint, ChooseSlangbox) && chooseDict)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang = true;
		if (CheckCollisionPointRec(mousePoint, ChooseEmobox) && chooseDict)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmo = true;
		if (chooseEE)
		{
			DrawRectangleRec(ChooseDictBox, yellow);
			DrawTextEx(bold, "ENG-ENG", { 1094,242 }, 30, 0, navy);
			chooseDict = false;
		}
		if (chooseEV)
		{
			DrawRectangleRec(ChooseDictBox, yellow);
			DrawTextEx(bold, "ENG-VIE", { 1094,242 }, 30, 0, navy);
			chooseDict = false;
		}
		if (chooseVE)
		{
			DrawRectangleRec(ChooseDictBox, yellow);
			DrawTextEx(bold, "VIE-ENG", { 1094,242 }, 30, 0, navy);
			chooseDict = false;
		}
		if (chooseSlang)
		{
			DrawRectangleRec(ChooseDictBox, yellow);
			DrawTextEx(bold, "SLANG", { 1094,242 }, 30, 0, navy);
			chooseDict = false;
		}
		if (chooseEmo)
		{
			DrawRectangleRec(ChooseDictBox, yellow);
			DrawTextEx(bold, "EMOJI", { 1094,242 }, 30, 0, navy);
			chooseDict = false;
		}


		if (chooseEE && ChooseWord) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(EngEng, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}

			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseEV && ChooseWord) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(EngVie, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseVE && ChooseWord) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(VieEng, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseSlang && ChooseWord) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(Slang, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseEmo && ChooseWord) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(Emoji, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseEE && ChooseDef) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(EngEngDef, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseEV && ChooseDef) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(EngVieDef, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseVE && ChooseDef) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(VieEngDef, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseSlang && ChooseDef) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(SlangDef, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}
		if (chooseEmo && ChooseDef) {
			if (CheckCollisionPointRec(mousePoint, { 270,292,61,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				random1Word4Def(EmojiDef, trueWord, trueDef, wrongdef);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, 3);
				randomNum = dist(gen);
				correctAns = false;
				wrongAns = false;
				positionWrong = 0;
			}
			DrawTextEx(bold, trueWord.c_str(), { 293,387 }, 20, 0, navy);
			DrawTextEx(bold, trueDef.c_str(), { 293,540 + 125 * (float)randomNum }, 20, 0, navy);
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					DrawTextEx(bold, wrongdef[j].c_str(), { 293,540 + 125 * (float)i }, 20, 0, navy);
					++j;
				}
			}
			if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)randomNum, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				correctAns = true;
			}
			for (int i = 0; i < 4; ++i) {
				if (i != randomNum) {
					if (CheckCollisionPointRec(mousePoint, { 270, 503 + 125 * (float)i, 984, 77 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						wrongAns = true;
						positionWrong = i;
						break;
					}
				}
			}

			if (correctAns) {
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
			if (wrongAns) {
				DrawRectangle(270, 503 + 125 * positionWrong, 984, 17, RED);
				DrawRectangle(270, 503 + 125 * randomNum, 984, 17, GREEN);
			}
		}

		EndDrawing();
	}
	ofstream fout;
	fout.open("../Dataset/EngEng.txt");
	WriteDictionaryToFile(EngEng, "", fout);
	fout.close();
	fout.open("../Dataset/EngVie.txt");
	WriteDictionaryToFile(EngVie, "", fout);
	fout.close();
	fout.open("../Dataset/VieEng.txt");
	WriteDictionaryToFile(VieEng, "", fout);
	fout.close();
	fout.open("../Dataset/Slang.txt");
	WriteDictionaryToFile(Slang, "", fout);
	fout.close();
	fout.open("../Dataset/Emoji.txt");
	WriteDictionaryToFile(Emoji, "", fout);
	fout.close();

	fout.open("../Dataset/Favor.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(favor[i], fout);
	}
	fout.close();
	fout.open("../Dataset/History.txt");
	for (int i = 0; i < 5; ++i) {
		fout << i << endl;
		writeNode2File(history[i], fout);
	}
	fout.close();

	for (int i = 0; i < 5; ++i) {
		deleteLL(history[i]);
		deleteLL(favor[i]);
	}
	DeleteAllTree(EngEng);
	DeleteAllTree(EngEngDef);
	DeleteAllTree(EngVie);
	DeleteAllTree(EngVieDef);
	DeleteAllTree(VieEng);
	DeleteAllTree(VieEngDef);
	DeleteAllTree(Slang);
	DeleteAllTree(SlangDef);
	DeleteAllTree(Emoji);
	DeleteAllTree(EmojiDef);
	CloseWindow();
}