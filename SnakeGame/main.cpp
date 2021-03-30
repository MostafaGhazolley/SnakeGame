#include <iostream>
#include "Game_Objects.cpp"

using std::cin;
using std::endl;
using std::cout;

extern bool gameOver;


int main()
{
	Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(5);
    }


    return 0;
}
  