#include <iostream>
#include "Cube.h"
#include "SolveRubiksCube.h"

int main()
{
    vector<char> vec;
    vec.push_back('b');
    vec.push_back('y');
    vec.push_back('g');
    vector<vector<char>> vecs;
    vecs.push_back(vec);
    vecs.push_back(vec);
    vecs.push_back(vec);
    Cube cc = Cube(vecs, vecs, vecs, vecs, vecs, vecs);  // Create cube object
    Cube c = Cube();
    // c = cc;
    c.print();
    c.scramble(5);     // Scramble the cube
    c.print();
    cout << endl;
    SolveRubiksCube solve;  // Solve
    solve.hillClimbing(c);

}