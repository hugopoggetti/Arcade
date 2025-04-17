#ifndef __SHAPES__
    #define __SHAPES__

#include "../transform/Transform.hpp"
#include "../color/Color.hpp"

class Rectangle {
    public:
        Rectangle();
        Rectangle(const Rectangle &other);
        ~Rectangle() = default;
        Transform &getTransform();
        const Transform &getTransform() const;
        void setColor(Color::ColorID color);
        Color::ColorID getColor() const;
        void fillRect(bool fill);
        bool isFilled() const;
        void operator=(const Rectangle &other);
    private:
        Transform _transform;
        Color::ColorID _colorID;
        bool _fill;
};

#endif
