#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <algorithm>

int width = 30, height = 10;
bool running = true; // is game running
bool addSeg = false;

enum direction {Up, Down, Left, Right};
direction dir; 

struct Point
{
    int x;
    int y;

    bool operator==(const Point& point)
    {
        return (point.x == x && point.y == y);
    }

    bool operator==(const std::vector<Point>& points)
    {
        for (int i = 0; i < points.size(); i++)
        {
            if(points[i].x == x && points[i].y == y)
                return true;
        }
        return false;
    }
};

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    return out << point.x << " " << point.y;
}

Point foodPos = Point();
std::vector<Point> bodyPositions;

void setCursorPosition(Point point)
{
    COORD position = {(SHORT)point.x, (SHORT)point.y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); // Set cursor position
}

void registerKeyPress()
{
    if(_kbhit()) // If key hit
    {
        switch(_getch()) // switch on key
        {
            case 'w': //up
                if (dir != Down || bodyPositions.size() == 1)
                    dir = Up;
                break;
            case 's': //down
                if (dir != Up || bodyPositions.size() == 1)
                    dir = Down;
                break;
            case 'a': //left
                if (dir != Right || bodyPositions.size() == 1)
                    dir = Left;
                break;
            case 'd': //right
                if (dir != Left || bodyPositions.size() == 1)
                    dir = Right;
                break;
            default: // Anything else pressed
                for (int i = 0; i < bodyPositions.size(); i++)
                {
                    setCursorPosition({5, i});
                    std::cout << bodyPositions[i].x << " " << bodyPositions[i].y;
                }
                running = false;
                break;
        }
    }
}

void moveCharacter()
{
    Point tailPos = {bodyPositions.back().x, bodyPositions.back().y};

    setCursorPosition({0, 0});
    std::cout << tailPos;

    for (Point point : bodyPositions)
    {
        setCursorPosition(point); 
        std::cout << " ";
    }

    for(int i = 1; i < bodyPositions.size(); i++)
    {
        bodyPositions[i] = {bodyPositions[i-1].x, bodyPositions[i-1].y};
    }

    switch(dir)
    {
    case Up:
        bodyPositions[0].y--; //minus for up the screen
        break;
    case Down:
        bodyPositions[0].y++;
        break;
    case Left:
        bodyPositions[0].x--;
        break;
    case Right:
        bodyPositions[0].x++;
        break;
    }

    if (bodyPositions[0].x < 1 || bodyPositions[0].x > width - 2 || bodyPositions[0].y < 1 || bodyPositions[0].y > height)
    {
        running = false;
    }
    else if (bodyPositions[0] == foodPos) // Food eaten
    {
        do // Make sure food is placed in the body
        {
            foodPos.x = rand() % (width - 2) + 1;
            foodPos.y = rand() % height + 1;
        } while(foodPos == bodyPositions); 

        setCursorPosition(foodPos);
        std::cout << "@";
        bodyPositions.push_back(tailPos);
    }

    for (Point point : bodyPositions)
    {
        setCursorPosition(point); 
        std::cout << "O";
    }
}

void setup()
{
    bodyPositions.push_back({width / 2, height / 2});

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
    
    foodPos.x = rand() % (width + 1) - 1;
    foodPos.y = rand() % height + 1;

    if (foodPos == bodyPositions[0])
    {
        foodPos.x--;
    }

    setCursorPosition(foodPos);
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

    setup();

    while(running)
    {
        registerKeyPress();
        moveCharacter();
        Sleep(200);
    }
}