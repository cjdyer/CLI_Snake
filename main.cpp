#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <algorithm>

int width = 30, height = 10;
bool running = true; // is game running
int length;
bool addSeg = false;

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

    bool operator==(const std::vector<Point>& a) const
    {
        for(Point i : a) 
        {
            if (&i == this)
                return true;
        }      
    }

    Point operator=(Point a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }
};

Point foodPos;
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
                if (dir != Down || length == 1)
                    dir = Up;
                break;
            case 's': //down
                if (dir != Up || length == 1)
                    dir = Down;
                break;
            case 'a': //left
                if (dir != Right || length == 1)
                    dir = Left;
                break;
            case 'd': //right
                if (dir != Left || length == 1)
                    dir = Right;
                break;
            default: // Anything else pressed
                for(int i = 0; i < length; i++)
                {
                    setCursorPosition({5,i});  
                    std::cout << bodyPositions[i].x;
                    setCursorPosition({8,i});  
                    std::cout << bodyPositions[i].y;
                }
                running = false;
                break;
        }
    }
}

void moveCharacter()
{
    setCursorPosition(bodyPositions[length -1]); 
    std::cout << " ";

    if (addSeg)
    {
        bodyPositions.push_back({bodyPositions[length - 1].x, bodyPositions[length - 1].y}); // TODO: This line appends the last item in bodyPositions
        length++;                                                                            // But not the tail position.
        addSeg = false;
    }
    else if (length >= 2)
    {
        for(int i = 1; i < length; i++)
        {
            bodyPositions[i] = bodyPositions[i-1];
        }
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
        addSeg = true;
    }

    setCursorPosition(bodyPositions[0]); 
    std::cout << "O";
}

void setup()
{
    bodyPositions.push_back({width / 2, height / 2});
    length = 1;

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
    while(true);
}