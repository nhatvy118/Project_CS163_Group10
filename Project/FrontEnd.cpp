#include <raylib.h>

void HomePage(const int screenWidth, const int screenHeight) {
	Font bold = LoadFontEx("../Fonts/SourceSansPro-Bold.ttf", 120, 0, 250);
	Font regular = LoadFontEx("../Fonts/SourceSansPro-Regular.ttf", 120, 0, 250);
	Font italic = LoadFontEx("../Fonts/SourceSansPro-Italic.ttf", 120, 0, 250);

	while (!WindowShouldClose()) {
		BeginDrawing();
		DrawRectangle(0, 0, float(screenWidth), float(screenHeight), WHITE);
		DrawRectangle(0, 0, 1512, 340, { 16,49,107,255 });
		DrawRectangle(0, 0, 1512, 48, { 11, 64, 156,255 });
		DrawTextEx(bold, "Favorite List", { 15,12 }, 24, 0, WHITE);
		DrawTextEx(bold, "Add new words", { 188,12 }, 24, 0, WHITE);
		DrawTextEx(bold, "Revision", { 388,12 }, 24, 0, WHITE);
		DrawLineEx({ 155, 10 }, { 155, 38 }, 3.0, WHITE);
		DrawLineEx({ 355, 10 }, { 355, 38 }, 3.0, WHITE);
		EndDrawing();
	}
}