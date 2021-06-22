#include "../include/Coords.h"
using std::cout;
using std::endl;

Coords::Coords(int x, int y) :_x(x), _y(y) {}
Coords::Coords(Coords& pos) :_x(pos._x), _y(pos._y) { }

void Coords::setX(int x) { _x = x; }
void Coords::setY(int y) { _y = y; }

int Coords::getX() { return _x; }
int Coords::getY() { return _y; }

const int Coords::operator()(const Axis& ax)
{
    if(ax == Axis::x)
        return _x;
    else
        return _y;
}

Coords Coords::operator++(int ax)
{
    if(ax == Axis::x)
        _x++;
    else
        _y++;
}

Coords Coords::operator--(int ax)
{
    if(ax == Axis::x)
        _x--;
    else
        _y--;
}

ostream& operator<<(ostream& os, Coords& pos)
{
    os << "(" << pos._x << ", " << pos._y << ")";
    return os;
}
