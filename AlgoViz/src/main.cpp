#include "raylib-cpp.hpp"
#include "raymath.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
void DrawGridRect(int width, int height, int boxSize, Vector2 mousePos);

int main(void)
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);


	// Main game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		const raylib::Vector2 mousePos = GetMousePosition();
		DrawGridRect(screenWidth, screenHeight, 25, mousePos);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}


std::vector < raylib::Vector2 > clickedPos;
void DrawGridRect(int width, int height, int boxSize, Vector2 mousePos) {
	const int padding = 10;
	for (int i = 1; i < width / (boxSize + padding); i++)
	{
		for (int j = 1; j < height / (boxSize + padding); j++)
		{
			int boxPosX = i * (boxSize + padding);
			int boxPosY = j * (boxSize + padding);
			if (Vector2Distance(mousePos, Vector2{ (float)(boxPosX + boxSize / 2), (float)(boxPosY + boxSize / 2) }) < boxSize / 2) {
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
					raylib::Vector2 valueToAdd = { (float)boxPosX, (float)boxPosY };
					clickedPos.push_back(valueToAdd);
				}
				else {
					DrawRectangle(boxPosX, boxPosY, boxSize, boxSize, BLUE);
				}

			}
			else {
				for (const raylib::Vector2& pos : clickedPos) {
					DrawRectangleV(pos, raylib::Vector2((float)boxSize, (float)boxSize), RED);
				}
				DrawRectangleLines(boxPosX, boxPosY, boxSize, boxSize, BLUE);
			}
		}
	}
}
