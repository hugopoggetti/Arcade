#include "Transform.hpp"

Transform::Transform(const Position &position,
    const Rotation &rotation, const Size &size) :
    _position(position), _rotation(rotation), _size(size) {}

Transform::Transform(const Position &position, double degrees,
    const Size &size) :
    _position(position), _rotation(degrees), _size(size) {}

Transform::Transform(const Transform &other)
{
    _position = other._position;
    _size = other._size;
    _rotation = other._rotation;
}

Position &Transform::getPosition()
{
    return _position;
}

const Position &Transform::getPosition() const
{
    return _position;
}

Rotation &Transform::getRotation()
{
    return _rotation;
}

const Rotation &Transform::getRotation() const
{
    return _rotation;
}

Size &Transform::getSize()
{
    return _size;
}

const Size &Transform::getSize() const
{
    return _size;
}

void Transform::operator=(const Transform &other)
{
    _position = other._position;
    _size = other._size;
    _rotation = other._rotation;
}
