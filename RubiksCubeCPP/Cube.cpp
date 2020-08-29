#include "Cube.h"

// Constructors
Cube::Cube() {
	// initialise cube to solved state
	vector<char> line{};
	for (int i = 0; i < 3; ++i)
		line.push_back('x');

	for (int j = 0; j < 3; ++j) {
		top[j] = line;
		bottom[j] = line;
		north[j] = line;
		south[j] = line;
		east[j] = line;
		west[j] = line;
	}

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			top[i][j] = 'o';
			bottom[i][j] = 'b';
			north[i][j] = 'w';
			west[i][j] = 'y';
			south[i][j] = 'g';
			east[i][j] = 'r';
		}

}

Cube::Cube(vector<vector<char>> t, vector<vector<char>> b, vector<vector<char>> n, vector<vector<char>> w, vector<vector<char>> s, vector<vector<char>> e){
	top = t;
	bottom = b;
	north = n;
	west = w;
	east = e;
	south = s;
}

// Operator overloading
bool Cube::operator==(Cube cube) {
	return top == cube.top && bottom == cube.bottom && south == cube.south && north == cube.north && west == cube.west && east == cube.east;
}

void Cube::operator=(Cube cube) {
	top = cube.top;
	bottom = cube.bottom;
	south = cube.south;
	north = cube.north;
	west = cube.west;
	east = cube.east;
}

// Helper functions
void Cube::print() {
	string t{};
	string b{};
	string n{};
	string s{};
	string e{};
	string w{};

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			t += top[i][j];
			b += bottom[i][j];
			n += north[i][j];
			s += south[i][j];
			e += east[i][j];
			w += west[i][j];
		}
	cout << "-----------------------" << endl;
	cout << "Distance from completion: " << distance_from_completion() << endl;
	cout << "Top: " << endl << t.substr(0, 3) << endl;
	cout << t.substr(3, 3) << endl;
	cout << t.substr(6, 3) << endl;
	cout << "Bottom: " << endl << b.substr(0, 3) << endl;
	cout << b.substr(3, 3) << endl;
	cout << b.substr(6, 3) << endl;
	cout << "North: " << endl << n.substr(0, 3) << endl;
	cout << n.substr(3, 3) << endl;
	cout << n.substr(6, 3) << endl;
	cout << "East: " << endl << e.substr(0, 3) << endl;
	cout << e.substr(3, 3) << endl;
	cout << e.substr(6, 3) << endl;
	cout << "South: " << endl << s.substr(0, 3) << endl;
	cout << s.substr(3, 3) << endl;
	cout << s.substr(6, 3) << endl;
	cout << "West: " << endl << w.substr(0, 3) << endl;
	cout << w.substr(3, 3) << endl;
	cout << w.substr(6, 3) << endl;
	cout << "-----------------------" << endl;

}

int Cube::distance_from_completion() {
	// Return number of squares away from completion
	// Returns 0 if Rubik's cube is solved.
	int distance = 54;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			distance -= (top[i][j] == 'o');		// true is 1, false is 0 
			distance -= (bottom[i][j] == 'b');
			distance -= (north[i][j] == 'w');
			distance -= (south[i][j] == 'g');
			distance -= (east[i][j] == 'r');
			distance -= (west[i][j] == 'y');
		}

	return distance;
}

void Cube::rotate_face(char face, bool clockwise) {
	/*
	Rotate face clockwise or anticlockwise 90 degrees
	*/
	vector<vector<char>> f = top; 	// Create copy of the correct face and store it in f
	switch (face) {
	case 'b':
		f = bottom;
		break;
	case 't':
		f = top;
		break;
	case 'n':
		f = north;
		break;
	case 'e':
		f = east;
		break;
	case 's':
		f = south;
		break;
	case 'w':
		f = west;
		break;
	default:
		return;
	}

	if (clockwise) {
		vector<vector<char>> copy = f;
		for (int i = 0; i < 3; ++i) {
			vector<char> row = f[i];

			for (int j = 0; j < 3; ++j) {
				copy[j][2 - i] = row[j];
			}
		}
		f = copy;	// update face to rotated face

		// Update the correct face
		switch (face) {
		case 'b':
			bottom = f;
			break;
		case 't':
			top = f;
			break;
		case 'n':
			north = f;
			break;
		case 'e':
			east = f;
			break;
		case 's':
			south = f;
			break;
		case 'w':
			west = f;
			break;
		default:
			return;
		}
	}
	else {
		for (int i = 0; i < 3; ++i) {
			Cube::rotate_face(face, true);	// anticlockwise equivalent to clockwise 3 times
		}
	}

}

int Cube::flip_around_1(int x) {
	if (x == 2)
		return 0;
	if (x == 1)
		return 1;
	return 2;
}

void Cube::move(char initial_face, char destination_face, int index_x, int index_y) {
	/* Move square at initial_face[index_x][index_y] onto destination face
	 Assertions:
	 initial face cannot be opposite to destination face or equal to initial face
	 initial face must be one of {t,b,n,w,s,e}
	 0<= index_x, index_y <3
	*/
	// Exit function if any of these assertions are not met
	if (index_x < 0 || index_y < 0 || index_x>2 || index_y>2)
		return;
	// check for valid faces input
	if (initial_face == destination_face)
		return;
	string valid_faces = "newstb";
	if (find(valid_faces.begin(), valid_faces.end(), initial_face) == valid_faces.end() ||
		find(valid_faces.begin(), valid_faces.end(), destination_face) == valid_faces.end())
		return;

	string faces{};
	faces += initial_face;
	faces += destination_face;
	sort(faces.begin(), faces.end());
	if (faces == "bt" || faces == "ns" || faces == "ew")
		return;

	// If we reach here the move is guaranteed to be valid
	// Convert all moves to one of {"tn", "ts", "tw", "te", "wn", "ws"}
	if (initial_face == 'w' && destination_face == 't') {
		initial_face = 't';
		destination_face = 'e';
	}
	else if (initial_face == 'b' && destination_face == 'w') {
		initial_face = 't';
		destination_face = 'e';
	}
	else if (initial_face == 'e' && destination_face == 'b') {
		initial_face = 't';
		destination_face = 'e';
	}
	else if (initial_face == 'w' && destination_face == 'b') {
		initial_face = 't';
		destination_face = 'w';
	}
	else if (initial_face == 'b' && destination_face == 'e') {
		initial_face = 't';
		destination_face = 'w';
	}
	else if (initial_face == 'e' && destination_face == 't') {
		initial_face = 't';
		destination_face = 'w';
	}
	else if (initial_face == 's' && destination_face == 't') {
		initial_face = 't';
		destination_face = 'n';
	}
	else if (initial_face == 'n' && destination_face == 'b') {
		initial_face = 't';
		destination_face = 'n';
	}
	else if (initial_face == 'b' && destination_face == 's') {
		initial_face = 't';
		destination_face = 'n';
		index_x = flip_around_1(index_x);
		index_y = flip_around_1(index_y);
	}
	else if (initial_face == 'n' && destination_face == 't') {
		initial_face = 't';
		destination_face = 's';
	}
	else if (initial_face == 'b' && destination_face == 'n') {
		initial_face = 't';
		destination_face = 's';
		index_x = flip_around_1(index_x);
		index_y = flip_around_1(index_y);
	}
	else if (initial_face == 's' && destination_face == 'b') {
		initial_face = 't';
		destination_face = 's';
	}
	else if (initial_face == 's' && destination_face == 'w') {
		initial_face = 'w';
		destination_face = 'n';
		int temp_index = index_y;
		index_y = flip_around_1(index_x);
		index_x = temp_index;
	}
	else if (initial_face == 'e' && destination_face == 's') {
		initial_face = 'w';
		destination_face = 'n';
		index_x = flip_around_1(index_x);
		index_y = flip_around_1(index_y);
	}
	else if (initial_face == 'n' && destination_face == 'e') {
		initial_face = 'w';
		destination_face = 'n';
		index_x = flip_around_1(index_x);
	}

	// We must rotate 12 squares
	string colours{}; // string length 12 

	switch (initial_face) {
	case 't':
		switch (destination_face) {
		case 'n':
			// Rotate face if a face has been rotated
			if (index_y == 0) {
				rotate_face('w', false);
			}
			else if (index_y == 2) {
				rotate_face('e', true);
			}
			// store colours of 12 squares that are being moved
			for (int r = 2; r > -1; --r)
				colours += top[r][index_y];
			for (int r = 2; r > -1; --r)
				colours += north[r][index_y];
			for (int r = 0; r < 3; ++r)
				colours += bottom[r][flip_around_1(index_y)];
			for (int r = 2; r > -1; --r)
				colours += south[r][index_y];

			// update the 12 moved squares in class
			north[2][index_y] = colours[0];
			north[1][index_y] = colours[1];
			north[0][index_y] = colours[2];
			bottom[0][flip_around_1(index_y)] = colours[3];
			bottom[1][flip_around_1(index_y)] = colours[4];
			bottom[2][flip_around_1(index_y)] = colours[5];
			south[2][index_y] = colours[6];
			south[1][index_y] = colours[7];
			south[0][index_y] = colours[8];
			top[2][index_y] = colours[9];
			top[1][index_y] = colours[10];
			top[0][index_y] = colours[11];
			break;
		case 'e':
			// Rotate face if a face has been rotated
			if (index_x == 0) {
				rotate_face('n', false);
			}
			else if (index_x == 2) {
				rotate_face('s', true);
			}
			// store colours of 12 squares that are being moved
			for (int r = 0; r < 3; ++r)
				colours += top[index_x][r];
			for (int r = 0; r < 3; ++r)
				colours += east[index_x][r];
			for (int r = 0; r < 3; ++r)
				colours += bottom[index_x][r];
			for (int r = 0; r < 3; ++r)
				colours += west[index_x][r];

			// update the 12 moved squares in class
			east[index_x][0] = colours[0];
			east[index_x][1] = colours[1];
			east[index_x][2] = colours[2];
			bottom[index_x][0] = colours[3];
			bottom[index_x][1] = colours[4];
			bottom[index_x][2] = colours[5];
			west[index_x][0] = colours[6];
			west[index_x][1] = colours[7];
			west[index_x][2] = colours[8];
			top[index_x][0] = colours[9];
			top[index_x][1] = colours[10];
			top[index_x][2] = colours[11];
			break;
		case 'w':
			// Rotate face if a face has been rotated
			if (index_x == 0) {
				rotate_face('n', true);
			}
			else if (index_x == 2) {
				rotate_face('s', false);
			}
			// store colours of 12 squares that are being moved
			for (int r = 2; r > -1; --r)
				colours += top[index_x][r];
			for (int r = 2; r > -1; --r)
				colours += west[index_x][r];
			for (int r = 2; r > -1; --r)
				colours += bottom[index_x][r];
			for (int r = 2; r > -1; --r)
				colours += east[index_x][r];

			// update the 12 moved squares in class
			west[index_x][2] = colours[0];
			west[index_x][1] = colours[1];
			west[index_x][0] = colours[2];
			bottom[index_x][2] = colours[3];
			bottom[index_x][1] = colours[4];
			bottom[index_x][0] = colours[5];
			east[index_x][2] = colours[6];
			east[index_x][1] = colours[7];
			east[index_x][0] = colours[8];
			top[index_x][2] = colours[9];
			top[index_x][1] = colours[10];
			top[index_x][0] = colours[11];
			break;
		case 's':
			// Rotate face if a face has been rotated
			if (index_y == 0) {
				rotate_face('w', true);
			}
			else if (index_y == 2) {
				rotate_face('e', false);
			}
			// store colours of 12 squares that are being moved
			for (int r = 0; r < 3; ++r)
				colours += top[r][index_y];
			for (int r = 0; r < 3; ++r)
				colours += south[r][index_y];
			for (int r = 2; r > -1; --r)
				colours += bottom[r][flip_around_1(index_y)];
			for (int r = 0; r < 3; ++r)
				colours += north[r][index_y];

			// update the 12 moved squares in class
			south[0][index_y] = colours[0];
			south[1][index_y] = colours[1];
			south[2][index_y] = colours[2];
			bottom[2][flip_around_1(index_y)] = colours[3];
			bottom[1][flip_around_1(index_y)] = colours[4];
			bottom[0][flip_around_1(index_y)] = colours[5];
			north[0][index_y] = colours[6];
			north[1][index_y] = colours[7];
			north[2][index_y] = colours[8];
			top[0][index_y] = colours[9];
			top[1][index_y] = colours[10];
			top[2][index_y] = colours[11];
			break;
		}
		break;
	case 'w':
		switch (destination_face) {
		case 'n':
			// Rotate face if a face has been rotated
			if (index_y == 0) {
				rotate_face('b', false);
			}
			else if (index_y == 2) {
				rotate_face('t', true);
			}
			// store colours of 12 squares that are being moved
			for (int r = 2; r > -1; --r)
				colours += west[r][index_y];
			for (int r = 0; r < 3; ++r)
				colours += north[index_y][r];
			for (int r = 0; r < 3; ++r)
				colours += east[r][flip_around_1(index_y)];
			for (int r = 2; r > -1; --r)
				colours += south[flip_around_1(index_y)][r];

			// update the 12 moved squares in class
			north[index_y][0] = colours[0];
			north[index_y][1] = colours[1];
			north[index_y][2] = colours[2];
			east[0][flip_around_1(index_y)] = colours[3];
			east[1][flip_around_1(index_y)] = colours[4];
			east[2][flip_around_1(index_y)] = colours[5];
			south[flip_around_1(index_y)][2] = colours[6];
			south[flip_around_1(index_y)][1] = colours[7];
			south[flip_around_1(index_y)][0] = colours[8];
			west[2][index_y] = colours[9];
			west[1][index_y] = colours[10];
			west[0][index_y] = colours[11];
			break;
		case 's':
			// Rotate face if a face has been rotated
			if (index_y == 0) {
				rotate_face('b', true);
			}
			else if (index_y == 2) {
				rotate_face('t', false);
			}
			// store colours of 12 squares that are being moved
			for (int r = 0; r < 3; ++r)
				colours += west[r][index_y];
			for (int r = 0; r < 3; ++r)
				colours += south[flip_around_1(index_y)][r];
			for (int r = 2; r > -1; --r)
				colours += east[r][flip_around_1(index_y)];
			for (int r = 2; r > -1; --r)
				colours += north[index_y][r];

			// update the 12 moved squares in class
			south[flip_around_1(index_y)][0] = colours[0];
			south[flip_around_1(index_y)][1] = colours[1];
			south[flip_around_1(index_y)][2] = colours[2];
			east[2][flip_around_1(index_y)] = colours[3];
			east[1][flip_around_1(index_y)] = colours[4];
			east[0][flip_around_1(index_y)] = colours[5];
			north[index_y][2] = colours[6];
			north[index_y][1] = colours[7];
			north[index_y][0] = colours[8];
			west[0][index_y] = colours[9];
			west[1][index_y] = colours[10];
			west[2][index_y] = colours[11];
			break;
		}
		break;
	}
}

void Cube::scramble(int num_moves) {
	// Makes a sequence of num_moves random moves to scramble the cube.
	srand(time(0));
	if (num_moves < 1)
		return;
	for (int i = 0; i < num_moves; ++i) {
		// random number to decide {tn,tw,te,ts,ws,wn}
		// random numbers to decide numbers index_x, index_y
		int x = rand() % 6;
		char initial_face = 't';
		char destination_face = 'n';
		if (x > 3) {
			initial_face = 'w';
			int y = rand() % 2;
			if (y == 0)
				destination_face = 's';
			else
				destination_face = 'n';
		}
		else {
			int y = rand() % 4;
			if (y == 0)
				destination_face = 'n';
			else if (y == 1)
				destination_face = 'w';
			else if (y == 2)
				destination_face = 'e';
			else {
				destination_face = 's';
			}
		}
		int index_x = rand() % 3;
		int index_y = rand() % 3;
		move(initial_face, destination_face, index_x, index_y);
	}
}


