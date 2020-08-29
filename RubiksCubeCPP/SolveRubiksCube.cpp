#include "SolveRubiksCube.h"

void SolveRubiksCube::hillClimbing(Cube cube) {
	// Standard hill climbing algorithm to solve cube
	Cube copy = cube;
	copy.scramble(1);
	cout << "..." << copy.distance_from_completion();
	// Print solution 
	cout << "solution";

	return;
}

void SolveRubiksCube::hillClimbingBackwards(Cube cube) {
	// Start with a solved cube and work towards the initial state of the unsolved cube using hill climbing
	return;
}