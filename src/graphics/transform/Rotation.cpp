#include "Rotation.hpp"

Rotation::Rotation() : _degrees(0) {}

Rotation::Rotation(double degrees) : _degrees(degrees) {}

void Rotation::setDegrees(double degrees)
{
    _degrees = degrees;
}

double Rotation::getDegrees() const
{
    return _degrees;
}

Rotation &Rotation::operator+=(double degrees)
{
    _degrees += degrees;
    return *this;
}

Rotation &Rotation::operator-=(double degrees)
{
    _degrees -= degrees;
    return *this;
}

Rotation Rotation::operator+(double degrees)
{
    Rotation newRotation;

    newRotation._degrees = _degrees + degrees;
    return newRotation;
}

Rotation Rotation::operator-(double degrees)
{
    Rotation newRotation;

    newRotation._degrees = _degrees - degrees;
    return newRotation;
}

Rotation::operator double() const
{
    return _degrees;
}

void Rotation::operator=(double degrees)
{
    _degrees = degrees;
}
