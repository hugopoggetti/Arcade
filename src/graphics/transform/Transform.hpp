#ifndef __TRANSFORM__
    #define __TRANSFORM__

#include "Position.hpp"
#include "Rotation.hpp"

class Transform{
    public:
        Transform() = default;
        Transform(const Position &position, const Rotation &rotation, const Size &size);
        Transform(const Position &position, double degrees, const Size &size);
        Transform(const Transform &other);
        ~Transform() = default;
        Position &getPosition();
        const Position &getPosition() const;
        Size &getSize();
        const Size &getSize() const;
        Rotation &getRotation();
        const Rotation &getRotation() const;
        void operator=(const Transform &other);
    private:
        Position _position;
        Rotation _rotation;
        Size  _size;
};

#endif
