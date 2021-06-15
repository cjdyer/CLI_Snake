#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int x, y, prevX, prevY;
int width = 30, height = 10;
bool running = true; // is game running

enum direction {Up, Down, Left, Right};
direction dir; 

void setCursorPosition(int x, int y)
{
    COORD position = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); // Set cursor position
}

void registerKeyPress()
{
    if(_kbhit()) // If key hit
    {
        switch(_getch()) // switch on key
        {
        case 'w': //up
            dir = Up;
            break;
        case 's': //down
            dir = Down;
            break;
        case 'a': //left
            dir = Left;
            break;
        case 'd': //right
            dir = Right;
            break;
        default: // Anything else pressed
            running = false;
            break;
        }
    }
}

void moveCharacter()
{
    prevX = x;
    prevY = y;
    switch(dir)
    {
    case Up:
        y--; //minus for up the screen
        break;
    case Down:
        y++;
        break;
    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    }
    if (x < 1 || x > width - 2 || y < 1 || y > height)
        running = false;
}

void drawGame()
{
    setCursorPosition(prevX, prevY); // clear previous
    std::cout << " ";
    setCursorPosition(x, y); 
    std::cout << "O";
}

void setup()
{
    system("cls"); //Clear screen

    for(int i = 0; i < width; i++)
    {
        std::cout << "#";
    }

    std::cout << std::endl;

    for(int i = 0; i < height; i++)
    {
        std::cout << "#";
        for (int j = 0; j < width - 2; ++j) // minus 2 for the 2 wall places
        {
            std::cout << " ";
        }
        std::cout << "#" << std::endl;
    }

    for(int i = 0; i < width; i++)
    {
        std::cout << "#";
    }
}

int main()
{
    // Hide cursor 
    // Taken from : https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo); // Get cursor info
    cursorInfo.bVisible = false;            // Set visible to false
    SetConsoleCursorInfo(out, &cursorInfo); // Set current info to updated info

    x = width / 2;
    y = height / 2;

    setup();

    while(running)
    {
        registerKeyPress();
        moveCharacter();
        drawGame();
        Sleep(100);
    }
}