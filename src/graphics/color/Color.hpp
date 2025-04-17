#ifndef __COLOR__
    #define __COLOR__

namespace Color
{
    typedef struct color_s {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } color_t;

    enum ColorID {
        BACKGROUND,
        TRANSPARENT,
        BLUE,
        RED,
        BLACK,
        WHITE,
        GREEN,
        YELLOW,
        PURPLE,
        ORANGE
    };
}

#endif
