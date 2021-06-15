#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int x, y, prevX, prevY;
int width = 30, height = 10;
bool running = true; // is game running 

void setCursorPosition(int x, int y)
{
    COORD position = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); // Set cursor position
}

void registerKeyPress()
{
    prevX = x;
    prevY = y;
    if(_kbhit()) // If key hit
    {
        switch(_getch()) // switch on key
        {
        case 'w': //up
            y--; // minus for up the screen
            break;
        case 'a': //left
            x--;
            break;
        case 's': //down
            y++;
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
    if (prevX == x && prevY == y) // Dont redraw
        return;
    setCursorPosition(prevX, prevY); // Clear previous position
    std::cout << " "; 
    setCursorPosition(x, y); // Print x at line 1 index 1
    std::cout << "O";
}

void drawWalls(int width, int height)
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

    drawWalls(width, height);
    while(running)
    {
        registerKeyPress();
        drawGame();
    }
}