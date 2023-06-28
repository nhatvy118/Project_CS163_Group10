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
	StartBtn.button = {660,700,200,100};

	while (!WindowShouldClose()) {
		mousePoint = GetMousePosition();

		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, navy);
		DrawTexture(logo2, 611, 218, WHITE);
		DrawTextEx(bold, "DICTIONARY", { 629,537 }, 60, 0, white);
		DrawTextEx(italic, "by APCS K22 Group 10", { 644,611 }, 32, 0, white);

		DrawTexture(DrawStartBtn, 660, 700, WHITE);
		StartBtn.workbutton(mousePoint, HomePage);
		EndDrawing();
	}
	CloseWindow();
}
void HomePage(const int screenWidth, const int screenHeight) {
	SetTargetFPS(60);
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 96, 0, 0);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 96, 0, 0);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 96, 0, 0);

	Color white = { 242, 247, 255,255 };
	Color blue = { 11,64,156,255 };
	Color navy = { 16,49,107,255 };
	Color yellow = { 253,190,52,255 };

	Textbox SearchBar;
	SearchBar.textbox = { 551, 122, 911, 60 };
	bool isSearching = false;

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
	while (!WindowShouldClose()) {
		BeginDrawing();
		DrawRectangle(0, 0,screenWidth, screenHeight, white);
		DrawRectangle(0, 0, 1512, 340, navy);
		DrawRectangle(0, 0, 1512, 48, blue);

		DrawRectangleRounded(SearchBar.textbox , 60, 0, WHITE);
		if (!isSearching) {
			DrawTextEx(italic, "Search for a word...", { 774,138 }, 28, 0, navy);
		}
		SearchBar.worktextbox(isSearching);
		DrawTextEx(bold, SearchBar.text, { 774,138 }, 28, 0, navy);

		//DrawRectangleRounded(randomWordBox, 60, 0, { 11, 64, 156,255 });
		//DrawRectangleRounded(Vocab, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(Definition, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(VocabBox, 15, 0, { 253, 190, 52, 255 });
		//DrawRectangleRounded(DefinitionBox, 15, 0, { 253, 190, 52, 255 });
		//DrawCircle(1426.5, 149.5, 20.5, {253, 190, 52, 255});
		//DrawTextEx(bold, "Favorite List", { 15,12 }, 24, 0, WHITE);
		//DrawTextEx(bold, "Add new words", { 188,12 }, 24, 0, WHITE);
		//DrawTextEx(bold, "Revision", { 388,12 }, 24, 0, WHITE);
		//DrawTextEx(bold, "Reset Data", { 1369,12 }, 24, 0, WHITE);
		DrawTextEx(bold, "or", { 634,189 }, 30, 0, WHITE);
		//DrawTextEx(bold, "Random a word", { 565,242 }, 31, 0, WHITE);// 581, 245
		//DrawTextEx(bold, "Vocab", { 72,392 }, 43, 0, { 11, 64, 156,255 });
		//DrawTextEx(bold, "Definition", { 67,607 }, 43, 0, { 11, 64, 156,255 });
		DrawTextEx(bold, "DICTIONARY", { 248,146 }, 49, 0, WHITE);
		DrawTextEx(italic, "by APCS K22 Group 10", { 219, 196 }, 41, 0, WHITE);
		//DrawLineEx({ 155, 10 }, { 155, 38 }, 3.0, WHITE);
		//DrawLineEx({ 355, 10 }, { 355, 38 }, 3.0, WHITE);
		DrawLineEx({ 744,133 }, { 744, 168 }, 4.0, { 16,49,107,255 });
		////First half of arrow
		//DrawLineEx({ 717.41, 145 }, { 725.895, 153.485 }, 2.0, { 16,49,107,255 });
		////Second half of arrow
		//DrawLineEx({ 734.41, 145 }, { 725.895, 153.485 }, 2.0, { 16,49,107,255 });
		//DrawLineEx({ 670,439 }, { 58,439 }, 1, { 253, 190, 52, 255 });
		//DrawLineEx({ 670,653 }, { 58,653 }, 1, { 253, 190, 52, 255 });

		DrawTexture(logo, 15, 100, WHITE);
		//DrawTexture(glass, 1417, 138, WHITE);
		//DrawTexture(whiteStar, 647, 398, WHITE);
		//DrawTexture(editIcon, 645, 611, WHITE);

		EndDrawing();

	}
	CloseWindow();
}