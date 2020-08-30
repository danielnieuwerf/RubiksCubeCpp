#include "SolveRubiksCube.h"

void SolveRubiksCube::hillClimbing(Cube cube) {
	/*
		Standard hill climbing algorithm to solve cube.
		Start at cube and work towards solved cube.
		 
	ALGORITHM
	1. Create two lists, L and Lseen. Initially, L contains only the initial state, and Lseen is empty.
	2. Compare L[0] with the ﬁnal state.
	   If they are identical, stop with success.
	3. Apply to L[0] all available moves, thus obtaining a set of new states.
	   Discard those states that already exist in Lseen.
	   As for the rest, sort them by the evaluation function and place them at the front of L.
	4. Transfer L[0] from L into the list Lseen.
	5. If L is empty stop and report failure. Otherwise, go to 2.
	
	*/

	// ALG1.
	vector<Cube> L{}, Lseen{};	// Initialise L and Lseen
	L.push_back(cube);     // add cube to L and leave Lseen empty

	// ALG2.
	bool done = false;
	bool success = false;
	while (!done) {
		if (L[0].distance_from_completion() == 0) {
			done = true;
			success = true;
		}

		// ALG3.
		if (!done) {
			vector<Move> moves = L[0].getPossibleMoves();	// Possible moves the cube can make
			for (Move move : moves) {	// Make all possible moves on copies of the cube
				Cube copyCube = L[0];
				copyCube.move(move);	// Make move on copy cube
				// If copy cube is now a new unseen cube add it to L
				if(find(Lseen.begin(), Lseen.end(), copyCube)==Lseen.end())
					L.push_back(copyCube);
			}

			// ALG4. Transfer L[0] from L into the list Lseen.
			if (find(Lseen.begin(), Lseen.end(), L[0]) == Lseen.end()) {  // If L[0] not in Lseen add to Lseen
				Lseen.push_back(L[0]);
			}
			L.erase(L.begin()); // delete first element from L

			unique(L.begin(), L.end(), [](Cube& a, Cube& b) -> bool {
				return a == b; });   // Remove copies from L

			// Sort L by distance to completion
			sort(L.begin(), L.end(), [](Cube& a, Cube& b) -> bool {
				return a.distance_from_completion() < b.distance_from_completion(); });

			// ALGORITHM 5.
			if (L.empty()) {	// If L is empty report failure
				done = true;
				success = false;
			}
			// PRINT L if it exists
			else {
				cout << "______________" << endl;
				for (Cube c : L) {
					cout << "Distance from completion: " << c.distance_from_completion() << endl;
					c.print();
					cout << endl;
					break;	// so only prints L[0]
				}
				cout << "______________" << endl;

			}
		}
	}

	cout << "DONE!" << endl;
	L[0].print();

	return;
}

void SolveRubiksCube::hillClimbingBackwards(Cube cube) {
	/*
		Start with a solved cube and work towards cube using hill climbing
	*/

	Cube solvedCube = Cube();	// Initialise solved cube
	return;
}