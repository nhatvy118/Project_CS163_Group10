#include <raylib.h>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include <string>


void WaitingPage(const int screenWidth, const int screenHeight, trieNode* VieEng,trieNode* EngVie,trieNode* EngEng,trieNode* VieEngDef,trieNode* EngVieDef,trieNode* EngEngDef,trieNode* Emoji,trieNode* EmojiDef,trieNode* Slang,trieNode* SlangDef) 
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
	StartBtn.button = {655,700,200,100};
	////---------------------------------------------------------------------------------------------------
	
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();

		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, navy);
		DrawTexture(logo2, 611, 218, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 629,537 }, 60, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 644,611 }, 32, 0, white);

		DrawTexture(DrawStartBtn, 655, 700, WHITE);
		StartBtn.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);
		EndDrawing();
	}
	CloseWindow();
}
void HomePage(const int screenWidth, const int screenHeight, trieNode* VieEng, trieNode* EngVie, trieNode* EngEng, trieNode* VieEngDef, trieNode* EngVieDef, trieNode* EngEngDef, trieNode* Emoji, trieNode* EmojiDef, trieNode* Slang, trieNode* SlangDef)
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
	// Set up searching components
	Rectangle SearchBar = { 551, 122, 911, 60 };;
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
	AddWordBtn.button = {188,12,166,31};
	NewPageButton FavoriteList;
	FavoriteList.button = { 15,9,131,31 };
	NewPageButton RevisionBtn;
	RevisionBtn.button = { 388,12,120,31 };

	Rectangle randomWordBox = { 551, 227, 197, 60 };
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
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0,screenWidth, screenHeight, white);
		DrawRectangle(0, 0, 1512, 340, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangle(0, 340, 1512, 48, yellow);
		DrawTexture(logo, 15, 100, WHITE);

		DrawTexture(randomBtn, 550, 227, WHITE);
		DrawRectangleRounded(SearchBar , 60, 0, white);
		if (!isSearching) {
			if (!SearchDefMode) DrawTextEx(italic, "Search for a word...", { 774,138 }, 28, 0, navy);
			else DrawTextEx(italic, "Search for a definition...", { 774,138 }, 28, 0, navy);
		}
		ActualSearchBar.worktextbox(isSearching);
		DrawTextEx(bold, ActualSearchBar.text, { 774,138 }, 28, 0, navy);

		//DrawRectangleRounded(randomWordBox, 60, 0, { 11, 64, 156,255 });
		//DrawRectangleRounded(VocabBox, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(DefinitionBox, 15, 0, { 253, 190, 52, 255 });
		//DrawCircle(1426.5, 149.5, 20.5, {253, 190, 52, 255});
		DrawTextEx(bold, "Favorite List", { 15,12 }, 24, 0, white);
		DrawTextEx(bold, "Add new words", { 188,12 }, 24, 0, white);
		AddWordBtn.workbutton(mousePoint, AddWordPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);
		FavoriteList.workbutton(mousePoint, FavoriteListPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);
		DrawTextEx(bold, "Revision", { 388,12 }, 24, 0, white);
		DrawTextEx(bold, "Reset Data", { 1369,12 }, 24, 0, white);
		DrawTextEx(bold, "or", { 634,189 }, 30, 0, white);
		//DrawTextEx(bold, "Random a word", { 565,242 }, 31, 0, WHITE);// 581, 245

		DrawTextEx(bold, "DICTIONARY", { 248,146 }, 49, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 219, 196 }, 41, 0, white);
		DrawLineEx({ 155, 10 }, { 155, 38 }, 3.0, white);
		DrawLineEx({ 355, 10 }, { 355, 38 }, 3.0, white);
		DrawLineEx({ 744,133 }, { 744, 168 }, 4.0, { 16,49,107,255 });

		//DrawTexture(glass, 1417, 138, WHITE);
		//DrawTexture(whiteStar, 647, 398, WHITE);
		//DrawTexture(editIcon, 645, 611, WHITE);

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
			DrawLine(551, 182+60, 736, 182+60, blue);
			DrawLine(551, 182+120, 736, 182+120, blue);
			DrawLine(551, 182+180, 736, 182+180, blue);
			DrawLine(551, 182+240, 736, 182+240, blue);

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
			DrawRectangle(575, 128, 160, 40,white);
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
		

		RevisionBtn.workbutton(mousePoint, RevisionPage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);

		if (SearchDefMode) DrawTexture(SearchDefModeBtn, 1405, 132, WHITE);
		else DrawTexture(SearchWordModeBtn, 1405, 132, WHITE);
		if (CheckCollisionPointRec(mousePoint, { 1405,132,40,40 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (SearchDefMode) SearchDefMode = false;
			else SearchDefMode = true;
		}
		DrawTexture(SearchBtn, 1345, 132, WHITE);
		
		vector<string> ans;
		ans.resize(0);
		if (ActualSearchBar.text[0] != '\0' ) {
			if (DictType == "ENG-ENG") {
				if (!SearchDefMode) {
					isDisplayingResult = search(EngEng, ActualSearchBar.text, ans);
				}
				else isDisplayingResult = search(EngEngDef, ActualSearchBar.text, ans);
			}			
			if (DictType == "ENG-VIE") {
				if (!SearchDefMode) {
					isDisplayingResult = search(EngVie, ActualSearchBar.text, ans);
				}
				else isDisplayingResult = search(EngVieDef, ActualSearchBar.text, ans);
			}
			if (DictType == "VIE-ENG") {
				if (!SearchDefMode) {
					isDisplayingResult = search(VieEng, ActualSearchBar.text, ans);
				}
				else isDisplayingResult = search(VieEngDef, ActualSearchBar.text, ans);
			}
			if (DictType == "SLANG") {
				if (!SearchDefMode) {
					isDisplayingResult = search(Slang, ActualSearchBar.text, ans);
				}
				else isDisplayingResult = search(SlangDef, ActualSearchBar.text, ans);
			}
			if (DictType == "EMOJI") {
				if (!SearchDefMode) {
					isDisplayingResult = search(Emoji, ActualSearchBar.text, ans);
				}
				else isDisplayingResult = search(EmojiDef, ActualSearchBar.text, ans);
			}
		}		

		if (isDisplayingResult) {
			/*for (int i = 0; i < ans.size(); ++i) {
				string tmp = "";
				int cnt = 0;
				int j = 0;
				int size = ans[i].size();
				while (j < size) {
					tmp = ans[i].substr(j, min(j + 100, size-1));
					int dem = tmp.size();
					while (tmp[tmp.size()] != ' ') dem--;
					string str = tmp.substr(0, dem);
					DrawTextEx(bold, str.c_str(), {30, (520 + 50 * (float)i)}, 30, 0, navy);
					j += dem;
				}
			}*/
			DrawRectangleRounded(Vocab, 0.3, 0, yellow);
			DrawRectangleRounded(Definition, 0.3, 0, yellow);
			DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 2, Vocab.x + 1400, Vocab.y + Vocab.height - 2, yellow);
			DrawLine(Vocab.x + 10, Vocab.y + Vocab.height - 1, Vocab.x + 1400, Vocab.y + Vocab.height - 1, yellow);
			DrawLine(Definition.x + 10, Definition.y + Definition.height - 2, Definition.x + 1400, Definition.y + Definition.height - 2, yellow);
			DrawLine(Definition.x + 10, Definition.y + Definition.height - 1, Definition.x + 1400, Definition.y + Definition.height - 1, yellow);
			DrawRectangleRounded({ Vocab.x + 158,Vocab.y,49,49 }, 0.3, 0, yellow);
			DrawRectangleRounded({ Vocab.x + 1365 ,Vocab.y,49,49 }, 0.3, 0, yellow);
			DrawRectangleRounded({ Definition.x + 1365,Definition.y,49,49 }, 0.3, 0, yellow);
			DrawTexture(trashcan, Vocab.x + 1376, Vocab.y + 10, WHITE);
			DrawTexture(editIcon, Definition.x + 1370+3, Definition.y + 5, WHITE);
			DrawTextEx(bold, "Vocab", { 69,412 }, 43, 0, navy);
			DrawTextEx(bold, "Definition", { 67,530 }, 43, 0, navy);
				
			if (CheckCollisionPointRec(mousePoint, { Vocab.x + 167, Vocab.y + 8, 32,30 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				if (isFavorite) isFavorite = false;
				else if (!isFavorite) isFavorite = true;
			}
			if (!isFavorite) DrawTexture(whiteStar, Vocab.x + 167, Vocab.y + 8, GRAY);
			else DrawTexture(blueStar, Vocab.x + 167, Vocab.y + 8, GRAY);

			DrawTextEx(bold, ActualSearchBar.text, { 72, 470 }, 30, 0, navy);

			for (int i = 0; i < ans.size(); ++i) {
				DrawTextEx(bold, ans[i].c_str(), { 72, (590 + 50 * (float)i) }, 30, 0, navy);
			}
			if (CheckCollisionPointRec(mousePoint, { Vocab.x + 1365, Vocab.y, 49, 49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				confirmDelete = true;
			}
			if (confirmDelete)
			{
				DrawRectangleRounded({ 501,375,511,243 }, 0.08, 0, blue);
				DrawRectangleRounded({ 542,534,161,49 }, 0.08, 0, yellow);
				DrawRectangleRounded({ 811,534,161, 49 }, 0.08, 0, yellow);
				DrawTexture(closeIcon, 966, 393, WHITE);
				DrawTextEx(bold, "Delete Confirmation", { 585,448 }, 48, 0, white);
				DrawTextEx(bold, "Yes", { 597,537 }, 44, 0, navy);
				DrawTextEx(bold, "No", { 874,537 }, 44, 0, navy);
				if (CheckCollisionPointRec(mousePoint, { 965,389,31,27 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					confirmDelete = false;
				}
				if (CheckCollisionPointRec(mousePoint, { 811,534,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					confirmDelete = false;
				}
				string str(ActualSearchBar.text);
				vector <string> tmp;
				tmp.resize(0);
				if (CheckCollisionPointRec(mousePoint, { 542,534,161,49 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {	
					if (DictType == "ENG-ENG")
					{
						DeleteAWord(EngEng, str, 0,tmp);
						vector <string> tmp2 = tmp;
						for (auto x : tmp)
						{
							DeleteAWord(EngEngDef, x, 0, tmp2);
						}
					}
					else
					if (DictType == "ENG-VIE")
					{
						DeleteAWord(EngVie, str, 0,tmp);
						vector <string> tmp2 = tmp;
						for (auto x : tmp)
						{
							DeleteAWord(EngVieDef, x, 0, tmp2);
						}
					}
					else
					if (DictType == "VIE-ENG")
					{
						DeleteAWord(VieEng, str, 0,tmp);
						vector <string> tmp2 = tmp;
						for (auto x : tmp)
						{
							DeleteAWord(VieEngDef, x, 0, tmp2);
						}
					}
					else
					if (DictType == "SLANG")
					{
						DeleteAWord(Slang, str, 0,tmp);
						vector <string> tmp2 = tmp;
						for (auto x : tmp)
						{
							DeleteAWord(SlangDef, x, 0, tmp2);
						}
					}
					else
					if (DictType == "EMOJI")
					{
						DeleteAWord(Emoji, str, 0,tmp);
						vector <string> tmp2 = tmp;
						for (auto x : tmp)
						{
							DeleteAWord(EmojiDef, x, 0, tmp2);
						}
					}
					confirmDelete = false;
				}
			}

		}
		else {
			DrawTextEx(bold, "No Data Available", { 30+450, (520) }, 100, 0, RED);
			DrawTextEx(bold, "Please try again", { 30+50+450, (600) }, 90, 0, RED);

		};
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
				resetData = false;
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
			}
		}
		EndDrawing();
	}
	CloseWindow();
}
void AddWordPage(const int screenWidth, const int screenHeight, trieNode* VieEng, trieNode* EngVie, trieNode* EngEng, trieNode* VieEngDef, trieNode* EngVieDef, trieNode* EngEngDef, trieNode* Emoji, trieNode* EmojiDef, trieNode* Slang, trieNode* SlangDef) {
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
		DrawRectangle(0, 0, screenWidth, screenHeight,navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawTexture(logo, 265, 126, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 255,331 }, 49, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 212,392 }, 41, 0, white);

		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);

		DrawRectangleRounded({ 667,295,125,90 },0.18, 0, yellow);
		DrawRectangleRounded({ 667,487,199,90 },0.18, 0, yellow);
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
		DrawTextEx(bold, DefBar.text, { 690,550}, 28, 0, navy);

		DrawTextEx(bold, "Please choose the dictionary",{132,522},43,0, yellow);
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
			DrawRectangle(217, 687+60, 261, 60, yellow);
			DrawRectangle(217, 687+120, 261, 60, yellow);
			DrawRectangle(217, 687+180, 261, 60, yellow);
			DrawRectangle(217, 687+ 240, 261, 60, yellow);

			DrawLine(217, 747, 478, 747,navy);
			DrawLine(217, 747+60, 478, 747+60,navy);
			DrawLine(217, 747+120, 478, 747+120,navy);
			DrawLine(217, 747+180, 478, 747+180,navy);
			DrawLine(217, 747+240, 478, 747+240,navy);

			DrawTextEx(bold, "ENG-ENG", { 285,697 }, 40, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 292,697+60 }, 40, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 293,697+120 }, 40, 0, navy);
			DrawTextEx(bold, "SLANG", { 293+10,697+180 }, 40, 0, navy);
			DrawTextEx(bold, "EMOJI", { 293+15,697+240 }, 40, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, {217,687,261,60}) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-ENG", { 287, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687+60,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-VIE", { 290, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687+120,261,60 }) && choose) {
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
			DrawTextEx(bold, "SLANG", { 285+20, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687 + 240,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmo = true;
		}
		if (chooseEmo) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "EMOJI", { 285+20, 637 }, 40, 0, navy);
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
		if (addSuccessfully==3) DrawText("Successful !", 1036, 827, 40, yellow);
		else if(addSuccessfully==2) DrawText("Failed ! ", 1036, 827, 40, yellow);
		EndDrawing();
	}
	CloseWindow();
}
void FavoriteListPage(const int screenWidth, const int screenHeight, trieNode* VieEng, trieNode* EngVie, trieNode* EngEng, trieNode* VieEngDef, trieNode* EngVieDef, trieNode* EngEngDef, trieNode* Emoji, trieNode* EmojiDef, trieNode* Slang, trieNode* SlangDef)

{
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);

	Textbox SearchBar;
	SearchBar.textbox = { 766, 171, 911-200, 60 };
	bool isSearching = false;

	//Textbox SearchBar2;
	//SearchBar2.textbox = { 133,382, 522, 60};
	//bool isSearching2 = false;

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

	Rectangle chooseDictBox = { 570,171,193, 60 };
	Rectangle chooseDictBox2 = { 439,496,216,43 };
	bool choose = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	bool chooseEmoji = false;
	bool chooseSlang = false;

	bool choose2 = false;
	bool chooseEE2 = false;
	bool chooseEV2 = false;
	bool chooseVE2 = false;
	bool chooseEmoji2 = false;
	bool chooseSlang2 = false;

	NewPageButton Back;
	Back.button = { 1431,9,61,31 };

	while (!WindowShouldClose()) 
	{
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, 1512, 982, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangleRounded({ 133,496,135,54 }, 0.18, 0, yellow);
		DrawRectangleRounded({ 856,496,220,54 }, 0.18, 0, yellow);
		DrawRectangleRounded({ 438,496,218,54 }, 0.18, 0, yellow);
		//DrawRectangleRounded({ 133,382, 522, 60 }, 1.047, 0, white);
		DrawRectangleRounded({ 570, 171, 911, 60  }, 1.047, 0, white);
		DrawRectangleRounded(SearchBar.textbox, 60, 0, white);
		//DrawRectangleRounded(SearchBar2.textbox, 60, 0, white);
		DrawLineEx({ 763,184 }, { 763, 219 }, 4.0, { 16,49,107,255 });
		if (!isSearching) {
			DrawTextEx(italic, "Add a word to your favorite list...", { 793,189 }, 28, 0, navy);
		}
		SearchBar.worktextbox(isSearching);
		//if (!isSearching2) {
		//	DrawTextEx(italic, "Search for your favorite word...", { 159, 400 }, 28, 0, navy);
		//}
		//SearchBar2.worktextbox(isSearching2);
		DrawTextEx(bold, SearchBar.text, { 774,138 }, 28, 0, navy);
		//DrawTextEx(bold, SearchBar2.text, { 54,387 }, 28, 0, navy);
		DrawRectangle(133, 539, 523, 283, white);
		DrawRectangle(856, 539, 523, 283, white);
		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		DrawTextEx(bold, "Word", { 162,496 }, 44, 0, navy);
		DrawTextEx(bold, "Definition", { 890,496 }, 44, 0, navy);
		DrawTextEx(bold, "FAVORITE", { 234,143 }, 54, 0, white);
		DrawTextEx(bold, "LIST", { 287,193 }, 54, 0, white);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);
		DrawTexture(logo, 15, 100, white);
		//DrawCircle(611.5, 412.5, 20.5, yellow);
		DrawCircle(1448.5, 200.5, 20.5, yellow);
		//DrawTexture(glass, 602, 401, white);
		DrawTexture(glass, 1439, 189, white);

		DrawTextEx(bold, "None", { 632,180 }, 40, 0, navy);
		DrawTextEx(bold, "None", { 500,496 }, 40, 0, navy);
		DrawTexture(arrow, 727.41, 196, WHITE);
		DrawTexture(arrow, 620.41, 513, WHITE);
		if (CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
			chooseSlang = false;
			chooseEmoji = false;
		}
		if (choose) { //{ 570, 171, 911, 60 }; //{ 551, 122, 911, 60 };
			DrawRectangle(570, 201, 30, 30, white);
			DrawRectangle(570, 231, 185, 60, white);
			DrawRectangle(570, 231 + 60, 185, 60, white);
			DrawRectangle(570, 231 + 120, 185, 60, white);
			DrawRectangle(570, 231 + 180, 185, 60, white);
			DrawRectangle(570, 231 + 240, 185, 60, white);

			DrawLine(570, 231, 755, 231, blue);
			DrawLine(570, 231 + 60, 755, 231 + 60, blue);
			DrawLine(570, 231 + 120, 755, 231 + 120, blue);
			DrawLine(570, 231 + 180, 755, 231 + 180, blue);
			DrawLine(570, 231 + 240, 755, 231 + 240, blue);

			DrawTextEx(bold, "ENG-ENG", { 595+19,200+49 }, 30, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 620,200+49 + 60 }, 30, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 620,200+49 + 120 }, 30, 0, navy);
			DrawTextEx(bold, "SLANG", { 628,200 + 49 + 180 }, 30, 0, navy);
			DrawTextEx(bold, "EMOJI", { 628,200 + 49 + 240 }, 30, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, { 570, 231, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangle(575+19, 128+49, 160, 40, white);
			DrawTextEx(bold, "ENG-ENG", { 585+19, 132+49 }, 40, 0, navy);
			choose = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 551+19, 182+49 + 60, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangle(575+19, 128+49, 160, 40, white);
			DrawTextEx(bold, "ENG-VIE", { 585+19, 132+49 }, 40, 0, navy);
			choose = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 551+19, 182+49 + 120, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		}
		if (chooseVE) {
			DrawRectangle(575+19, 128+49, 160, 40, white);
			DrawTextEx(bold, "VIE-ENG", { 585+19, 132+49 }, 40, 0, navy);
			choose = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 551 + 19, 182 + 49 + 180, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang = true;
		}
		if (CheckCollisionPointRec(mousePoint, { 551 + 19, 182 + 49 + 240, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmoji = true;
		}
		if (chooseSlang)
		{
			DrawRectangle(575 + 19, 128 + 49, 160, 40, white);
			DrawTextEx(bold, "SLANG", { 628, 132 + 49 }, 40, 0, navy);
			choose = false;
		}
		if (chooseEmoji)
		{
			DrawRectangle(575 + 19, 128 + 49, 160, 40, white);
			DrawTextEx(bold, "EMOJI", { 628, 132 + 49 }, 40, 0, navy);
			choose = false;
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;

		if (CheckCollisionPointRec(mousePoint, chooseDictBox2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose2 = true;
			chooseEE2 = false;
			chooseEV2 = false;
			chooseVE2 = false;
			chooseSlang2 = false;
			chooseEmoji2 = false;
		}
		if (choose2) { //{ 570, 171, 911, 60 }; //{ 439,496,216,43 }//{ 551, 122, 911, 60 };
			DrawRectangle(438, 534, 30, 30, yellow);
			DrawRectangle(438, 534, 218, 60, yellow);
			DrawRectangle(438, 534 + 60, 218, 60, yellow);
			DrawRectangle(438, 534 + 120, 218, 60, yellow);
			DrawRectangle(438, 534 + 180, 218, 60, yellow);
			DrawRectangle(438, 534 + 240, 218, 60, yellow);

			DrawLine(438, 538, 657, 538, blue);
			DrawLine(438, 538 + 60, 657, 538 + 60, blue);
			DrawLine(438, 538 + 120, 657, 538 + 120, blue);
			DrawLine(438, 538 + 180, 657, 538 + 180, blue);
			DrawLine(438, 538 + 240, 657, 538 + 240, blue);
			

			DrawTextEx(bold, "ENG-ENG", { 595 -112,175 + 374 }, 40, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 595 -112+5,175 + 374 + 60 }, 40, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 595 -112+5,175 + 374 + 120 }, 40, 0, navy);
			DrawTextEx(bold, "SLANG", { 595 - 112+15,175 + 374 + 180 }, 40, 0, navy);
			DrawTextEx(bold, "EMOJI", { 595 - 112+15,175 + 374 + 240 }, 40, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE2 = true;
		}
		if (chooseEE2) {
			DrawRectangle(575 -112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "ENG-ENG", { 585 -112, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534 + 60, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV2 = true;
		}
		if (chooseEV2) {
			DrawRectangle(575 -112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "ENG-VIE", { 585 -112+5, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534 + 120, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE2 = true;
		}
		if (chooseVE2) {
			DrawRectangle(575 -112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "VIE-ENG", { 585 -112+5, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534 + 180, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseSlang2 = true;
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534 + 240, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEmoji2 = true;
		}
		if (chooseSlang2) {
			DrawRectangle(575 - 112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "SLANG", { 585 - 112+15, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (chooseEmoji2) {
			DrawRectangle(575 - 112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "EMOJI", { 585 - 112+15, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose2 = false;

		EndDrawing();
	}
	CloseWindow();
}
void RevisionPage(const int screenWidth, const int screenHeight, trieNode* VieEng, trieNode* EngVie, trieNode* EngEng, trieNode* VieEngDef, trieNode* EngVieDef, trieNode* EngEngDef, trieNode* Emoji, trieNode* EmojiDef, trieNode* Slang, trieNode* SlangDef) {
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);

	Rectangle ChooseModeBox{ 1036,148,218,54 };
	Rectangle wordRevision{ 818,148,218,54 };
	Rectangle defRevision{ 818,202,218,54 };

	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D refreshBtn = LoadTexture("../resources/RefreshBtn.png");
	Texture2D arrow = LoadTexture("../resources/Arrow2.png");

	NewPageButton Back;
	Back.button = { 1431,9,61,31 };


	bool ChooseMode = false;
	bool ChooseWord = false;
	bool ChooseDef = false;

	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0, 1512, 982, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangle(270, 372, 984, 221, white);
		DrawRectangle(270, 649, 404, 85, white);
		DrawRectangle(270, 774, 404, 85, white);
		DrawRectangle(850, 649, 404, 85, white);
		DrawRectangle(850, 774, 404, 85, white);
		DrawRectangle(270, 372, 984, 17, yellow);
		DrawRectangle(270, 649, 404, 17, yellow);
		DrawRectangle(270, 774, 404, 17, yellow);
		DrawRectangle(850, 649, 404, 17, yellow);
		DrawRectangle(850, 774, 404, 17, yellow);
		DrawRectangle(270, 323, 61, 49, yellow);
		DrawRectangle(1036, 148, 218, 54, yellow);
		//Refresh button
		DrawTexture(refreshBtn, 283, 331, WHITE);
		DrawTexture(logo, 270, 105, WHITE);
		DrawTexture(arrow, 1057, 168, WHITE);
		DrawTextEx(bold, "Revision", { 492,152 }, 45, 0, white);
		DrawTextEx(bold, "Tool", { 536,204 }, 45, 0, white);
		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		DrawTextEx(bold, "MODE", { 1098,154 }, 44, 0, navy);
		Back.workbutton(mousePoint, HomePage, VieEng, EngVie, EngEng, VieEngDef, EngVieDef, EngEngDef, Emoji, EmojiDef, Slang, SlangDef);

		if (CheckCollisionPointRec(mousePoint, ChooseModeBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ChooseMode = true;
			ChooseWord = false;
			ChooseDef = false;
		}
		if (ChooseMode)
		{
			DrawRectangle(818, 148, 218, 54, white);
			DrawRectangle(818, 202, 218, 54, white);
			DrawLine(818, 203, 818 + 218, 203, navy);
			DrawTextEx(bold, "Word revision", { 856,162 }, 30, 0, navy);
			DrawTextEx(bold, "Definition revision", { 829,213 }, 30, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, wordRevision) && ChooseMode)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseWord = true;
		if (CheckCollisionPointRec(mousePoint, defRevision) && ChooseMode)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseDef = true;
		if (ChooseWord)
		{
			DrawRectangleRec(ChooseModeBox, yellow);
			DrawTextEx(bold, "Word revision", { 1078,159 }, 30, 0, navy);
			ChooseMode = false;
		}
		if (ChooseDef)
		{
			DrawRectangleRec(ChooseModeBox, yellow);
			DrawTextEx(bold, "Definition revision", { 1047,162 }, 30, 0, navy);
			ChooseMode = false;
		}
		if (!CheckCollisionPointRec(mousePoint, ChooseModeBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ChooseMode = false;
		EndDrawing();
	}
	CloseWindow();
}