#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

class Cube
{
public:
	/*
	Representation of the cube:
	  N
	W T E B
	  S
	Each face is a 3x3 vector of chars denoting colour 'rgbywo'
	Each face is indexed as follows:
	00 01 02
	10 11 12
	20 21 22
	*/
	vector<vector<char>> top{ 3 };
	vector<vector<char>> bottom{ 3 };
	vector<vector<char>> north{ 3 };
	vector<vector<char>> west{ 3 };
	vector<vector<char>> south{ 3 };
	vector<vector<char>> east{ 3 };

	// functions defined in Cube.cpp file
	int flip_around_1(int x);
	void move(char initial_face, char destination_face, int index_x, int index_y);
	void scramble(int num_moves);
	void rotate_face(char face, bool clockwise);
	void print();
	int distance_from_completion();

	// Constructors
	Cube();
	Cube(vector<vector<char>> t, vector<vector<char>> b, vector<vector<char>> n, vector<vector<char>> w, vector<vector<char>> s, vector<vector<char>> e);

	// Operator overloading
	bool operator==(Cube cube);
	void operator=(Cube cube);

};

