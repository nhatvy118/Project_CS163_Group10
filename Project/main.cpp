#include<iostream>
#include "struct.h"
#include "function.h"
#include "FrontEnd.h"
#include "raylib.h"
using namespace std;

int main() {
	const int screenW = 1512;
	const int screenH = 982;
	InitWindow(screenW, screenH, "Group 10 Dictionary");
	HomePage(screenW, screenH);

	return 0;
}