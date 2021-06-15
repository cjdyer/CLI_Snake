#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int length;
int width = 30, height = 10;
bool running = true; // is game running

enum direction {Up, Down, Left, Right};
direction dir; 

struct Point
{
    int x;
    int y;

    bool operator==(const Point& a) const
    {
        return (a.x == x && a.y == y);
    }
};

Point headPos;
Point foodPos;

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
    switch(dir)
    {
    case Up:
        headPos.y--; //minus for up the screen
        break;
    case Down:
        headPos.y++;
        break;
    case Left:
        headPos.x--;
        break;
    case Right:
        headPos.x++;
        break;
    }
    if (headPos.x < 1 || headPos.x > width - 2 || headPos.y < 1 || headPos.y > height)
        running = false;
}

void drawGame()
{
    // setCursorPosition(prevX, prevY); // clear previous
    // std::cout << " ";
    // setCursorPosition(x, y); 
    // std::cout << "O";
}

void setup()
{
    system("cls"); //Clear screen

    // Start Draw walls

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

    // END Draw walls
    
    foodPos.x = rand() % width;
    foodPos.y = rand() % height;

    if (foodPos == headPos)
    {
        foodPos.x--;
    }

    setCursorPosition(foodPos.x, foodPos.y);
    std::cout << "@";
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

    headPos.x = width / 2;
    headPos.y = height / 2;

    setup();

    while(running)
    {
        registerKeyPress();
        //moveCharacter();
        drawGame();
        Sleep(100);
    }
}