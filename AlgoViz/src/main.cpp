#include "raylib-cpp.hpp"
#include "raymath.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
void DrawGridRect(int width, int height, int boxSize, raylib::Vector2 mousePos);

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "AlgoViz");

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

bool isContainted(std::vector<raylib::Vector2> arrayToCheck, const raylib::Vector2& valueToCheck) {
	for (auto& value : arrayToCheck) {
		if (value == valueToCheck)
			return true;
	}
	return false;
}

std::vector<raylib::Vector2> clickedPositions;
bool clicked = false;
raylib::Vector2 startingPosition;
raylib::Vector2 endingPosition;
void DrawGridRect(int width, int height, int boxSize, raylib::Vector2 mousePos) {
	const int padding = 10;
	for (int i = 1; i < width / (boxSize + padding); i++) {
		for (int j = 1; j < height / (boxSize + padding); j++) {
			raylib::Vector2 boxPos(i * (boxSize + padding), j * (boxSize + padding));
			if (mousePos.Distance(raylib::Vector2(boxPos.x + boxSize / 2, boxPos.y + boxSize / 2)) < boxSize / 2) {

				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !clicked) {
					startingPosition = boxPos;
					clicked = true;
				}


				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !isContainted(clickedPositions, boxPos) && clicked && !(startingPosition == boxPos)) {
					clickedPositions.push_back(boxPos);
				}

				//FOR HOVER EFFECT
				if (!isContainted(clickedPositions, boxPos))
					boxPos.DrawRectangle(raylib::Vector2(boxSize, boxSize), BLUE);

			}

			if (clicked)
				startingPosition.DrawRectangle(raylib::Vector2(boxSize, boxSize), RED);

			if (!isContainted(clickedPositions, boxPos))
				DrawRectangleLines(boxPos.x, boxPos.y, boxSize, boxSize, BLUE);

			for (auto& pos : clickedPositions) {
				pos.DrawRectangle(raylib::Vector2(boxSize, boxSize), BLACK);
			}
		}
	}

}
