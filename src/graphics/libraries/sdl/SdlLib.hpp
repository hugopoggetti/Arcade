#ifndef __SDL_LIB__
    #define __SDL_LIB__

#include "../../IDisplayModule.hpp"
#include "../../color/Color.hpp"

#include "../../../events/EventsSystem.hpp"
#include "../../../plugin/Plugin.hpp"

#include <map>

#include <SDL2/SDL.h>

class SdlLib : public IDisplayModule {
    public:
        SdlLib();
        ~SdlLib();
        void init(int width, int height) override;
        void clear() override;
        void draw(const Sprite &sprite) override;
        void draw(const Text &text) override;
        void draw(const Rectangle &rectangle) override;
        void display() override;
        void destroy() override;
        void setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette) override;
        void setGridSize(size_t x, size_t y) override;
        std::queue<IEvent *> pollEvents() override;
        void setWindowSize(int x, int y) override;
        const Plugin &getPlugin() const override;
    private:
        static ArcadeKey getArcadeKey(SDL_Event event);
        static ArcadeMouseButton getArcadeMouseButton(SDL_Event event);

        int _width;
        int _height;
        std::map<Color::ColorID, Color::color_t> _colors;
        SDL_Window *_window;
        SDL_Renderer *_windowRenderer;
        std::pair<std::size_t, std::size_t> _grid;
        Plugin _libPlugin;
};

#endif
