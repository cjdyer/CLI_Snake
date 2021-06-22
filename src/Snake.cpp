#include "../include/Direction.h"
#include "../include/Coords.h"
#include "../include/Symbol.h"
#include "../include/Snake.h"
#include <iostream>
using std::cout;
using std::endl;

Snake::Snake() :length(1), headSymbol(Head_Symbol::LookUp), 
                bodySymbol(Body_Symbol::Vertical) 
{
    headCoords = Coords();
    oldHeadCoords = Coords();    
}

Snake::Snake(int x, int y)
    :length(3), 
    oldHeadCoords(Coords()), headSymbol(Head_Symbol::LookUp), bodySymbol(Body_Symbol::Vertical)
{
    headCoords = (Coords(((x+1)/2)-1, ((y + 1) / 2) - 1))
    bodyArray.reserve(2);
    bodyArray.push_back(headCoords);
}

const unsigned int Snake::Length() 
{ return length; }

Coords& Snake::HeadCoords() 
{ return headCoords; }

const unsigned int Snake::HeadCoord(const Axis& ax)
{ return headCoords(ax); }

Coords& Snake::OldHeadCoords() 
{ return oldHeadCoords; }

const unsigned int Snake::OldHeadCoord(const Axis& ax)
{ return oldHeadCoords(ax); }

const Head_Symbol& Snake::HeadSymbol() 
{ return headSymbol; }

const Body_Symbol& Snake::BodySymbol() 
{ return bodySymbol; }

const vector<Coords>& Snake::BodyArray() 
{ return bodyArray; }

void Snake::move(const Direction& dir, const Direction& oldDir)
{
    oldHeadCoords = headCoords;

    switch(dir)
    {
        case Up:
            headCoords--(Axis::y);
            headSymbol = Head_Symbol::LookUp;
            
            updateBody();

            switch(oldDir)
            {
                case Up:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
                    
                case Down:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
                    
                case Left:
                    bodySymbol = Body_Symbol::BottomLeft;
                    break;
                    
                case Right:
                    bodySymbol = Body_Symbol::BottomRight;
                    break;
                    
                case None:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
            }
            break;
            
        case Down:
            headCoords++(Axis::y);
            headSymbol = Head_Symbol::LookDown;
            
            updateBody();
            
            switch(oldDir)
            {
                case Up:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
                    
                case Down:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
                    
                case Left:
                    bodySymbol = Body_Symbol::TopLeft;
                    break;
                    
                case Right:
                    bodySymbol = Body_Symbol::TopRight;
                    break;
                    
                case None:
                    bodySymbol = Body_Symbol::Vertical;
                    break;
            }
            break;
            
        case Left:
            headCoords--(Axis::x);
            headSymbol = Head_Symbol::LookLeft;
            
            updateBody();
            
            switch(oldDir)
            {
                case Up:
                    bodySymbol = Body_Symbol::TopRight;
                    break;
                    
                case Down:
                    bodySymbol = Body_Symbol::BottomRight;
                    break;
                    
                case Left:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
                    
                case Right:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
                    
                case None:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
            }
            break;
            
        case Right:
            headCoords++(Axis::x);
            headSymbol = Head_Symbol::LookRight;
            
            updateBody();
            
            switch(oldDir)
            {
                case Up:
                    bodySymbol = Body_Symbol::TopLeft;
                    break;
                    
                case Down:
                    bodySymbol = Body_Symbol::BottomLeft;
                    break;
                    
                case Left:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
                    
                case Right:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
                    
                case None:
                    bodySymbol = Body_Symbol::Horizontal;
                    break;
            }
            break;
        case None:
            cout << "Current direction was None :/" << endl;
            break;
    }
}

void Snake::updateBody()
{
    bodyArray.push_back(headCoords);
    
    tailCoords = bodyArray[length - 1];
    
    bodyArray.erase(bodyArray.begin() + length - 1);
}

Coords& Snake::TailCoords()
{ return tailCoords; }
