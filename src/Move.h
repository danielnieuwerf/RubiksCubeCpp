#pragma once
class Move
{
public:
	char initial_face;
	char destination_face;
	int x_index;
	int y_index;

	// Constructor
	Move(char i, char d, int x, int y) {
		initial_face = i;
		destination_face = d;
		x_index = x;
		y_index = y;
	}
};