#include <iostream>
#include <raylib.h>
#include "struct.h"
#include "FrontEnd.h"

void Textbox::worktextbox(bool& isSearching) {
	if (CheckCollisionPointRec(GetMousePosition(), textbox)) mouseontextbox = true;
	else mouseontextbox = false;
	if (mouseontextbox)
	{
		// Get char pressed (unicode character) on the queue
		int key = GetCharPressed();

		// Check if more characters have been pressed on the same frame
		while (key > 0)
		{
			// NOTE: Only allow keys in range [32..125]
			if ((key >= 32) && (key <= 125) && (lettercount < MAX_INPUT_CHARS))
			{
				text[lettercount] = (char)key;
				text[lettercount + 1] = '\0'; // Add null terminator at the end of the string.
				lettercount++;
			}

			key = GetCharPressed();  // Check next character in the queue
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			isSearching = false;
			lettercount--;
			if (lettercount < 0) lettercount = 0;
			text[lettercount] = '\0';
		}
		if (IsKeyDown(KEY_BACKSPACE)) {
			isSearching = false;
			if (delay_time < BACKSPACE_DELAY) {
				delay_time += GetFrameTime();
			}
			else {
				lettercount--;
				if (lettercount < 0) lettercount = 0;
				text[lettercount] = '\0';
			}
		}
		else delay_time = 0.0f;
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_V)) {
			isSearching = false;
			lettercount = 0;
			const char* a = GetClipboardText();
			if (a[0] == '\'' || a[0] == '\"') {
				for (int i = 1; i < strlen(a) - 1; ++i) {
					text[lettercount++] = a[i];
				}
				text[lettercount] = '\0';
			}
			else {
				for (int i = 0; i < strlen(a); ++i) {
					text[lettercount++] = a[i];
				}
				text[lettercount] = '\0';
			}
		}
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_Z)) {
			isSearching = false;
			text[0] = '\0';
			lettercount = 0;
		}
	}
	if (mouseontextbox || text[0] != '\0') {
		isSearching = true;
	}
	else isSearching = false;

}
void NewPageButton::workbutton(Vector2 mousePoint, void(*func)(const int screenWidth, const int screenHeight, trieNode* VieEng,
	trieNode* EngVie,
	trieNode* EngEng,
	trieNode* VieEngDef,
	trieNode* EngVieDef,
	trieNode* EngEngDef,
	trieNode* Emoji,
	trieNode* EmojiDef,
	trieNode* Slang,
	trieNode* SlangDef), 
	trieNode* VieEng,
	trieNode* EngVie,
	trieNode* EngEng,
	trieNode* VieEngDef,
	trieNode* EngVieDef,
	trieNode* EngEngDef,
	trieNode* Emoji,
	trieNode* EmojiDef,
	trieNode* Slang,
	trieNode* SlangDef) {
	if (CheckCollisionPointRec(mousePoint, button)) {          // Check button state
		//DrawRectangleLines((int)button.x, (int)button.y, (int)button.width, (int)button.height, BLACK);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) action = true;
	}
	else action = false;
	if (action)
	{
		EndDrawing();
		func(screenWidth, screenHeight, VieEng,EngVie,EngEng,VieEngDef,EngVieDef,EngEngDef,Emoji,EmojiDef,Slang,SlangDef);
	}
}