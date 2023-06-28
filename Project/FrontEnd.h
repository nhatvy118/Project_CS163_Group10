#pragma once
#include <iostream>
#include <raylib.h>
using namespace std;

const int MAX_INPUT_CHARS = 200;
const float BACKSPACE_DELAY = 0.5f;

struct Textbox {
	char text[MAX_INPUT_CHARS + 1] = "\0";
	int lettercount = 0;
	float delay_time = 0.0f;
	Rectangle textbox;
	bool mouseontextbox = false;
	void worktextbox(bool& somethingfalsedisplay);
};

struct NewPageButton {
	const int screenWidth = 1512;
	const int screenHeight = 982;
	Rectangle button = { 0, 0, 0, 0 };
	bool mouseonbutton = false;
	bool action = false;
	void workbutton(Vector2 mousePoint, void(*func)(const int screenWidth, const int screenHeight));
};

void WaitingPage(const int screenWidth, const int screenHeight);
void HomePage(const int screenWidth, const int screenHeight);