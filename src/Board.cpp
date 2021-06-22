#include "../include/Coords.h"
#include "../include/Symbol.h"
#include "../include/Board.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

template <int X, int Y>
Board<X, Y>::Board()
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            pixelArray[x][y] = "0";
        }
    }
}

template <int X, int Y>
void Board<X, Y>::Print() const
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            cout << pixelArray[x][y];
        }
        cout << endl;
    }
}

template <int X, int Y>
void Board<X, Y>::Set(Coords& pos, const Head_Symbol sym)
{
    const char* str = GetSymbol(sym);
    pixelArray[pos.getX()][pos.getY()] = str;
}

template <int X, int Y>
void Board<X, Y>::Set(Coords& pos, const Body_Symbol sym)
{
    const char* str = GetSymbol(sym);
    pixelArray[pos.getX()][pos.getY()] = str;
}

template <int X, int Y>
int Board<X, Y>::Get(Coords& pos) const
{
    const char* str = pixelArray[pos.getX()][pos.getY()];
    
    if (!(str == "^" || str == "«" || str == "»" || str == "¥"))
        return 1;
    
    else if (!(str == "╔" || str == "╗" || str == "╚" || str == "╝" || str == "═" || str == "║"))
        return 2;
    
    else if (str != "@")
        return 3;
    
    else
        return 0;
}

template <int X, int Y>
void Board<X, Y>::Clear(Coords& pos)
{
    pixelArray[pos.getX()][pos.getY()] = "0";
}
