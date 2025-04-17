#pragma once

#include "../../IDisplayModule.hpp"
#include "NcurseLibCache.hpp"
#include "../../../events/EventsSystem.hpp"
#include "../../../events/Events.hpp"
#include "../../../events/Listener.hpp"
#include "../../color/Color.hpp"
#include <ncurses.h>

class NcurseLib : public IDisplayModule {
    public:
        NcurseLib();
        ~NcurseLib();
        void init(int width, int height) override;
        void clear() override;
        void draw(const Sprite &sprite) override;
        void draw(const Text &text) override;
        void draw(const Rectangle &rectangle) override;
        void destroy() override;
        std::queue<IEvent *> pollEvents() override;
        void display() override;
        void setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette) override;
        void setGridSize(size_t x, size_t y) override;
        void setWindowSize(int x, int y) override;
        const Plugin &getPlugin() const override;
    private:
        void KeyBoardEvents(const int ch, std::queue<IEvent *> &events) const;
        void MouseEvents(const int ch, std::queue<IEvent *> &events) const;
        void setTermSize();
        std::map<Color::ColorID, Color::color_t> _colorpalette;
        std::pair<std::size_t, std::size_t> _grid;
        int terminalWidth;
        int terminalHeight;
        int _width;
        int _height;
        NcurseLibCache _cache;
        Plugin _plugin;
};

