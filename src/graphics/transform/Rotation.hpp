#ifndef __ROTATION__
    #define __ROTATION__

class Rotation {
    public:
        Rotation();
        Rotation(double degrees);
        ~Rotation() = default;
        void setDegrees(double degrees);
        double getDegrees() const;
        Rotation &operator+=(double degrees);
        Rotation &operator-=(double degrees);
        Rotation operator+(double degrees);
        Rotation operator-(double degrees);
        operator double () const;
        void operator=(double degrees);
    private:
        double _degrees;
};

#endif
