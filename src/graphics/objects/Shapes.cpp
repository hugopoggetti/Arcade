#include "Shapes.hpp"

/* ------------------------------------------------ */

Rectangle::Rectangle() : _colorID(Color::TRANSPARENT), _fill(false) {}


Rectangle::Rectangle(const Rectangle &other)
{
    _transform = other._transform;
}

Transform &Rectangle::getTransform()
{
    return _transform;
}

const Transform &Rectangle::getTransform() const
{
    return _transform;
}

void Rectangle::setColor(Color::ColorID color)
{
    _colorID = color;
}

Color::ColorID Rectangle::getColor() const
{
    return _colorID;
}

void Rectangle::fillRect(bool fill)
{
    _fill = fill;
}

bool Rectangle::isFilled() const
{
    return _fill;
}

void Rectangle::operator=(const Rectangle &other)
{
    _transform = other._transform;
    _colorID = other._colorID;
    _fill = other._fill;
}

/* ------------------------------------------------ */
