#include "Position.hpp"

Position::Position() : _x(0), _y(0) {}

Position::Position(double x, double y) : _x(x), _y(y) {}

Position::Position(const Position &other)
{
    _x = other._x;
    _y = other._y;
}

void Position::setX(double x)
{
    _x = x;
}

void Position::setY(double y)
{
    _y = y;
}

void Position::setPosition(double x, double y)
{
    _x = x;
    _y = y;
}

double Position::getX() const
{
    return _x;
}

double Position::getY() const
{
    return _y;
}

bool Position::operator==(const Position &other)
{
    if (_x == other._x && _y == other._y) {
        return true;
    }
    return false;
}

bool Position::operator!=(const Position &other)
{
    if (_x != other._x || _y != other._y) {
        return true;
    }
    return false;
}

Position &Position::operator+=(const Position &other)
{
    _x += other._x;
    _y += other._y;
    return *this;
}

Position &Position::operator-=(const Position &other)
{
    _x += other._x;
    _y += other._y;
    return *this;
}

Position Position::operator+(const Position &other)
{
    Position newPosition;

    newPosition._x = _x + other._x;
    newPosition._y = _y + other._y;
    return newPosition;
}

Position Position::operator-(const Position &other)
{
    Position newPosition;

    newPosition._x = _x - other._x;
    newPosition._y = _y - other._y;
    return newPosition;
}

void Position::operator=(const Position &other)
{
    _x = other._x;
    _y = other._y;
}
