#pragma once

#include "Coords.h"
#include "Direction.h"
#include "Symbol.h"
#include <vector>
using std::vector;

class Snake
{
public:
    Snake();
    Snake(const int x, const int y);
    
    void move(const Direction& dir, const Direction& oldDir);
    
    const unsigned int Length();
    
    Coords& HeadCoords();
    const unsigned int HeadCoord(const Axis& ax);

    Coords& OldHeadCoords();
    const unsigned int OldHeadCoord(const Axis& ax);
    
    const Head_Symbol& HeadSymbol();
    const Body_Symbol& BodySymbol();

    const vector<Coords>& BodyArray();
    
    Coords& TailCoords();
    
    
private:
    int length;
    
    Coords headCoords;
    Coords oldHeadCoords;

    Head_Symbol headSymbol;
    Body_Symbol bodySymbol;
    
    vector<Coords> bodyArray;
    
    Coords tailCoords;
    
private:
    void updateBody();
};
