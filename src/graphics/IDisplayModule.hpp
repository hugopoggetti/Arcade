#ifndef __IDISPLAY_MODULE__
    #define __IDISPLAY_MODULE__

#include "transform/Transform.hpp"
#include "objects/Sprite.hpp"
#include "objects/Text.hpp"
#include "objects/Shapes.hpp"
#include "color/Color.hpp"

#include "../plugin/IModule.hpp"

#include <map>
#include <queue>

class IEvent;

class IDisplayModule : public IModule {
    public:
        IDisplayModule() = default;
        virtual ~IDisplayModule() = default;
        virtual void init(int width, int height) = 0;
        virtual void clear() = 0;
        virtual void draw(const Sprite &sprite) = 0;
        virtual void draw(const Text &text) = 0;
        virtual void draw(const Rectangle &rectangle) = 0;
        virtual void display() = 0;
        virtual void destroy() = 0;
        virtual std::queue<IEvent *> pollEvents() = 0;
        virtual void setGridSize(std::size_t x, std::size_t y) = 0;
        virtual void setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette) = 0;
        virtual void setWindowSize(int x, int y) = 0;
};

#endif
