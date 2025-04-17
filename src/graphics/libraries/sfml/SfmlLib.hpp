#ifndef __SFML_LIB__
    #define __SFML_LIB__

#include "SfmlLibCache.hpp"

#include "../../IDisplayModule.hpp"
#include "../../color/Color.hpp"

#include "../../../events/EventsSystem.hpp"
#include "../../../plugin/Plugin.hpp"

#include <map>

#include <SFML/Graphics.hpp>

class SfmlLib : public IDisplayModule {
    public:
        SfmlLib();
        ~SfmlLib();
        void init(int width, int height) override;
        void clear() override;
        void draw(const Sprite &sprite) override;
        void draw(const Text &text) override;
        void draw(const Rectangle &rectangle) override;
        void display() override;
        void destroy() override;
        void setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette) override;
        void setGridSize(std::size_t x, std::size_t y) override;
        std::queue<IEvent *> pollEvents() override;
        void setWindowSize(int x, int y) override;
        const Plugin &getPlugin() const override;
    private:
        static ArcadeKey getArcadeKey(const sf::Event &event);
        static ArcadeMouseButton getArcadeButton(const sf::Event &event);

        int _width;
        int _height;
        bool _windowInitialized;
        std::map<Color::ColorID, Color::color_t> _colors;
        sf::RenderWindow _window;
        SfmlLibCache _cache;
        std::pair<std::size_t, std::size_t> _gridRatio;
        Plugin _libPlugin;
};

#endif
