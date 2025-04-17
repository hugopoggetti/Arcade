#include "Map.hpp"
#include "../../graphics/objects/Shapes.hpp"

void Map::displayMap(int startx, int starty,
        const std::vector<std::vector<Element>>& map,
        IDisplayModule* dsp)
{
    Rectangle rect;
    rect.getTransform().getSize().setPosition(1, 1);
    rect.fillRect(1);

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            switch (map[i][j]) {
                case _M: rect.setColor(Color::ColorID::BLUE); break;
                case _P: rect.setColor(Color::ColorID::WHITE); break;
                case _W: rect.setColor(Color::ColorID::GREEN); break;
                case _I: rect.setColor(Color::ColorID::RED); break;
                case _G: rect.setColor(Color::ColorID::YELLOW); break;
                case _V: continue;
            }

            rect.getTransform().getPosition().setPosition(
                static_cast<double>(j) + startx,
                static_cast<double>(i) + starty
            );
            dsp->draw(rect);
        }
    }
}

std::vector<std::vector<Element>> Map::getMap() const {
    return _map;
}
