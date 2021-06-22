#pragma once
#include <iostream>
using std::ostream;

enum Axis { x, y };

class Coords
{
  private:
    int _x, _y;
    
  public:
    Coords(int x = 0, int y = 0);
    Coords(Coords& pos);

    void setX(int x);
    void setY(int y);

    int getX();
    int getY();

    const int operator()(const Axis& ax);

    Coords operator++(int ax);
    Coords operator--(int ax);
    
    friend ostream& operator<<(ostream& os, Coords& pos);
};
