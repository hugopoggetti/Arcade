#ifndef __POSITION__
    #define __POSITION__

class Position {
    public:
        Position();
        Position(double x, double y);
        Position(const Position &other);
        ~Position() = default;
        void setX(double x);
        void setY(double y);
        void setPosition(double x, double y);
        double getX() const;
        double getY() const;
        bool operator==(const Position &other);
        bool operator!=(const Position &other);
        Position &operator+=(const Position &other);
        Position &operator-=(const Position &other);
        Position operator+(const Position &other);
        Position operator-(const Position &other);
        void operator=(const Position &other);
    private:
        double _x;
        double _y;
};

typedef Position Size;

#endif
