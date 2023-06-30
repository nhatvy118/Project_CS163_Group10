#include <raylib.h>
#include "FrontEnd.h"

void WaitingPage(const int screenWidth, const int screenHeight) {
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Texture2D logo2 = LoadTexture("../resources/School Logo2.png");

	Texture2D DrawStartBtn = LoadTexture("../resources/StartBtn.png");
	NewPageButton StartBtn;
	StartBtn.button = {655,700,200,100};

	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();

		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, navy);
		DrawTexture(logo2, 611, 218, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 629,537 }, 60, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 644,611 }, 32, 0, white);

		DrawTexture(DrawStartBtn, 655, 700, WHITE);
		StartBtn.workbutton(mousePoint, HomePage);
		EndDrawing();
	}
	CloseWindow();
}
void HomePage(const int screenWidth, const int screenHeight) {
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Rectangle SearchBar = { 551, 122, 911, 60 };;
	Textbox ActualSearchBar;
	ActualSearchBar.textbox = { 731, 122, 731, 60 };
	bool isSearching = false;

	NewPageButton AddWordBtn;
	AddWordBtn.button = {188,12,166,31};
	NewPageButton FavoriteList;
	FavoriteList.button = { 15,9,131,31 };



	Rectangle randomWordBox = { 551, 227, 197, 60 };
	Rectangle Vocab = { 41,391,161,49 };
	Rectangle Definition = { 41, 605,207,49 };
	Rectangle VocabBox = { 639,391,49,49 };
	Rectangle DefinitionBox = { 639, 605, 49, 49 };
	Texture2D logo = LoadTexture("../resources/School Logo.png");
	Texture2D glass = LoadTexture("../resources/Magnifying Glass.png");
	Texture2D whiteStar = LoadTexture("../resources/White Star.png");
	Texture2D blueStar = LoadTexture("../resources/Blue Star.png");
	Texture2D editIcon = LoadTexture("../resources/Edit Icon.png");
	Texture2D arrow = LoadTexture("../resources/Arrow.png");

	Rectangle chooseDictBox = { 551,122,180,60 };
	bool choose = false;
	bool chooseEE = false;
	bool chooseEV = false;
	bool chooseVE = false;
	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();
		BeginDrawing();
		DrawRectangle(0, 0,screenWidth, screenHeight, white);
		DrawRectangle(0, 0, 1512, 340, navy);
		DrawRectangle(0, 0, 1512, 48, blue);
		DrawRectangle(0, 340, 1512, 48, yellow);
		DrawTexture(logo, 15, 100, WHITE);

		DrawRectangleRounded(SearchBar , 60, 0, white);
		if (!isSearching) {
			DrawTextEx(italic, "Search for a word...", { 774,138 }, 28, 0, navy);
		}
		ActualSearchBar.worktextbox(isSearching);
		DrawTextEx(bold, ActualSearchBar.text, { 774,138 }, 28, 0, navy);

		//DrawRectangleRounded(randomWordBox, 60, 0, { 11, 64, 156,255 });
		//DrawRectangleRounded(Vocab, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(Definition, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(VocabBox, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(DefinitionBox, 15, 0, { 253, 190, 52, 255 });
		//DrawCircle(1426.5, 149.5, 20.5, {253, 190, 52, 255});
		DrawTextEx(bold, "Favorite List", { 15,12 }, 24, 0, white);
		DrawTextEx(bold, "Add new words", { 188,12 }, 24, 0, white);
		AddWordBtn.workbutton(mousePoint, AddWordPage);
		FavoriteList.workbutton(mousePoint, FavoriteListPage);
		DrawTextEx(bold, "Revision", { 388,12 }, 24, 0, white);
		DrawTextEx(bold, "Reset Data", { 1369,12 }, 24, 0, white);
		DrawTextEx(bold, "or", { 634,189 }, 30, 0, white);
		//DrawTextEx(bold, "Random a word", { 565,242 }, 31, 0, WHITE);// 581, 245
		//DrawTextEx(bold, "Vocab", { 72,392 }, 43, 0, { 11, 64, 156,255 });
		//DrawTextEx(bold, "Definition", { 67,607 }, 43, 0, { 11, 64, 156,255 });
		DrawTextEx(bold, "DICTIONARY", { 248,146 }, 49, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 219, 196 }, 41, 0, white);
		DrawLineEx({ 155, 10 }, { 155, 38 }, 3.0, white);
		DrawLineEx({ 355, 10 }, { 355, 38 }, 3.0, white);
		DrawLineEx({ 744,133 }, { 744, 168 }, 4.0, { 16,49,107,255 });
		////First half of arrow
		//DrawLineEx({ 717.41, 145 }, { 725.895, 153.485 }, 2.0, { 16,49,107,255 });
		////Second half of arrow
		//DrawLineEx({ 734.41, 145 }, { 725.895, 153.485 }, 2.0, { 16,49,107,255 });

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
		}
		if (choose) { //{ 551, 122, 911, 60 };
			DrawRectangle(551, 152, 30, 30, white);
			DrawRectangle(551, 182, 185, 60, white);
			DrawRectangle(551, 182 + 60, 185, 60, white);
			DrawRectangle(551, 182 + 120, 185, 60, white);

			DrawLine(551, 182, 736, 182, blue);
			DrawLine(551, 182+60, 736, 182+60, blue);
			DrawLine(551, 182+120, 736, 182+120, blue);

			DrawTextEx(bold, "ENG-ENG", { 595,200 }, 30, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 595,200 + 60 }, 30, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 595,200 + 120 }, 30, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangle(575, 128, 160, 40,white);
			DrawTextEx(bold, "ENG-ENG", { 585, 132 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 60, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "ENG-VIE", { 585, 132 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 551, 182 + 120, 185, 60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		}
		if (chooseVE) {
			DrawRectangle(575, 128, 160, 40, white);
			DrawTextEx(bold, "VIE-ENG", { 585, 132 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;
		EndDrawing();

	}
	CloseWindow();
}
void AddWordPage(const int screenWidth, const int screenHeight) {
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
		Back.workbutton(mousePoint, HomePage);

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


		//confirmBtnAction = false;
		//if (CheckCollisionPointRec(mousePoint, btnBoundsconfirmBtn)) {
		//	//DrawRectangleLines((int)btnBoundsconfirmBtn.x, (int)btnBoundsconfirmBtn.y, (int)btnBoundsconfirmBtn.width, (int)btnBoundsconfirmBtn.height, BLACK);
		//	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) confirmBtnAction = true;
		//}
		//else if (IsKeyPressed(KEY_ENTER)) confirmBtnAction = true;
		//else confirmBtnState = 0;
		//if (confirmBtnAction) {
		//	if (createASchoolYear(schoolyear.text)) {
		//		confirmBtnFalseDisplay = false;
		//		EndDrawing();
		//		ViewSchoolYearsPage(screenWidth, screenHeight, CurrentUser);
		//	}
		//	else confirmBtnFalseDisplay = true;
		//}
		//if (confirmBtnFalseDisplay) DrawTextEx(bold, "Invalid data or this year already existed. Try again!", { 495, 359 }, 25, 0, RED);
		//// Calculate button frame rectangle to draw depending on button state
		//sourceRecconfirmBtn.y = confirmBtnState * frameHeightconfirmBtn;
		//DrawTextureRec(confirmBtn, sourceRecconfirmBtn, { btnBoundsconfirmBtn.x, btnBoundsconfirmBtn.y }, WHITE); // Draw button frame
		DrawTexture(confirm, 969, 643, WHITE);

		//Choose Dictionary
		DrawRectangleRec(chooseDictBox, WHITE);
		DrawTextEx(bold, "Choose Dict", { 265,637 }, 40, 0, navy);

		if (CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose = true;
			chooseEE = false;
			chooseEV = false;
			chooseVE = false;
		}
		if (choose) { //{ 217,627,261,60 };
			DrawRectangle(217, 687, 261, 60, yellow);
			DrawRectangle(217, 687+60, 261, 60, yellow);
			DrawRectangle(217, 687+120, 261, 60, yellow);

			DrawLine(217, 747, 478, 747,navy);
			DrawLine(217, 747+60, 478, 747+60,navy);
			DrawLine(217, 747+120, 478, 747+120,navy);
			DrawTextEx(bold, "ENG-ENG", { 285,697 }, 40, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 292,697+60 }, 40, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 293,697+120 }, 40, 0, navy);
		}
		if (CheckCollisionPointRec(mousePoint, {217,687,261,60}) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEE = true;
		}
		if (chooseEE) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-ENG", { 285, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687+60,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseEV = true;
		}
		if (chooseEV) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "ENG-VIE", { 285, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (CheckCollisionPointRec(mousePoint, { 217,687+120,261,60 }) && choose) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE = true;
		}
		if (chooseVE) {
			DrawRectangleRec(chooseDictBox, yellow);
			DrawTextEx(bold, "VIE-ENG", { 285, 637 }, 40, 0, navy);
			choose = false;
			//semesternametmp = (char*)"Fall";
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;


		EndDrawing();
	}
	CloseWindow();
}
void FavoriteListPage(const int screenWidth, const int screenHeight)
{
	Vector2 mousePoint = { 0.0f, 0.0f };
	SetTargetFPS(60);

	Textbox SearchBar;
	SearchBar.textbox = { 766, 171, 911-200, 60 };
	bool isSearching = false;

	Textbox SearchBar2;
	SearchBar2.textbox = { 133,382, 522, 60};
	bool isSearching2 = false;

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

	bool choose2 = false;
	bool chooseEE2 = false;
	bool chooseEV2 = false;
	bool chooseVE2 = false;

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
		DrawRectangleRounded({ 133,382, 522, 60 }, 1.047, 0, white);
		DrawRectangleRounded({ 570, 171, 911, 60  }, 1.047, 0, white);
		DrawRectangleRounded(SearchBar.textbox, 60, 0, white);
		DrawRectangleRounded(SearchBar2.textbox, 60, 0, white);
		DrawLineEx({ 763,184 }, { 763, 219 }, 4.0, { 16,49,107,255 });
		if (!isSearching) {
			DrawTextEx(italic, "Add a word to your favorite list...", { 793,189 }, 28, 0, navy);
		}
		SearchBar.worktextbox(isSearching);
		if (!isSearching2) {
			DrawTextEx(italic, "Search for your favorite word...", { 159, 400 }, 28, 0, navy);
		}
		SearchBar2.worktextbox(isSearching2);
		DrawTextEx(bold, SearchBar.text, { 774,138 }, 28, 0, navy);
		DrawTextEx(bold, SearchBar2.text, { 54,387 }, 28, 0, navy);
		DrawRectangle(133, 539, 523, 283, white);
		DrawRectangle(856, 539, 523, 283, white);
		DrawTextEx(bold, "Back", { 1431,9 }, 33, 0, white);
		DrawTextEx(bold, "Word", { 162,496 }, 44, 0, navy);
		DrawTextEx(bold, "Definition", { 890,496 }, 44, 0, navy);
		DrawTextEx(bold, "FAVORITE", { 234,143 }, 54, 0, white);
		DrawTextEx(bold, "LIST", { 287,193 }, 54, 0, white);
		Back.workbutton(mousePoint, HomePage);
		DrawTexture(logo, 15, 100, white);
		DrawCircle(611.5, 412.5, 20.5, yellow);
		DrawCircle(1448.5, 200.5, 20.5, yellow);
		DrawTexture(glass, 602, 401, white);
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
		}
		if (choose) { //{ 570, 171, 911, 60 }; //{ 551, 122, 911, 60 };
			DrawRectangle(570, 201, 30, 30, white);
			DrawRectangle(570, 231, 185, 60, white);
			DrawRectangle(570, 231 + 60, 185, 60, white);
			DrawRectangle(570, 231 + 120, 185, 60, white);

			DrawLine(570, 231, 736, 231, blue);
			DrawLine(570, 231 + 60, 736, 231 + 60, blue);
			DrawLine(570, 231 + 120, 736, 231 + 120, blue);

			DrawTextEx(bold, "ENG-ENG", { 595+19,200+49 }, 30, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 595+19,200+49 + 60 }, 30, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 595+19,200+49 + 120 }, 30, 0, navy);
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
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose = false;

		if (CheckCollisionPointRec(mousePoint, chooseDictBox2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			choose2 = true;
			chooseEE2 = false;
			chooseEV2 = false;
			chooseVE2 = false;
		}
		if (choose2) { //{ 570, 171, 911, 60 }; //{ 439,496,216,43 }//{ 551, 122, 911, 60 };
			DrawRectangle(438, 534, 30, 30, yellow);
			DrawRectangle(438, 534, 218, 60, yellow);
			DrawRectangle(438, 534 + 60, 218, 60, yellow);
			DrawRectangle(438, 534 + 120, 218, 60, yellow);

			DrawLine(438, 538, 633, 538, blue);
			DrawLine(438, 538 + 60, 633, 538 + 60, blue);
			DrawLine(438, 538 + 120, 633, 538 + 120, blue);

			DrawTextEx(bold, "ENG-ENG", { 595 -112,175 + 374 }, 40, 0, navy);
			DrawTextEx(bold, "ENG-VIE", { 595 -112,175 + 374 + 60 }, 40, 0, navy);
			DrawTextEx(bold, "VIE-ENG", { 595 -112,175 + 374 + 120 }, 40, 0, navy);
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
			DrawTextEx(bold, "ENG-VIE", { 585 -112, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (CheckCollisionPointRec(mousePoint, { 438, 534 + 120, 218, 60 }) && choose2) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) chooseVE2 = true;
		}
		if (chooseVE2) {
			DrawRectangle(575 -112, 124 + 374, 160, 40, yellow);
			DrawTextEx(bold, "VIE-ENG", { 585 -112, 124 + 374 }, 40, 0, navy);
			choose2 = false;
		}
		if (!CheckCollisionPointRec(mousePoint, chooseDictBox2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choose2 = false;

		EndDrawing();
	}
	CloseWindow();
}