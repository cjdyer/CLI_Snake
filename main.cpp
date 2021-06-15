#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int x, y;
bool running = true; // is game running 

void registerKeyPress()
{
    if(_kbhit()) // If key hit
    {
        switch(_getch()) // switch on key
        {
        case 'w': //up
            y++;
            break;
        case 'a': //left
            x--;
            break;
        case 's': //down
            y--;
            break;
        case 'd': //right
            x++;
            break;
        default: // Anything else pressed
            running = false;
            break;
        }
    }
}

void drawGame()
{
    system("CLS");
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

int main()
{
    while(running)
    {
        registerKeyPress();
        drawGame();
    }
}