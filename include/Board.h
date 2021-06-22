#pragma once

#include "Coords.h"
#include "Symbol.h"

template<int X, int Y>
class Board
{
public:
    Board();

    void Print() const;

    void Set(Coords& pos, const Head_Symbol sym);
    void Set(Coords& pos, const Body_Symbol sym);

    int Get(Coords& pos) const;
    
    void Clear(Coords& pos);

public:
    static int constexpr Width = X;
    static int constexpr Height = Y;

private:
    const char* pixelArray[X][Y];
};
