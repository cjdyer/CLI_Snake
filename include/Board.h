#pragma once

#include "Coords.h"
#include "Symbol.h"

template<int X, int Y>
class Board
{
    public:
        Board();

        void print();

        static int constexpr width = X;
        static int constexpr height = Y;

        void set(Coords pos, Symbol sym);

    private:
        const char* pixelArray[X][Y];
};