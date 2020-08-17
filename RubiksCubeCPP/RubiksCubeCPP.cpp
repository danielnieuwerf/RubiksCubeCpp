#include <iostream>
#include "Cube.h"
int main()
{
    Cube c = Cube();
    c.print();
    //cout << endl;
    //c.north[0][0] = 'x';
    //c.top[0][1] = 'y';
    //c.top[0][2] = 'z';
    c.scramble(10);
    c.print();
    cout << endl;

}